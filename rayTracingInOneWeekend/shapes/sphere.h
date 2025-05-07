#pragma once

#include <stdbool.h>
#include <math.h>

#include "shape.h"
#include "../interval.h"
#include "../ray.h"

typedef struct Sphere
{
	Vec3 center;
	double radius;
} Sphere;

bool sphereHit(const Shape* shape, const Ray* ray, const Interval* interval, HitRecord* recordOut);