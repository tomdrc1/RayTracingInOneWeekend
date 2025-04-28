#include "ray.h"

Vec3 rayAt(const Ray* ray, const double t)
{
	Vec3 at = { 0 };

	at.x = ray->origin.x + (t * ray->direction.x);
	at.y = ray->origin.y + (t * ray->direction.y);
	at.z = ray->origin.z + (t * ray->direction.z);

	return at;
}

Vec3 rayColor(const Ray* ray)
{
	Vec3* direction = &ray->direction;

	double a = 0.5 * (direction->y + 1.0);
	double colorDelta = 1.0 - a;

	Vec3 color = {
		colorDelta * 1.0 + a * 0.5,
		colorDelta * 1.0 + a * 0.7,
		colorDelta * 1.0 + a * 1.0
	};

	return color;
}
