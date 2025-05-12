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
        const Vec3 point = vec3RandomVectorConfined(-1, 1);
        const double lensq = vec3SquareLength(&point);

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

Vec3 vec3RandomInUnitDisk()
{
    while (true)
    {
        const Vec3 point = { randomDoubleConfined(-1,1), randomDoubleConfined(-1, 1), 0 };
        const double pointLength = vec3Length(&point);

        if (pointLength < 1)
        {
            return point;
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

Vec3 vec3Reflect(const Vec3* vec, const Vec3* other)
{
    const double dotProduct = vec3Dot(vec, other);

    return (Vec3) {
        vec->x - 2 * dotProduct * other->x,
        vec->y - 2 * dotProduct * other->y,
        vec->z - 2 * dotProduct * other->z
    };
}

Vec3 vec3Refract(const Vec3* vec, const Vec3* other, const double etaiOverEtat)
{
    const Vec3 ngativeVec = { -vec->x, -vec->y, -vec->z };
    const double cosTheta = fmin(vec3Dot(&ngativeVec, other), 1.0);
    const Vec3 rOutPerp = { 
        etaiOverEtat * (vec->x + (cosTheta * other->x)),
        etaiOverEtat * (vec->y + (cosTheta * other->y)),
        etaiOverEtat * (vec->z + (cosTheta * other->z)),
    };

    const double rootLength = -sqrt(fabs(1.0 - vec3SquareLength(&rOutPerp)));
    const Vec3 rOutParallel = {
        rootLength * other->x,
        rootLength * other->y,
        rootLength * other->z
    };


    return (Vec3) {
        rOutParallel.x + rOutParallel.x,
        rOutParallel.y + rOutParallel.y,
        rOutParallel.z + rOutParallel.z,
    };
}

Vec3 vec3Cross(const Vec3* vec, const Vec3* other)
{
    return (Vec3) {
        (vec->y * other->z) - (vec->z * other->y),
        (vec->z * other->x) - (vec->x * other->z),
        (vec->x * other->y) - (vec->y * other->x)
    };
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
