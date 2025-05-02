#pragma once

#include <stdbool.h>
#include <math.h>

#include "../ray.h"
#include "../vec3.h"
#include "shape.h"

typedef struct Sphere
{
	Vec3 center;
	double radius;
} Sphere;

bool sphereHit(const Shape* shape, const Ray* ray, const double ray_tmin, const double ray_tmax, HitRecord* recordOut);