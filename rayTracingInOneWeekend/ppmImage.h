#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "vec3.h"

typedef struct PPMImage
{
	FILE* imageFile;
	unsigned short height;
	unsigned short width;
} PPMImage;

void ppmImageInit(PPMImage* image, const char* path, const unsigned short width, const unsigned short height);
void ppmImageGenerateData(PPMImage* image);
void ppmImageWriteColour(PPMImage* image, Vec3 pixel);
void ppmImageDestroy(PPMImage* image);