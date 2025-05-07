#include "metal.h"

void metalInit(Material* material, Vec3 albedo)
{
	Metal* metal = (Metal*)malloc(sizeof(Metal));

	metal->albedo = albedo;

	material->materialData = (void*)metal;
	material->scatterFunc = &metalScatter;
}

void metalScatter(const Material* material, const Ray* rayIn, const HitRecord* rec, Vec3* attenuation, Ray* scattered)
{
	const Metal* metal = (Metal*)material->materialData;

	Vec3 reflected = vec3Reflect(&rayIn->direction, &rec->normal);

	scattered->direction = reflected;
	scattered->origin = rec->point;
	*attenuation = metal->albedo;
}
