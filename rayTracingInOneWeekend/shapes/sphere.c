#include "sphere.h"

bool sphereHit(const Shape* shape, const Ray* ray, const Interval* interval, HitRecord* recordOut)
{
    Sphere* sphere = (Sphere*)shape->data;

	Vec3 oc = {
		sphere->center.x - ray->origin.x,
		sphere->center.y - ray->origin.y,
		sphere->center.z - ray->origin.z
	};

	double a = vec3SquareLength(&ray->direction);
	double h = vec3Dot(&ray->direction, &oc);
	double c = vec3SquareLength(&oc) - sphere->radius * sphere->radius;
	double discriminant = h * h - a * c;

	if (discriminant <= 0)
	{
		return false;
	}

	double sqrtd = sqrt(discriminant);
	double root = (h - sqrtd) / a;

	if (!intervalSurrounds(interval, root))
	{
		root = (h + sqrtd) / a;
		if (!intervalSurrounds(interval, root))
		{
			return false;
		}
	}

	recordOut->t = root;
	recordOut->point = rayAt(ray, recordOut->t);

	recordOut->normal = (Vec3){ 
		(recordOut->point.x - sphere->center.x) / sphere->radius,
		(recordOut->point.y - sphere->center.y) / sphere->radius,
		(recordOut->point.z - sphere->center.z) / sphere->radius,
	};
	rayRecordSetFaceFormal(ray, recordOut);
	recordOut->material = sphere->material;

	return true;
}