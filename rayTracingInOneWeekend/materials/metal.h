#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "material.h"
#include "../vec3.h"
#include "../ray.h"

typedef struct Metal
{
	Vec3 albedo;
} Metal;

void metalInit(Material* material, const Vec3 albedo);

void metalScatter(const Material* material, const Ray* rayIn, const HitRecord* rec, Vec3* attenuation, Ray* scattered);