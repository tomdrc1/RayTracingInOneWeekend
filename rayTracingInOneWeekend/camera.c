#include "camera.h"

void cameraInit(Camera* camera, const Vec3 lookFrom, const Vec3 lookAt, const unsigned int imageWidth, const unsigned int imageHeight)
{
	camera->center = lookFrom;
	camera->vfov = 20;

	camera->defocusAngle = 0.6;
	camera->focusDist = 10.0;

	camera->maxDepth = 50;

	camera->samplesPerPixel = 500;
	camera->pixelSamplesScale = 1.0 / (double)camera->samplesPerPixel;

	const double theta = degreesToRadians(camera->vfov);
	const double h = tan(theta / 2.0);
	const double viewportHeight = 2.0 * h * camera->focusDist;
	const double viewportWidth = viewportHeight * ((double)imageWidth / (double)imageHeight);

	const Vec3 vUp = { 0, 1, 0 };
	const Vec3 focal = {
		lookFrom.x - lookAt.x,
		lookFrom.y - lookAt.y,
		lookFrom.z - lookAt.z
	};

	const Vec3 w = vec3UnitVector(&focal);
	const Vec3 wCross = vec3Cross(&vUp, &w);

	const Vec3 u = vec3UnitVector(&wCross);
	const Vec3 v = vec3Cross(&w, &u);

	const Vec3 viewportU = { viewportWidth * u.x, viewportWidth * u.y, viewportWidth * u.z };
	const Vec3 viewportV = { viewportHeight * -v.x, viewportHeight * -v.y, viewportHeight * -v.z };

	camera->pixelDeltaU = (Vec3){
		viewportU.x / imageWidth,
		viewportU.y / imageWidth,
		viewportU.z / imageWidth
	};

	camera->pixelDeltaV = (Vec3){
		viewportV.x / imageHeight,
		viewportV.y / imageHeight,
		viewportV.z / imageHeight,
	};

	const Vec3 focusRange = {
		w.x * camera->focusDist,
		w.y * camera->focusDist,
		w.z * camera->focusDist
	};

	const Vec3 viewportUpperLeft = {
		camera->center.x - focusRange.x - (viewportU.x / 2) - (viewportV.x / 2),
		camera->center.y - focusRange.y - (viewportU.y / 2) - (viewportV.y / 2),
		camera->center.z - focusRange.z - (viewportU.z / 2) - (viewportV.z / 2)
	};

	camera->pixel00Location = (Vec3){
		viewportUpperLeft.x + 0.5 * (camera->pixelDeltaU.x + camera->pixelDeltaV.x),
		viewportUpperLeft.y + 0.5 * (camera->pixelDeltaU.y + camera->pixelDeltaV.y),
		viewportUpperLeft.z + 0.5 * (camera->pixelDeltaU.z + camera->pixelDeltaV.z)
	};

	const double defocusRadius = camera->focusDist * tan(degreesToRadians((camera->defocusAngle / 2)));
	camera->defocusDiskU = (Vec3){
		u.x * defocusRadius,
		u.y * defocusRadius,
		u.z * defocusRadius
	};

	camera->defocusDiskV = (Vec3){
		v.x * defocusRadius,
		v.y * defocusRadius,
		v.z * defocusRadius
	};
}

void cameraGenerateRay(const Camera* camera, const Vec2 PixelCoordinates, Ray* rayOut)
{
	const Vec3 offset = {
		randomDouble() - 0.5,
		randomDouble() - 0.5,
		0.0
	};

	const Vec3 pixelCenter = {
		camera->pixel00Location.x + ((PixelCoordinates.x + offset.x) * camera->pixelDeltaU.x) + ((PixelCoordinates.y + offset.y) * camera->pixelDeltaV.x),
		camera->pixel00Location.y + ((PixelCoordinates.x + offset.x) * camera->pixelDeltaU.y) + ((PixelCoordinates.y + offset.y) * camera->pixelDeltaV.y),
		camera->pixel00Location.z + ((PixelCoordinates.x + offset.x) * camera->pixelDeltaU.z) + ((PixelCoordinates.y + offset.y) * camera->pixelDeltaV.z)
	};

	rayOut->origin = (camera->defocusAngle <= 0) ? camera->center : cameraDefocusDiskSample(camera);
	rayOut->direction = (Vec3){
		pixelCenter.x - rayOut->origin.x,
		pixelCenter.y - rayOut->origin.y,
		pixelCenter.z - rayOut->origin.z
	};
}

Vec3 cameraDefocusDiskSample(const Camera* camera)
{
	const Vec3 point = vec3RandomInUnitDisk();

	const Vec3 pointDefocusU = {
		camera->defocusDiskU.x * point.x,
		camera->defocusDiskU.y * point.x,
		camera->defocusDiskU.z * point.x
	};

	const Vec3 pointDefocusV = {
		camera->defocusDiskV.x * point.y,
		camera->defocusDiskV.y * point.y,
		camera->defocusDiskV.z * point.y
	};

	return (Vec3) {
		camera->center.x + pointDefocusU.x + pointDefocusV.x,
		camera->center.y + pointDefocusU.y + pointDefocusV.y,
		camera->center.z + pointDefocusU.z + pointDefocusV.z
	};
}

void cameraDestroy(Camera* camera)
{
	memset(camera, NULL, sizeof(Camera));
}
