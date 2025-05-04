#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "vec3.h"
#include "interval.h"

static const Interval PPM_IMAGE_INTENSITY = { 0.000, 0.999 };

typedef struct PPMImage
{
	FILE* imageFile;
	unsigned short height;
	unsigned short width;
} PPMImage;

void ppmImageInit(PPMImage* image, const char* path, const unsigned short width, const unsigned short height);
void ppmImageWriteColor(PPMImage* image, Vec3 pixelColor);
void ppmImageDestroy(PPMImage* image);