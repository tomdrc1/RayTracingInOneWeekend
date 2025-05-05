#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "random.h"
#include "vec2.h"
#include "vec3.h"
#include "ray.h"

typedef struct Camera
{
	Vec3 center;

	Vec3 pixelDeltaU;
	Vec3 pixelDeltaV;

	Vec3 pixel00Location;
	unsigned int maxDepth;
} Camera;


void cameraInit(Camera* camera, const unsigned int imageWidth, const unsigned int imageHeight);
void cameraGenerateRay(const Camera* camera, const Vec2 PixelCoordinates, Ray* rayOut);
void cameraDestroy(Camera* camera);