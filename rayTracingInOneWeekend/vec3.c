#include "vec3.h"

double vec3Dot(const Vec3* vec, const Vec3* other)
{
    return vec->x * other->x
        + vec->y * other->y
        + vec->z * other->z;
}

double vec3SquareLength(const Vec3* vec)
{
    return (vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z);
}

Vec3 vec3RandomVectorConfined(const double min, const double max)
{
    return (Vec3) {
        randomDoubleConfined(min, max),
        randomDoubleConfined(min, max),
        randomDoubleConfined(min, max)
    };
}

Vec3 vec3RandomUnitVector()
{
    while (true)
    {
        Vec3 point = vec3RandomVectorConfined(-1, 1);

        double lensq = vec3SquareLength(&point);
        if (1e-160 < lensq && lensq <= 1)
        {
            const double lensqRoot = sqrt(lensq);

            return (Vec3) {
                point.x / lensqRoot,
                point.y / lensqRoot,
                point.z / lensqRoot
            };
        }
    }
}

Vec3 randomOnHemisphere(const Vec3* normal)
{
    Vec3 onUnitSphere = vec3RandomUnitVector();

    if (vec3Dot(&onUnitSphere, normal) <= 0.0)
    {
        onUnitSphere.x = -onUnitSphere.x;
        onUnitSphere.y = -onUnitSphere.y;
        onUnitSphere.z = -onUnitSphere.z;
    }

    return onUnitSphere;
}

void vec3Print(const Vec3* vec)
{
	printf("X: %f, Y: %f, Z: %f\n", vec->x, vec->y, vec->z);
}
