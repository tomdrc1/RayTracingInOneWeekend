#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "random.h"

typedef struct Vec3
{
	double x;
	double y;
	double z;
} Vec3;

double vec3Dot(const Vec3* vec, const Vec3* other);
double vec3SquareLength(const Vec3* vec);
double vec3Length(const Vec3* vec);

Vec3 vec3UnitVector(const Vec3* vec);
Vec3 vec3RandomVectorConfined(const double min, const double max);
Vec3 vec3RandomUnitVector();
Vec3 vec3RandomOnHemisphere(const Vec3* normal);

bool vec3NearZero(const Vec3* vec);

void vec3Print(const Vec3* vec);