#pragma once

#include <stdbool.h>

#include "vec3.h"

typedef struct Ray
{
	Vec3 origin;
	Vec3 direction;
} Ray;

bool rayHitSphere(const Vec3 center, const double radius, const Ray* ray);

Vec3 rayAt(const Ray* ray, const double t);
Vec3 rayColor(const Ray* ray);