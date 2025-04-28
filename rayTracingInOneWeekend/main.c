#include <stdio.h>

#include "ppmImage.h"

#define IMAGE_NAME "image.ppm"

int main(int argc, char** argv)
{
	PPMImage image;

	printf("Writing data to image %s\n", IMAGE_NAME);

	ppmImageInit(&image, IMAGE_NAME, 480, 480);
	ppmImageGenerateData(&image);
	ppmImageDestroy(&image);

	return 0;
}