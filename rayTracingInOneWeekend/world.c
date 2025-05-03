#include "world.h"

void worldInit(World* world, const unsigned int imageWidth, const unsigned int imageHeight)
{
	cameraInit(&world->camera, imageWidth, imageHeight);
	ppmImageInit(&world->image, IMAGE_NAME, imageWidth, imageHeight);

	world->shapes = (Shape*)malloc(sizeof(Shape));
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

			Vec3 pixelColor = rayColor(&ray, &world->shapes[0]);
			ppmImageWriteColor(&world->image, pixelColor);
		}
	}
}

void worldDestroy(World* world)
{
	free(world->shapes[0].data);
	free(world->shapes);

	cameraDestroy(&world->camera);
	ppmImageDestroy(&world->image);
}

void worldAddSphere(World* world, shapeType type, const Vec3 center, const double radius)
{
	Sphere* sphere = (Sphere*)malloc(sizeof(Sphere));

	sphere->center.x = center.x;
	sphere->center.y = center.y;
	sphere->center.z = center.z;

	sphere->radius = radius;

	world->shapes[0].type = type;
	world->shapes[0].hitFunc = &sphereHit;
	world->shapes[0].data = (void*)sphere;
}
