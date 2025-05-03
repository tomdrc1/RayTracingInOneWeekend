#include "camera.h"

void cameraInit(Camera* camera, const unsigned int imageWidth, const unsigned int imageHeight)
{
	double focalLength = 1.0;
	double viewportHeight = 2.0;
	double viewportWidth = viewportHeight * ((double)imageWidth / (double)imageHeight);

	camera->center.x = 0;
	camera->center.y = 0;
	camera->center.z = 0;

	Vec3 viewportU = { viewportWidth, 0, 0 };
	Vec3 viewportV = { 0, -viewportHeight, 0 };

	camera->pixelDeltaU.x = viewportU.x / imageWidth;
	camera->pixelDeltaU.y = viewportU.y / imageWidth;
	camera->pixelDeltaU.z = viewportU.z / imageWidth;

	camera->pixelDeltaV.x = viewportV.x / imageHeight;
	camera->pixelDeltaV.y = viewportV.y / imageHeight;
	camera->pixelDeltaV.z = viewportV.z / imageHeight;

	Vec3 viewportUpperLeft = {
		camera->center.x - (viewportU.x / 2) - (viewportV.x / 2),
		camera->center.y - (viewportU.y / 2) - (viewportV.y / 2),
		camera->center.z - focalLength - (viewportU.z / 2) - (viewportV.z / 2)
	};

	camera->pixel00Location.x = viewportUpperLeft.x + 0.5 * (camera->pixelDeltaU.x + camera->pixelDeltaV.x);
	camera->pixel00Location.y = viewportUpperLeft.y + 0.5 * (camera->pixelDeltaU.y + camera->pixelDeltaV.y);
	camera->pixel00Location.z = viewportUpperLeft.z + 0.5 * (camera->pixelDeltaU.z + camera->pixelDeltaV.z);
}

void cameraDestroy(Camera* camera)
{
	memset(camera, NULL, sizeof(Camera));
}
