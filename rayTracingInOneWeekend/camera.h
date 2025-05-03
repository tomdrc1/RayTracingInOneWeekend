#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vec3.h"

typedef struct Camera
{
	Vec3 center;

	Vec3 pixelDeltaU;
	Vec3 pixelDeltaV;

	Vec3 pixel00Location;
} Camera;


void cameraInit(Camera* camera, const unsigned int imageWidth, const unsigned int imageHeight);
void cameraDestroy(Camera* camera);