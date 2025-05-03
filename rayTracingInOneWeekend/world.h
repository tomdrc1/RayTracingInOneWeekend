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
} World;

void worldInit(World* world, const unsigned int imageWidth, const unsigned int imageHeight);
void worldRender(World* world);
void worldDestroy(World* world);

void worldAddSphere(World* world, shapeType type, const Vec3 center, const double radius);