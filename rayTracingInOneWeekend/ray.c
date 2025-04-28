#include "ray.h"

bool rayHitSphere(const Vec3 center, const double radius, const Ray* ray)
{
	Vec3 oc = {
		center.x - ray->origin.x,
		center.y - ray->origin.y,
		center.z - ray->origin.z
	};

	double a = vec3Dot(&ray->direction, &ray->direction);
	double b = -2.0 * vec3Dot(&ray->direction, &oc);
	double c = vec3Dot(&oc,& oc) - radius * radius;
	double discriminant = b * b - 4.0 * a * c;

	return (discriminant >= 0);
}

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
	Vec3 color = { 0 };
	Vec3 sphere = { 0, 0, -1};

	if (rayHitSphere(sphere, 0.5, ray))
	{
		color.x = 1;

		return color;
	}

	double a = 0.5 * (ray->direction.y + 1.0);
	double colorDelta = 1.0 - a;

	color.x = colorDelta * 1.0 + a * 0.5;
	color.y = colorDelta * 1.0 + a * 0.7;
	color.z = colorDelta * 1.0 + a * 1.0;

	return color;
}
