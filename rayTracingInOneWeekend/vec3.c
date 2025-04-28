#include "vec3.h"

double vec3Dot(const Vec3* vec, const Vec3* other)
{
    return vec->x * other->x
        + vec->y * other->y
        + vec->z * other->z;
}

void vec3Print(const Vec3* vec)
{
	printf("X: %f, Y: %f, Z: %f\n", vec->x, vec->y, vec->z);
}
