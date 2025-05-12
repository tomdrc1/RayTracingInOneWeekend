#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "camera.h"
#include "ppmImage.h"
#include "ray.h"
#include "interval.h"

#include "vec3.h"
#include "vec2.h"

#include "shapes/sphere.h"

#include "materials/lambertian.h"
#include "materials/metal.h"
#include "materials/dielectric.h"

#define IMAGE_NAME "image.ppm"

typedef struct World
{
	PPMImage image;
	Camera camera;

	Shape* shapes;
	unsigned int shapeCount;
	unsigned int maxShapes;
} World;

void worldInit(World* world, const Vec3 lookFrom, const Vec3 lookAt, const unsigned int imageWidth, const unsigned int imageHeight, const unsigned int shapeCount);
void worldRender(World* world);
void worldDestroy(World* world);

void worldCastRayAntialiasing(const World* world, const Vec2 pixelCoordinates, Vec3* pixelColorOut);

bool worldCastRay(World* world, const Ray* ray, HitRecord* recordOut);
void worldAddSphere(World* world, const Vec3 center, const double radius, const Material material);