/* pipe.c a program that calculates the volume and   */
/* thickness of a pipe                               */
/* author: Marco Costa                               */
/*                                                   */
/* modifications:                                    */
/* 02/09/23 Initial Version                          */

#include <stdio.h>

#define PI 3.14159265359
int main()
{
    float r = 0; /* input inner radius */
    float R = 0; /* input outer radius */
    float L = 0; /* input length       */

    float thickness = 0; /* output thickness */
    float volume = 0;    /* output volume    */

    printf("\nPlease enter the inner radius of the pipe (r): ");
    scanf("%f", &r);
    printf("Please enter the outer radius of the pipe (R): ");
    scanf("%f", &R);
    printf("Please enter the length of the pipe (L): ");
    scanf("%f", &L);

    thickness = R - r;
    volume = PI * ((R*R)-(r*r)) * L;
    printf("The thickness of the pipe is: %f", thickness);
    printf("\nThe volume of the pipe is: %f", volume);
    printf("\n");

    return 0;
}

