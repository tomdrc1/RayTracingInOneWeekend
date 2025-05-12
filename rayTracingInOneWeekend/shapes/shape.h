#pragma once

#include <stdbool.h>

#include "../materials/material.h"
#include "../vec3.h"

struct Ray;
struct HitRecord;
struct Interval;

typedef struct Shape
{
	Material material;
	void* data;
	bool (*hitFunc)(const struct Shape*, const struct Ray*, const struct Ineravl*, struct HitRecord*);
} Shape;
