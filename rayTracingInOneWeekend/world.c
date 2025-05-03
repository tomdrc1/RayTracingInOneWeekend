#include "world.h"

void worldInit(World* world, const unsigned int imageWidth, const unsigned int imageHeight, const unsigned int shapeCount)
{
	cameraInit(&world->camera, imageWidth, imageHeight);
	ppmImageInit(&world->image, IMAGE_NAME, imageWidth, imageHeight);

	world->shapes = (Shape*)malloc(sizeof(Shape) * shapeCount);
	world->shapeCount = 0;
}

void worldRender(World* world)
{
	int i = 0;
	int j = 0;

	for (int j = 0; j < world->image.height; j++)
	{
		for (int i = 0; i < world->image.width; i++)
		{
			Vec3 pixelCenter = {
				world->camera.pixel00Location.x + (i * world->camera.pixelDeltaU.x) + (j * world->camera.pixelDeltaV.x),
				world->camera.pixel00Location.y + (i * world->camera.pixelDeltaU.y) + (j * world->camera.pixelDeltaV.y),
				world->camera.pixel00Location.z + (i * world->camera.pixelDeltaU.z) + (j * world->camera.pixelDeltaV.z)
			};

			Vec3 rayDirection = {
				pixelCenter.x - world->camera.center.x,
				pixelCenter.y - world->camera.center.y,
				pixelCenter.z - world->camera.center.z
			};

			Ray ray = { world->camera.center, rayDirection };
			HitRecord rec = { 0 };
			worldCastRay(world, &ray, &rec);

			Vec3 pixelColor = rayColor(&ray, &rec);
			ppmImageWriteColor(&world->image, pixelColor);
		}
	}
}

void worldDestroy(World* world)
{
	unsigned int i = 0;

	for (i = 0; i < world->shapeCount; i++)
	{
		free(world->shapes[i].data);
	}

	free(world->shapes);

	cameraDestroy(&world->camera);
	ppmImageDestroy(&world->image);
}

bool worldCastRay(World* world, const Ray* ray, HitRecord* recordOut)
{
	unsigned int i = 0;
	bool isHit = false;
	double closest = (double)INFINITY;
	HitRecord tempRecord = { 0 };

	for (i = 0; i < world->shapeCount; i++)
	{
		if (world->shapes[i].hitFunc && world->shapes[i].hitFunc(&world->shapes[i], ray, 0, closest, &tempRecord))
		{
			isHit = true;
			closest = tempRecord.t;

			*recordOut = tempRecord;
		}
	}

	return isHit;
}

void worldAddSphere(World* world, shapeType type, const Vec3 center, const double radius)
{
	Sphere* sphere = (Sphere*)malloc(sizeof(Sphere));

	sphere->center.x = center.x;
	sphere->center.y = center.y;
	sphere->center.z = center.z;

	sphere->radius = radius;

	world->shapes[world->shapeCount].type = type;
	world->shapes[world->shapeCount].hitFunc = &sphereHit;
	world->shapes[world->shapeCount].data = (void*)sphere;

	world->shapeCount++;
}
