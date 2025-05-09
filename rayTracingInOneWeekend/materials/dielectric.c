#include "dielectric.h"

void dielectricInit(Material* material, Vec3 albedo, const double refractionIndex)
{
	Dielectric* dielectric = (Dielectric*)malloc(sizeof(Dielectric));

	dielectric->albedo = albedo;
	dielectric->refractionIndex = refractionIndex;

	material->materialData = (void*)dielectric;
	material->scatterFunc = &dielectricScatter;
}

void dielectricScatter(const Material* material, const Ray* rayIn, const HitRecord* rec, Vec3* attenuation, Ray* scattered)
{
	const Dielectric* dielectric = (Dielectric*)material->materialData;

	const double ri = rec->isFrontFace ? (1.0 / dielectric->refractionIndex) : dielectric->refractionIndex;
	*attenuation = dielectric->albedo;

	Vec3 unitDirection = vec3UnitVector(&rayIn->direction);
	Vec3 refracted = vec3Refract(&unitDirection, &rec->normal, ri);

	scattered->origin = rec->point;
	scattered->direction = refracted;
}
