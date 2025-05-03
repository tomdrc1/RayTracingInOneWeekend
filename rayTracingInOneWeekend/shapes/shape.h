#pragma once

#include <stdbool.h>

#include "../vec3.h"

struct Ray;
struct HitRecord;

typedef enum shapeType 
{ 
	SHAPE_SPHERE = 1, 
	SHAPE_CUBE 
} shapeType;

typedef struct Shape
{
	shapeType type;
	void* data;
	bool (*hitFunc)(const struct Shape*, const struct Ray*, const double, const double, struct HitRecord*);
} Shape;
