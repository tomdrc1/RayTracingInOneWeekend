#include <stdio.h>

#include "ppmImage.h"
#include "ray.h"

#define IMAGE_NAME "image.ppm"

int main(int argc, char** argv)
{
	PPMImage image;

	printf("Writing data to image %s\n", IMAGE_NAME);

	ppmImageInit(&image, IMAGE_NAME, 480, 480);
	ppmImageGenerateData(&image);
	ppmImageDestroy(&image);

	Ray ray = { 0 };

	ray.origin.x = 0;
	ray.origin.y = 0;
	ray.origin.z = 0;

	ray.direction.x = 0.5;
	ray.direction.y = 0.5;
	ray.direction.z = 0;

	Vec3 res = rayAt(&ray, 2.5);

	vec3Print(&res);
	
	return 0;
}