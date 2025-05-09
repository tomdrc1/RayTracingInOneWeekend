#include <stdio.h>

#include "world.h"

#define ASPECT_RATIO (16.0 / 9.0)

int main(int argc, char** argv)
{
	const unsigned int imageWidth = 400;
	int imageHeight = (int)((double)imageWidth / ASPECT_RATIO);
	imageHeight = (imageHeight < 1) ? 1 : imageHeight;

	World world;

	worldInit(&world, imageWidth, imageHeight, 10);

	Material ground = { 0 };
	Material center = { 0 };
	Material left = { 0 };
	Material right = { 0 };

	lambertianInit(&ground, (Vec3) { 0.8, 0.8, 0.0 });
	lambertianInit(&center, (Vec3) { 0.1, 0.2, 0.5 });
	metalInit(&left, (Vec3) { 0.8, 0.8, 0.8 });
	dielectricInit(&right, (Vec3) { 0.8, 0.6, 0.2 }, 1.5);

	worldAddSphere(&world, (Vec3){ 0, 0, -1.2 }, 0.5, center);
	worldAddSphere(&world, (Vec3){ 0, -100.5, -1 }, 100, ground);
	worldAddSphere(&world, (Vec3) { -1, 0, -1 }, 0.5, left);
	worldAddSphere(&world, (Vec3) { 1, 0, -1 }, 0.5, right);
	worldRender(&world);

	worldDestroy(&world);
	
	return 0;
}