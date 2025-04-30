#pragma once

#include <math.h>
#include <stdbool.h>

#include "vec3.h"

typedef struct Ray
{
	Vec3 origin;
	Vec3 direction;
} Ray;

double rayHitSphere(const Vec3 center, const double radius, const Ray* ray);

Vec3 rayAt(const Ray* ray, const double t);
Vec3 rayColor(const Ray* ray);