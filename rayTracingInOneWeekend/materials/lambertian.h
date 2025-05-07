#pragma once

#include <stdbool.h>

#include "material.h"
#include "../vec3.h"
#include "../ray.h"

typedef struct Lambertian
{
	Vec3 albedo;
} Lambertian;

void lambertianScatter(const Material* material, const Ray* rayIn, const HitRecord* rec, Vec3* attenuation, Ray* scattered);