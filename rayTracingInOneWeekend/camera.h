#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "ppmImage.h"
#include "ray.h"

#define IMAGE_NAME "image.ppm"
#define ASPECT_RATIO (16.0 / 9.0)

typedef struct Camera
{
	PPMImage image;

	Vec3 center;

	Vec3 pixelDeltaU;
	Vec3 pixelDeltaV;

	Vec3 pixel00Location;
} Camera;


void cameraInit(Camera* camera, const unsigned int imageWidth);
void cameraRender(Camera* camera);
void cameraDestroy(Camera* camera);