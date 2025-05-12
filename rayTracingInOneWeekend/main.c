#include <stdio.h>

#include "world.h"

#define SHAPE_COUNT (22*22) + 3
#define ASPECT_RATIO (16.0 / 9.0)

int main(int argc, char** argv)
{
	const unsigned int imageWidth = 1200;
	int imageHeight = (int)((double)imageWidth / ASPECT_RATIO);
	imageHeight = (imageHeight < 1) ? 1 : imageHeight;

	World world;

	const Vec3 lookFrom = { 13, 2, 3 };
	const Vec3 lookAt = { 0, 0, 0 };

	worldInit(&world, lookFrom, lookAt, imageWidth, imageHeight, SHAPE_COUNT);

	Material ground = { 0 };

	lambertianInit(&ground, (Vec3) { 0.5, 0.5, 0.5 });
	worldAddSphere(&world, (Vec3){ 0, -1000, 0 }, 1000, ground);

	int a = 0;
	int b = 0;

	for (a = -11; a < 11; a++)
	{
		for (b = -11; b < 11; b++)
		{
			const Vec3 center = {
				a + (0.9 * randomDouble()),
				0.2,
				b + (0.9 * randomDouble())
			};

			const Vec3 centerBound = {
				center.x - 4,
				center.y - 0.2,
				center.z - 0
			};
			
			if (vec3Length(&centerBound) > 0.9)
			{
				const double materialChoice = randomDouble();
				Material mat = { 0 };

				if (materialChoice < 0.8)
				{
					const Vec3 color = vec3RandomVectorConfined(-1, 1);
					lambertianInit(&mat, color);
				}
				else if (materialChoice < 0.95)
				{
					const Vec3 color = vec3RandomVectorConfined(0.5, 1);
					metalInit(&mat, color);
				}
				else
				{
					const Vec3 color = { 1.0, 1.0, 1.0 };
					dielectricInit(&mat, color, 1.5);
				}

				worldAddSphere(&world, center, 0.2, mat);
			}
		}
	}
	
	Material material1 = { 0 };
	Material material2 = { 0 };
	Material material3 = { 0 };

	dielectricInit(&material1, (Vec3) { 1.0, 1.0, 1.0 }, 1.5);
	lambertianInit(&material2, (Vec3) {0.5, 0.2, 0.1});
	metalInit(&material3, (Vec3) { 0.7, 0.6, 0.5 });

	worldAddSphere(&world, (Vec3) { 0, 1, 0 }, 1.0, material1);
	worldAddSphere(&world, (Vec3) { -4, 1, 0 }, 1.0, material2);
	worldAddSphere(&world, (Vec3) { 4, 1, 0 }, 1.0, material3);

	worldRender(&world);

	worldDestroy(&world);
	
	return 0;
}