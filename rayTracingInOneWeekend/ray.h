#pragma once

#include <math.h>
#include <stdbool.h>

#include "vec3.h"
#include "shapes/shape.h"

typedef struct HitRecord
{
    Vec3 point;
    Vec3 normal;
    double t;
} HitRecord;

typedef struct Ray
{
	Vec3 origin;
	Vec3 direction;
} Ray;

Vec3 rayAt(const Ray* ray, const double t);
Vec3 rayColor(const Ray* ray, const Shape* shape);