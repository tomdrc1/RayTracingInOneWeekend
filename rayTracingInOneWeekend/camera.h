#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <corecrt_math_defines.h>

#include "random.h"
#include "vec2.h"
#include "vec3.h"
#include "ray.h"

#define degreesToRadians(x) x * M_PI / 180.0

typedef struct Camera
{
	Vec3 center;

	Vec3 pixelDeltaU;
	Vec3 pixelDeltaV;

	Vec3 defocusDiskU;
	Vec3 defocusDiskV;

	Vec3 pixel00Location;
	unsigned int maxDepth;

	double vfov;
	double defocusAngle;
	double focusDist;

	unsigned int samplesPerPixel;
	double pixelSamplesScale;
} Camera;


void cameraInit(Camera* camera, const Vec3 lookFrom, const Vec3 lookAt, const unsigned int imageWidth, const unsigned int imageHeight);
void cameraGenerateRay(const Camera* camera, const Vec2 PixelCoordinates, Ray* rayOut);
Vec3 cameraDefocusDiskSample(const Camera* camera);
void cameraDestroy(Camera* camera);