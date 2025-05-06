#pragma once

#include <stdbool.h>

#include "../vec3.h"

struct Ray;
struct HitRecord;

typedef struct Material
{
	void* materialData;
	bool (*scatterFunc)(const struct Ray* rayIn, const struct HitRecord* rec, Vec3* color, struct Ray* rayOut);
} Material;