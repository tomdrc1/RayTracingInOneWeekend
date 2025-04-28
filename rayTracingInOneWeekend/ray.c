#include "ray.h"

Vec3 rayAt(const Ray* ray, const double t)
{
	Vec3 at = { 0 };

	at.x = ray->origin.x + (t * ray->direction.x);
	at.y = ray->origin.y + (t * ray->direction.y);
	at.z = ray->origin.z + (t * ray->direction.z);

	return at;
}
