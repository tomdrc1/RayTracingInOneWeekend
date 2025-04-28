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
}

void ppmImageGenerateData(PPMImage* image)
{
    const int width = image->width;
    const int height = image->height;
    Vec3 pixelColor = { 0, 0, 0 };

    fprintf(image->imageFile, "P3\n%d %d\n255\n", width, height);

    for (int j = 0; j < width; j++)
    {
        for (int i = 0; i < height; i++)
        {
            pixelColor.x = (double)i / (double)(width - 1);
            pixelColor.y = (double)j / (double)(height - 1);
            pixelColor.z = 0.0;

            ppmImageWriteColour(image, pixelColor);
        }
    }
}

void ppmImageWriteColour(PPMImage* image, Vec3 pixel)
{
    int ir = (int)(255.999 * (double)pixel.x);
    int ig = (int)(255.999 * (double)pixel.y);
    int ib = (int)(255.999 * (double)pixel.z);

    fprintf(image->imageFile, "%d %d %d\n", ir, ig, ib);
}

void ppmImageDestroy(PPMImage* image)
{
    fclose(image->imageFile);

    memset(image, NULL, sizeof(PPMImage));
}
