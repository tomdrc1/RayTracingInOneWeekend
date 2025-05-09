#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "material.h"
#include "../vec3.h"
#include "../ray.h"

typedef struct Dielectric
{
	double refractionIndex;
	Vec3 albedo;
} Dielectric;

void dielectricInit(Material* material, Vec3 albedo, const double refractionIndex);

void dielectricScatter(const Material* material, const Ray* rayIn, const HitRecord* rec, Vec3* attenuation, Ray* scattered);