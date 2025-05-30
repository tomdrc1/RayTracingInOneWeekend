#include "ray.h"

Vec3 rayAt(const Ray* ray, const double t)
{
	Vec3 at = { 0 };

	at.x = ray->origin.x + (t * ray->direction.x);
	at.y = ray->origin.y + (t * ray->direction.y);
	at.z = ray->origin.z + (t * ray->direction.z);

	return at;
}

Vec3 rayColorSky(const Ray* ray)
{
	Vec3 color = { 0 };

	Vec3 unitDirection = vec3UnitVector(&ray->direction);
	double a = 0.5 * (unitDirection.y + 1.0);
	double colorDelta = 1.0 - a;

	color.x = colorDelta * 1.0 + a * 0.5;
	color.y = colorDelta * 1.0 + a * 0.7;
	color.z = colorDelta * 1.0 + a * 1.0;

	return color;
}

void rayRecordSetFaceFormal(const Ray* ray, HitRecord* record)
{
	record->isFrontFace = vec3Dot(&ray->direction, &record->normal) < 0;

	if (!record->isFrontFace)
	{
		record->normal.x = -record->normal.x;
		record->normal.y = -record->normal.y;
		record->normal.z = -record->normal.z;
	}
}
