#include <stdio.h>

#include "ppmImage.h"
#include "ray.h"

#define IMAGE_NAME "image.ppm"
#define ASPECT_RATIO (16.0 / 9.0)

int main(int argc, char** argv)
{
	PPMImage image;

	const int imageWidth = 400;
	int imageHeight = (int)((double)imageWidth / ASPECT_RATIO);
	imageHeight = (imageHeight < 1) ? 1 : imageHeight;

	printf("Writing data to image %s\n", IMAGE_NAME);

	double focalLength = 1.0;
	double viewportHeight = 2.0;
	double viewportWidth = viewportHeight * ((double)imageWidth / (double)imageHeight);
	Vec3 cameraCenter = { 0, 0, 0 };

	Vec3 viewportU = { viewportWidth, 0, 0 };
	Vec3 viewportV = {0, -viewportHeight, 0};

	Vec3 pixelDeltaU = { viewportU.x / imageWidth, viewportU.y / imageWidth, viewportU.z / imageWidth };
	Vec3 pixelDeltaV = { viewportV.x / imageHeight, viewportV.y / imageHeight, viewportV.z / imageHeight };

	Vec3 viewportUpperLeft = {
		cameraCenter.x - (viewportU.x / 2) - (viewportV.x / 2),
		cameraCenter.y - (viewportU.y / 2) - (viewportV.y / 2),
		cameraCenter.z - focalLength - (viewportU.z / 2) - (viewportV.z / 2)
	};

	Vec3 pixel00Location = {
		viewportUpperLeft.x + 0.5 * (pixelDeltaU.x + pixelDeltaV.x),
		viewportUpperLeft.y + 0.5 * (pixelDeltaU.y + pixelDeltaV.y),
		viewportUpperLeft.z + 0.5 * (pixelDeltaU.z + pixelDeltaV.z)
	};

	ppmImageInit(&image, IMAGE_NAME, imageWidth, imageHeight);

	const int width = image.width;
	const int height = image.height;
	Vec3 pixelColor = { 0, 0, 0 };

	fprintf(image.imageFile, "P3\n%d %d\n255\n", width, height);

	for (int j = 0; j < width; j++)
	{
		for (int i = 0; i < height; i++)
		{
			Vec3 pixelCenter = {
				pixel00Location.x + (i * pixelDeltaU.x) + (j * pixelDeltaV.x),
				pixel00Location.y + (i * pixelDeltaU.y) + (j * pixelDeltaV.y),
				pixel00Location.z + (i * pixelDeltaU.z) + (j * pixelDeltaV.z)
			};

			Vec3 rayDirection = {
				pixelCenter.x - cameraCenter.x,
				pixelCenter.y - cameraCenter.y,
				pixelCenter.z - cameraCenter.z
			};

			Ray ray = { cameraCenter, rayDirection };

			pixelColor = rayColor(&ray);

			ppmImageWriteColour(&image, pixelColor);
		}
	}

	ppmImageDestroy(&image);
	
	return 0;
}