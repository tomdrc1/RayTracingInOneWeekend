#pragma once

#include "vec3.h"

typedef struct Ray
{
	Vec3 origin;
	Vec3 direction;
} Ray;

Vec3 rayAt(const Ray* ray, const double t);
Vec3 rayColor(const Ray* ray);