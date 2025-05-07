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

	Vec3 pixelColor = { 0 };

	for (j = 0; j < world->image.height; j++)
	{
		printf("\rScanlines remaining: %d \n", (world->image.height - j));
		for (i = 0; i < world->image.width; i++)
		{
			pixelColor = (Vec3){ 0 };
			worldCastRayAntialiasing(world, (Vec2) { i, j }, &pixelColor);

			pixelColor.x *= world->pixelSampelsScale;
			pixelColor.y *= world->pixelSampelsScale;
			pixelColor.z *= world->pixelSampelsScale;

			pixelColor.x = linearToGamma(pixelColor.x);
			pixelColor.y = linearToGamma(pixelColor.y);
			pixelColor.z = linearToGamma(pixelColor.z);
			ppmImageWriteColor(&world->image, pixelColor);
		}
	}
}

void worldDestroy(World* world)
{
	unsigned int i = 0;

	for (i = 0; i < world->shapeCount; i++)
	{
		free(world->shapes[i].material.materialData);
		free(world->shapes[i].data);
	}

	free(world->shapes);

	cameraDestroy(&world->camera);
	ppmImageDestroy(&world->image);

	memset(world, NULL, sizeof(World));
}

void worldCastRayAntialiasing(const World* world, const Vec2 pixelCoordinates, Vec3* pixelColorOut)
{
	int i = 0;
	Ray ray = { 0 };
	HitRecord rec = { 0 };
	int depth = 0;

	Vec3 currentPixelColor = { 0 };
	Vec3 tempPixelColor = { 0 };

	for (i = 0; i < world->sampelsPerPixel; i++)
	{
		cameraGenerateRay(&world->camera, pixelCoordinates, &ray);
		depth = world->camera.maxDepth;
	
		tempPixelColor = (Vec3){ 1.0, 1.0, 1.0 };

		do
		{
			rec = (HitRecord){ 0 };
			rec.isHit = worldCastRay(world, &ray, &rec);
			
			currentPixelColor = (Vec3){ 0 };
			if (rec.isHit)
			{
				rec.material.scatterFunc(&rec.material, &ray, &rec, &currentPixelColor, &ray);
			}
			else
			{
				currentPixelColor = rayColorSky(&ray);
			}

			tempPixelColor.x *= currentPixelColor.x;
			tempPixelColor.y *= currentPixelColor.y;
			tempPixelColor.z *= currentPixelColor.z;
		} while (rec.isHit && depth--);

		pixelColorOut->x += tempPixelColor.x;
		pixelColorOut->y += tempPixelColor.y;
		pixelColorOut->z += tempPixelColor.z;
	}
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
		interval.min = 0.001;
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

void worldAddSphere(World* world, const Vec3 center, const double radius, const Material material)
{
	Sphere* sphere = (Sphere*)malloc(sizeof(Sphere));

	sphere->center.x = center.x;
	sphere->center.y = center.y;
	sphere->center.z = center.z;

	sphere->radius = radius;

	world->shapes[world->shapeCount].hitFunc = &sphereHit;
	world->shapes[world->shapeCount].data = (void*)sphere;
	world->shapes[world->shapeCount].material = material;

	world->shapeCount++;
}
