#pragma once

#include <stdbool.h>

#include "../ray.h"

enum shapeType
{
	Sphere,
	Cube
};


typedef struct Shape {
	shapeType type;
	void* data;
	bool (*hitFunc)(const Ray* ray, const double ray_tmin, const double ray_tmax, HitRecord* recordOut);
} Shape;