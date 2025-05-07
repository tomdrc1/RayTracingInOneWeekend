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

double vec3Length(const Vec3* vec)
{
    return sqrt(vec3SquareLength(vec));
}

Vec3 vec3UnitVector(const Vec3* vec)
{
    double vecLength = vec3Length(vec);

    return (Vec3) {
        vec->x / vecLength,
        vec->y / vecLength,
        vec->z / vecLength
    };
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

Vec3 vec3RandomOnHemisphere(const Vec3* normal)
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

bool vec3NearZero(const Vec3* vec)
{
    const double s = 1e-8;
    return (fabs(vec->x) < s) && (fabs(vec->y) < s) && (fabs(vec->z) < s);
}

void vec3Print(const Vec3* vec)
{
	printf("X: %f, Y: %f, Z: %f\n", vec->x, vec->y, vec->z);
}
