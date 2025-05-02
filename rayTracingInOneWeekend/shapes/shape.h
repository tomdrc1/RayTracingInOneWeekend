#pragma once

#include <stdbool.h>

#include "../ray.h"

typedef enum shapeType { SHAPE_SPHERE, SHAPE_CUBE } shapeType;

typedef struct Shape
{
	shapeType type;
	void* data;
	bool (*hitFunc)(const struct Shape*, const Ray*, const double, const double, HitRecord*);
} Shape;
