#include "ray.h"

double rayHitSphere(const Vec3 center, const double radius, const Ray* ray)
{
	Vec3 oc = {
		center.x - ray->origin.x,
		center.y - ray->origin.y,
		center.z - ray->origin.z
	};

	double a = vec3SquareLength(&ray->direction);
	double h = vec3Dot(&ray->direction, &oc);
	double c = vec3SquareLength(&oc) - radius * radius;
	double discriminant = h * h - a * c;

	if (discriminant < 0)
	{
		return -1.0;
	}
	else
	{
		return (h - sqrt(discriminant)) / a;
	}
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

	double t = rayHitSphere(sphere, 0.5, ray);
	if (t > 0.0)
	{
		Vec3 at = rayAt(ray, t);
		Vec3 N = {
			at.x - sphere.x,
			at.y - sphere.y,
			at.z - sphere.z
		};

		color.x = 0.5 * (N.x + 1);
		color.y = 0.5 * (N.y + 1);
		color.z = 0.5 * (N.z + 1);

		return color;
	}

	double a = 0.5 * (ray->direction.y + 1.0);
	double colorDelta = 1.0 - a;

	color.x = colorDelta * 1.0 + a * 0.5;
	color.y = colorDelta * 1.0 + a * 0.7;
	color.z = colorDelta * 1.0 + a * 1.0;

	return color;
}
