#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "camera.h"
#include "ppmImage.h"
#include "ray.h"
#include "shapes/sphere.h"

#define IMAGE_NAME "image.ppm"

typedef struct World
{
	PPMImage image;
	Camera camera;

	Shape* shapes;
	unsigned int shapeCount;
} World;

void worldInit(World* world, const unsigned int imageWidth, const unsigned int imageHeight, const unsigned int shapeCount);
void worldRender(World* world);
void worldDestroy(World* world);

bool worldCastRay(World* world, const Ray* ray, HitRecord* recordOut);
void worldAddSphere(World* world, const Vec3 center, const double radius);