#include "camera.h"

void cameraInit(Camera* camera, const unsigned int imageWidth, const unsigned int imageHeight)
{
	camera->lookFrom = (Vec3){ -2, 2, 1 };
	camera->lookAt = (Vec3){ 0, 0, -1 };
	camera->vUp = (Vec3){ 0, 1, 0 };
	camera->center = camera->lookFrom;

	camera->vfov = 90;

	const Vec3 focal = {
		camera->lookFrom.x - camera->lookAt.x,
		camera->lookFrom.y - camera->lookAt.y,
		camera->lookFrom.z - camera->lookAt.z
	};

	const double theta = camera->vfov * M_PI / 180.0;
	const double h = tan(theta / 2.0);
	const double focalLength = vec3Length(&focal);
	const double viewportHeight = 2.0 * h * focalLength;
	const double viewportWidth = viewportHeight * ((double)imageWidth / (double)imageHeight);


	const Vec3 w = vec3UnitVector(&focal);
	const Vec3 wCross = vec3Cross(&camera->vUp, &w);

	const Vec3 u = vec3UnitVector(&wCross);
	const Vec3 v = vec3Cross(&w, &u);

	const Vec3 viewportU = { viewportWidth * u.x, viewportWidth * u.y, viewportWidth * u.z };
	const Vec3 viewportV = { viewportHeight * -v.x, viewportHeight * -v.y, viewportHeight * -v.z };

	camera->pixelDeltaU.x = viewportU.x / imageWidth;
	camera->pixelDeltaU.y = viewportU.y / imageWidth;
	camera->pixelDeltaU.z = viewportU.z / imageWidth;

	camera->pixelDeltaV.x = viewportV.x / imageHeight;
	camera->pixelDeltaV.y = viewportV.y / imageHeight;
	camera->pixelDeltaV.z = viewportV.z / imageHeight;


	const Vec3 wMulFocalLength = {
		w.x * focalLength,
		w.y * focalLength,
		w.z * focalLength
	};

	const Vec3 viewportUpperLeft = {
		camera->center.x - wMulFocalLength.x - (viewportU.x / 2) - (viewportV.x / 2),
		camera->center.y - wMulFocalLength.y - (viewportU.y / 2) - (viewportV.y / 2),
		camera->center.z - wMulFocalLength.z - (viewportU.z / 2) - (viewportV.z / 2)
	};

	camera->pixel00Location.x = viewportUpperLeft.x + 0.5 * (camera->pixelDeltaU.x + camera->pixelDeltaV.x);
	camera->pixel00Location.y = viewportUpperLeft.y + 0.5 * (camera->pixelDeltaU.y + camera->pixelDeltaV.y);
	camera->pixel00Location.z = viewportUpperLeft.z + 0.5 * (camera->pixelDeltaU.z + camera->pixelDeltaV.z);

	camera->maxDepth = 50;
}

void cameraGenerateRay(const Camera* camera, const Vec2 PixelCoordinates, Ray* rayOut)
{
	Vec3 offset = {
		randomDouble() - 0.5,
		randomDouble() - 0.5,
		0.0
	};

	Vec3 pixelCenter = {
		camera->pixel00Location.x + ((PixelCoordinates.x + offset.x) * camera->pixelDeltaU.x) + ((PixelCoordinates.y + offset.y) * camera->pixelDeltaV.x),
		camera->pixel00Location.y + ((PixelCoordinates.x + offset.x) * camera->pixelDeltaU.y) + ((PixelCoordinates.y + offset.y) * camera->pixelDeltaV.y),
		camera->pixel00Location.z + ((PixelCoordinates.x + offset.x) * camera->pixelDeltaU.z) + ((PixelCoordinates.y + offset.y) * camera->pixelDeltaV.z)
	};

	Vec3 rayDirection = {
		pixelCenter.x - camera->center.x,
		pixelCenter.y - camera->center.y,
		pixelCenter.z - camera->center.z
	};

	rayOut->origin = camera->center;
	rayOut->direction = rayDirection;
}

void cameraDestroy(Camera* camera)
{
	memset(camera, NULL, sizeof(Camera));
}
