#include "ppmImage.h"

void ppmImageInit(PPMImage* image, const char* path, const unsigned short width, const unsigned short height)
{
    memset(image, NULL, sizeof(PPMImage));

    fopen_s(&image->imageFile, path, "w");

    if (!image->imageFile)
    {
        printf("Error opening the file!\n");
        getchar();

        exit(-1);
    }

    image->height = height;
    image->width = width;

    fprintf(image->imageFile, "P3\n%d %d\n255\n", width, height);
}

void ppmImageWriteColor(PPMImage* image, Vec3 pixelColor)
{
    int ir = (int)(255.999 * (double)pixelColor.x);
    int ig = (int)(255.999 * (double)pixelColor.y);
    int ib = (int)(255.999 * (double)pixelColor.z);

    fprintf(image->imageFile, "%d %d %d\n", ir, ig, ib);
}

void ppmImageDestroy(PPMImage* image)
{
    fclose(image->imageFile);

    memset(image, NULL, sizeof(PPMImage));
}
