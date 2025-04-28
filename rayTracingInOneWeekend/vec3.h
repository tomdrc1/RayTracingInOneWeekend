#pragma once

#include <stdio.h>

typedef struct Vec3
{
	double x;
	double y;
	double z;
} Vec3;

double vec3Dot(const Vec3* vec, const Vec3* other);
void vec3Print(const Vec3* vec);