#include <stdio.h>

#include "camera.h"

int main(int argc, char** argv)
{
	Camera cam;

	cameraInit(&cam, 800);
	cameraRender(&cam);
	cameraDestroy(&cam);
	
	return 0;
}