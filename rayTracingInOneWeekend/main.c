#include <stdio.h>

#include "world.h"

#define ASPECT_RATIO (16.0 / 9.0)

int main(int argc, char** argv)
{
	const unsigned int imageWidth = 400;
	int imageHeight = (int)((double)imageWidth / ASPECT_RATIO);
	imageHeight = (imageHeight < 1) ? 1 : imageHeight;

	World world;

	worldInit(&world, imageWidth, imageHeight);

	worldAddSphere(&world, SHAPE_SPHERE, (Vec3) { 0, 0, -1 }, 0.5);
	worldRender(&world);

	worldDestroy(&world);
	
	return 0;
}