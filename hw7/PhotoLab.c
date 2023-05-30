/*********************************************************************/
/* PhotoLab.c: Assignment 7 for CENG231, Spring 2023                 */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Image.h"

/*** global definitions ***/
#define SLEN      80		/* maximum length of file names */
#define MAX_PIXEL 255           /* maximum pixel intensity value */

/*** function declarations ***/
/* Read image from a file 						*/
/* The size of the image needs to be pre-set				*/
/* The memory spaces of the image will be allocated in this function	*/
/* Return values:							*/
/* NULL: fail to load or create an image				*/
/* image: load or create an image successfully				*/
IMAGE *LoadImage(const char *fname);

/* Save a processed image 		*/
/* Return values:			*/
/* 0: successfully saved the image	*/
/* 1: Cannot open the file for writing	*/
/* 2: File error while writing to file	*/
int SaveImage(const char *fname, const IMAGE *image);

/* Age the image */
IMAGE *Aging(IMAGE *image);

/* Black and White */
IMAGE *BlackNWhite(IMAGE *image);

/* Reverse image color */
IMAGE *Negative(IMAGE *image);

/* flip image vertically */
IMAGE *VFlip(IMAGE *image);

/* mirror image horizontally */
IMAGE *HMirror(IMAGE *image);

/* sharpen the image */
IMAGE *Sharpen(IMAGE *image);

/* exchange R and B color channels */
IMAGE *ExRB(IMAGE *image);

/* [Bonus] crop an image */
IMAGE *Crop(IMAGE *image, int X, int Y, int W, int H);

/* test all functions */
int AutoTest(void);

IMAGE *LoadImage(const char *fname)
{
	FILE         *File;
	char         Type[SLEN];
	int          W, H, MaxValue;
	unsigned int x, y;
	char         ftype[] = ".ppm";
	char         fname_tmp[SLEN];
	IMAGE        *image;
	strcpy(fname_tmp, fname);
	strcat(fname_tmp, ftype);
	File = fopen(fname_tmp, "r");
	if (!File) {
		printf("\nCan't open file \"%s\" for reading!\n", fname);
		return NULL;
	}

	fscanf(File, "%79s", Type);
	if (Type[0] != 'P' || Type[1] != '6' || Type[2] != 0) {
		printf("\nUnsupported file format!\n");
		fclose(File);
		return NULL;
	}

	fscanf(File, "%d", &W);
	if (W <= 0) {
		printf("\nUnsupported image width %d!\n", W);
		fclose(File);
		return NULL;
	}

	fscanf(File, "%d", &H);
	if (H <= 0) {
		printf("\nUnsupported image height %d!\n", H);
		fclose(File);
		return NULL;
	}

	fscanf(File, "%d", &MaxValue);
	if (MaxValue != 255) {
		printf("\nUnsupported image maximum value %d!\n", MaxValue);
		fclose(File);
		return NULL;
	}
	if ('\n' != fgetc(File)) {
		printf("\nCarriage return expected at the end of the file!\n");
		fclose(File);
		return NULL;
	}

	image = CreateImage(W, H);

	if (!image) {
		printf("\nError creating image from %s!\n", fname_tmp);
		fclose(File);
		return NULL;
	}
	else {
		for (y = 0; y < ImageHeight(image); y++)
			for (x = 0; x < ImageWidth(image); x++) {
				SetPixelR(image, x, y, fgetc(File));
				SetPixelG(image, x, y, fgetc(File));
				SetPixelB(image, x, y, fgetc(File));
			}

		if (ferror(File)) {
			printf("\nFile error while reading from file!\n");
			DeleteImage(image);
			return NULL;
		}

		printf("%s was read successfully!\n", fname_tmp);
		fclose(File);
		return image;
	}
}

int SaveImage(const char *fname, const IMAGE *image)
{
    assert(image != NULL && "No image to save!\n");
	FILE         *File;
	int          x, y;
	char         SysCmd[SLEN * 5];
	char         ftype[] = ".ppm";
	char         fname_tmp[SLEN];
	char         fname_tmp2[SLEN];
	unsigned int WIDTH = ImageWidth(image);
	unsigned int HEIGHT = ImageHeight(image);
	strcpy(fname_tmp, fname);
	strcpy(fname_tmp2, fname);
	strcat(fname_tmp2, ftype);

	File = fopen(fname_tmp2, "w");
	if (!File) {
		printf("\nCan't open file \"%s\" for writing!\n", fname);
		return 1;
	}
	fprintf(File, "P6\n");
	fprintf(File, "%d %d\n", WIDTH, HEIGHT);
	fprintf(File, "255\n");

	for (y = 0; y < HEIGHT; y++)
		for (x = 0; x < WIDTH; x++) {
			fputc(GetPixelR(image, x, y), File);
			fputc(GetPixelG(image, x, y), File);
			fputc(GetPixelB(image, x, y), File);
		}

	if (ferror(File)) {
		printf("\nError while writing to file!\n");
		return 2;
	}
	fclose(File);
	printf("%s was saved successfully. \n", fname_tmp2);
	/*
	 * Rename file to image.ppm, convert it to ~/public_html/<fname>.jpg
	 * and make it world readable
	 */
	sprintf(SysCmd, "~ceng231/bin/pnmtojpeg.sh %s",
			fname_tmp2);
	if (system(SysCmd) != 0) {
		printf("\nError while converting to JPG:\nCommand \"%s\" failed!\n", SysCmd);
		return 3;
	}
	printf("%s.jpg was stored for viewing. \n", fname_tmp);
	return 0;
}

/* auto test */
int AutoTest(void) {
    int result;
    const char fname[SLEN] = "wilson";

	IMAGE *image = NULL;
    image = LoadImage(fname);
    if (! image) return 11;
    image = Aging(image);
    if (! image) return 12;
    result = SaveImage("aging", image);
    if (result) return result;
    printf("Aging tested!\n\n");
	DeleteImage(image);
	image = NULL;

    image = LoadImage(fname);
    if (! image) return 13;
    image = BlackNWhite(image);
    if (! image) return 14;
    result = SaveImage("bw", image);
    if (result) return result;
    printf("Black and White tested!\n\n");
	DeleteImage(image);
	image = NULL;

    image = LoadImage(fname);
    if (! image) return 15;
    image = Negative(image);
    if (! image) return 16;
    result = SaveImage("negative", image);
    if (result) return result;
    printf("Negative tested!\n\n");
    DeleteImage(image);
	image = NULL;

    image = LoadImage(fname);
    if (! image) return 17;
    image = VFlip(image);
    if (! image) return 18;
    result = SaveImage("vflip", image);
    if (result) return result;
    printf("VFlip tested!\n\n");
    DeleteImage(image);
	image = NULL;

    image = LoadImage(fname);
    if (! image) return 19;
    image = HMirror(image);
    if (! image) return 20;
    result = SaveImage("hmirror", image);
    if (result) return result;
    printf("HMirror tested!\n\n");
    DeleteImage(image);
	image = NULL;

    image = LoadImage(fname);
    if (! image) return 21;
    image = Sharpen(image);
    if (! image) return 22;
    result = SaveImage("sharpen", image);
    if (result) return result;
    printf("Sharpen tested!\n\n");
    DeleteImage(image);
	image = NULL;

    image = LoadImage(fname);
    if (! image) return 23;
    image = ExRB(image);
    if (! image) return 24;
    result = SaveImage("xRB", image);
    if (result) return result;
    printf("ExRB tested!\n\n");
    DeleteImage(image);
	image = NULL;

	image = LoadImage(fname);
    if (! image) return 25;
    image = Crop(image, 200, 150, 115, 130);
    if (! image) return 26;
    result = SaveImage("crop", image);
    if (result) return result;
    printf("Crop tested!\n\n");
    DeleteImage(image);
	image = NULL;


    return 0; /* success! */
}

/**************************************************************/
/* Please add your function definitions here...               */
/**************************************************************/

IMAGE *Aging(IMAGE *image) {
	int x, y;

    for( y = 0; y < ImageHeight(image); y++ ) {
        for( x = 0; x < ImageWidth(image); x++ ) {
			SetPixelB(image, x, y, (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y)) / 5);
            SetPixelR(image, x, y, GetPixelB(image, x, y) * 1.6);
            SetPixelG(image,x, y, GetPixelB(image, x, y) *1.6);
	    }
    }

	return image;
}

IMAGE *BlackNWhite(IMAGE *image) {
    int x, y;
    for (y = 0; y < ImageHeight(image); y++) {
        for (x = 0; x < ImageWidth(image); x++) {
            int average = (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y)) / 3;
            SetPixelR(image, x, y, average);
            SetPixelG(image, x, y, average);
            SetPixelB(image, x, y, average);
        }
    }
    return image;
}
IMAGE *Negative(IMAGE *image) {
    int x, y;
    for (y = 0; y < ImageHeight(image); y++) {
        for (x = 0; x < ImageWidth(image); x++) {
            SetPixelR(image, x, y, 255 - GetPixelR(image, x, y));
            SetPixelG(image, x, y, 255 - GetPixelG(image, x, y));
            SetPixelB(image, x, y, 255 - GetPixelB(image, x, y));
        }
    }
    return image;
}

IMAGE *VFlip(IMAGE *image) {
    int x, y;
    for (y = 0; y < ImageHeight(image) / 2; y++) {
        for (x = 0; x < ImageWidth(image); x++) {
            int r = GetPixelR(image, x, y);
            int g = GetPixelG(image, x, y);
            int b = GetPixelB(image, x, y);

            SetPixelR(image, x, y, GetPixelR(image, x, ImageHeight(image) - y - 1));
            SetPixelG(image, x, y, GetPixelG(image, x, ImageHeight(image) - y - 1));
            SetPixelB(image, x, y, GetPixelB(image, x, ImageHeight(image) - y - 1));

            SetPixelR(image, x, ImageHeight(image) - y - 1, r);
            SetPixelG(image, x, ImageHeight(image) - y - 1, g);
            SetPixelB(image, x, ImageHeight(image) - y - 1, b);
        }
    }
    return image;
}

IMAGE *HMirror(IMAGE *image) {
    int x, y;
    for (y = 0; y < ImageHeight(image); y++) {
        for (x = 0; x < ImageWidth(image); x++) {
            SetPixelR(image, ImageWidth(image) - 1 - x, y, GetPixelR(image, x, y));
            SetPixelG(image, ImageWidth(image) - 1 - x, y, GetPixelG(image, x, y));
            SetPixelB(image, ImageWidth(image) - 1 - x, y, GetPixelB(image, x, y));
        }
    }
    return image;
}


unsigned char CalculateCenterPixelIntensity(IMAGE *image, unsigned char *array, int x, int y)
{
    if(x < ImageWidth(image) - 1 && x != 0 && y < ImageHeight(image) - 1 && y != 0)
    {
        int num = array[x + y * ImageWidth(image)] * 9;
        num -= array[x-1 + (y+1) * ImageWidth(image)];
        num -= array[x + (y+1) * ImageWidth(image)];
        num -= array[x+1 + (y+1) * ImageWidth(image)];
        num -= array[x-1 + y * ImageWidth(image)];
        num -= array[x+1 + y * ImageWidth(image)];
        num -= array[x-1 + (y-1) * ImageWidth(image)];
        num -= array[x + (y-1) * ImageWidth(image)];
        num -= array[x+1 + (y-1) * ImageWidth(image)];

        if(num > 255)
            return 255;
        if(num < 0)
            return 0;
        return num;
    }
    return array[x + y * ImageWidth(image)];
}

IMAGE *Sharpen(IMAGE *image) {
    unsigned char tempR[ImageWidth(image) * ImageHeight(image)];
    unsigned char tempG[ImageWidth(image) * ImageHeight(image)];
    unsigned char tempB[ImageWidth(image) * ImageHeight(image)];

    int x, y;
    for (y = 0; y < ImageHeight(image); y++) {
        for (x = 0; x < ImageWidth(image); x++) {
            tempR[x + y * ImageWidth(image)] = GetPixelR(image, x, y);
            tempG[x + y * ImageWidth(image)] = GetPixelG(image, x, y);
            tempB[x + y * ImageWidth(image)] = GetPixelB(image, x, y);
        }
    }

    for (y = 0; y < ImageHeight(image); y++) {
        for (x = 0; x < ImageWidth(image); x++) {
            SetPixelR(image, x, y, CalculateCenterPixelIntensity(image, tempR, x, y));
            SetPixelG(image, x, y, CalculateCenterPixelIntensity(image, tempG, x, y));
            SetPixelB(image, x, y, CalculateCenterPixelIntensity(image, tempB, x, y));
        }
    }

    return image;
}

IMAGE *ExRB(IMAGE *image) {
    int x, y;
    for (y = 0; y < ImageHeight(image); y++) {
        for (x = 0; x < ImageWidth(image); x++) {
            unsigned char num = GetPixelR(image, x, y);
            SetPixelR(image, x, y, GetPixelB(image, x, y));
            SetPixelB(image, x, y, num);
        }
    }
    return image;
}

IMAGE *Crop(IMAGE *image, int x, int y, int W, int H) {
    IMAGE *croppedImage = CreateImage(W, H);

    int i, j;
    for (i = 0; i < H; i++) {
        for (j = 0; j < W; j++) {
            int row = i + y;
            int col = j + x;

            if (row >= 0 && row < ImageHeight(image) && col >= 0 && col < ImageWidth(image)) {
                SetPixelR(croppedImage, j, i, GetPixelR(image, col, row));
                SetPixelG(croppedImage, j, i, GetPixelG(image, col, row));
                SetPixelB(croppedImage, j, i, GetPixelB(image, col, row));
            }
        }
    }

    DeleteImage(image);
    image = NULL;
    return croppedImage;
}



/**************************************************************/
/* Main function (do not modify!)                             */
/**************************************************************/

int main(void)
{
  int result;
  result = AutoTest();
  if (result) {
	printf("AutoTest failed, error code %d!\n", result);
  }
  else{
	printf("AutoTest finished.\n");
  }
  return 0;
}
