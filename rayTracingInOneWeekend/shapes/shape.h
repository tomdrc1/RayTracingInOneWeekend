#pragma once

#include <stdbool.h>

#include "../vec3.h"

struct Ray;
struct HitRecord;

typedef struct Shape
{
	void* data;
	bool (*hitFunc)(const struct Shape*, const struct Ray*, const double, const double, struct HitRecord*);
} Shape;
