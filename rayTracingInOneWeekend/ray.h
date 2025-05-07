#pragma once

#include <math.h>
#include <stdbool.h>

#include "materials/material.h"
#include "vec3.h"

typedef struct HitRecord
{
    Material material;
    Vec3 point;
    Vec3 normal;
    double t;
    bool isFrontFace;
    bool isHit;
} HitRecord;

typedef struct Ray
{
	Vec3 origin;
	Vec3 direction;
} Ray;

Vec3 rayAt(const Ray* ray, const double t);
Vec3 rayColor(const Ray* ray, const HitRecord* hitRecord);

void rayRecordSetFaceFormal(const Ray* ray, HitRecord* record);