#include "world.h"

void worldInit(World* world, const unsigned int imageWidth, const unsigned int imageHeight, const unsigned int shapeCount)
{
	randomInit();
	cameraInit(&world->camera, imageWidth, imageHeight);
	ppmImageInit(&world->image, IMAGE_NAME, imageWidth, imageHeight);

	world->shapes = (Shape*)malloc(sizeof(Shape) * shapeCount);
	world->shapeCount = 0;

	world->sampelsPerPixel = 100;
	world->pixelSampelsScale = 1.0 / (double)world->sampelsPerPixel;
}

void worldRender(World* world)
{
	int i = 0;
	int j = 0;
	int sample = 0;

	Ray ray = { 0 };
	Vec3 pixelColor = { 0 };

	for (j = 0; j < world->image.height; j++)
	{
		for (i = 0; i < world->image.width; i++)
		{
			pixelColor = (Vec3){ 0 };

			for (sample = 0; sample < world->sampelsPerPixel; sample++)
			{
				worldGenerateRay(world, i, j, &ray);

				HitRecord rec = { 0 };
				rec.isHit = worldCastRay(world, &ray, &rec);

				Vec3 tempPixelColor = rayColor(&ray, &rec);

				pixelColor.x += tempPixelColor.x;
				pixelColor.y += tempPixelColor.y;
				pixelColor.z += tempPixelColor.z;
			}


			pixelColor.x *= world->pixelSampelsScale;
			pixelColor.y *= world->pixelSampelsScale;
			pixelColor.z *= world->pixelSampelsScale;
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

	memset(world, NULL, sizeof(World));
}

void worldGenerateRay(World* world, const unsigned int i, const unsigned int j, Ray* out)
{
	Vec3 offset = {
		randomDouble() - 0.5,
		randomDouble() - 0.5,
		0.0
	};
	
	Vec3 pixelCenter = {
		world->camera.pixel00Location.x + ((i + offset.x) * world->camera.pixelDeltaU.x) + ((j + offset.y) * world->camera.pixelDeltaV.x),
		world->camera.pixel00Location.y + ((i + offset.x) * world->camera.pixelDeltaU.y) + ((j + offset.y) * world->camera.pixelDeltaV.y),
		world->camera.pixel00Location.z + ((i + offset.x) * world->camera.pixelDeltaU.z) + ((j + offset.y) * world->camera.pixelDeltaV.z)
	};

	Vec3 rayDirection = {
		pixelCenter.x - world->camera.center.x,
		pixelCenter.y - world->camera.center.y,
		pixelCenter.z - world->camera.center.z
	};

	out->origin = world->camera.center;
	out->direction = rayDirection;
}

bool worldCastRay(World* world, const Ray* ray, HitRecord* recordOut)
{
	unsigned int i = 0;
	bool isHit = false;
	double closest = (double)INFINITY;
	HitRecord tempRecord = { 0 };
	Interval interval = { 0 };

	for (i = 0; i < world->shapeCount; i++)
	{
		interval.min = 0;
		interval.max = closest;

		if (world->shapes[i].hitFunc && world->shapes[i].hitFunc(&world->shapes[i], ray, &interval, &tempRecord))
		{
			isHit = true;
			closest = tempRecord.t;

			*recordOut = tempRecord;
		}
	}

	return isHit;
}

void worldAddSphere(World* world, const Vec3 center, const double radius)
{
	Sphere* sphere = (Sphere*)malloc(sizeof(Sphere));

	sphere->center.x = center.x;
	sphere->center.y = center.y;
	sphere->center.z = center.z;

	sphere->radius = radius;

	world->shapes[world->shapeCount].hitFunc = &sphereHit;
	world->shapes[world->shapeCount].data = (void*)sphere;

	world->shapeCount++;
}
