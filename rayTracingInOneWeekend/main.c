#include <stdio.h>

#include "camera.h"

#define ASPECT_RATIO (16.0 / 9.0)

int main(int argc, char** argv)
{
	const unsigned int imageWidth = 400;
	int imageHeight = (int)((double)imageWidth / ASPECT_RATIO);
	imageHeight = (imageHeight < 1) ? 1 : imageHeight;

	Camera cam;

	cameraInit(&cam, imageWidth, imageHeight);
	cameraRender(&cam);
	cameraDestroy(&cam);
	
	return 0;
}