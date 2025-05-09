#include "lambertian.h"

void lambertianInit(Material* material, const Vec3 albedo)
{
	Lambertian* lambertian = (Lambertian*)malloc(sizeof(Lambertian));

	lambertian->albedo = albedo;

	material->materialData = (void*)lambertian;
	material->scatterFunc = &lambertianScatter;
}

void lambertianScatter(const Material* material, const Ray* rayIn, const HitRecord* rec, Vec3* attenuation, Ray* scattered)
{
	const Lambertian* lambertian = (Lambertian*)material->materialData;
	const Vec3 randomDirection = vec3RandomUnitVector();

	scattered->direction.x = rec->normal.x + randomDirection.x;
	scattered->direction.y = rec->normal.y + randomDirection.y;
	scattered->direction.z = rec->normal.z + randomDirection.z;

	if (vec3NearZero(&scattered->direction))
	{
		scattered->direction = rec->normal;
	}

	scattered->origin = rec->point;
	
	*attenuation = lambertian->albedo;
}
