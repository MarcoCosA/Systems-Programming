#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Image.h"

/* Get the color intensity of the Red channel of pixel (x, y) in image */
unsigned char GetPixelR(const IMAGE *image, unsigned int x, unsigned int y) {
    assert(image);
    assert(x <= image->W);
    assert(y <= image->H);

    return image->R[x + y * image->W];
}

unsigned char GetPixelG(const IMAGE *image, unsigned int x, unsigned int y) {
    assert(image);
    assert(x <= image->W);
    assert(y <= image->H);

    return image->G[x + y * image->W];
}

unsigned char GetPixelB(const IMAGE *image, unsigned int x, unsigned int y) {
    assert(image);
    assert(x <= image->W);
    assert(y <= image->H);

    return image->B[x + y * image->W];
}
/* Set the color intensity of the Red channel of pixel (x, y) in image to r */
void SetPixelR(IMAGE *image, unsigned int x, unsigned int y, unsigned char r) {
    assert(image);
    assert(x <= image->W);
    assert(y <= image->H);

    image->R[x + y * image->W] = r;
}

void SetPixelG(IMAGE *image, unsigned int x, unsigned int y, unsigned char g) {
    assert(image);
    assert(x <= image->W);
    assert(y <= image->H);

    image->G[x + y * image->W] = g;
}

void SetPixelB(IMAGE *image, unsigned int x, unsigned int y, unsigned char b) {
    assert(image);
    assert(x <= image->W);
    assert(y <= image->H);

    image->B[x + y * image->W] = b;
}

/* Return the image’s width in pixels */
unsigned int ImageWidth(const IMAGE *image){
    assert(image);
    return image->W;
}
/* Return the image’s height in pixels */
unsigned int ImageHeight(const IMAGE *image){
    assert(image);
    return image->H;
}

/* Allocate the memory space for the image structure */
/* and the memory spaces for the color intensity values. */
/* Return the pointer to the image, or NULL in case of error */
IMAGE *CreateImage(unsigned int Width, unsigned int Height) {
    assert(Width >= 0);
    assert(Height >= 0);

    IMAGE *image = malloc(sizeof(IMAGE));

    image->W = Width;
    image->H = Height;

    image->R = malloc(sizeof(char) * Width * Height);
    image->G = malloc(sizeof(char) * Width * Height);
    image->B = malloc(sizeof(char) * Width * Height);

    return image;
}
/* Release the memory spaces for the pixel color intensity values */
/* Deallocate all the memory spaces for the image */
/* Set R/G/B pointers to NULL */
void DeleteImage(IMAGE *image) {
    free(image->R);
    image->R = NULL;
    
    free(image->G);
    image->G = NULL;

    free(image->B);
    image->B = NULL;

    free(image);
}