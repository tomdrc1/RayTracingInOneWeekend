#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "ppmImage.h"
#include "ray.h"

#define IMAGE_NAME "image.ppm"

typedef struct Camera
{
	PPMImage image;

	Vec3 center;

	Vec3 pixelDeltaU;
	Vec3 pixelDeltaV;

	Vec3 pixel00Location;
} Camera;


void cameraInit(Camera* camera, const unsigned int imageWidth, const unsigned int imageHeight);
void cameraRender(Camera* camera);
void cameraDestroy(Camera* camera);