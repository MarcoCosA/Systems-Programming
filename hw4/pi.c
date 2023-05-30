/* blackjack.c is a program that engages the user     */
/* with the popular game of blackjack. This program   */
/* does not include the benefit of aces which are     */
/* normally considered as either 1 or 11              */
/* author: Marco Costa                                */
/*                                                    */
/* modifications:                                     */
/* 03/03/23 Initial Version                           */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	/*Seed the random number generator with the current time */
	srand(time(NULL));
	int numPoints;
	double r, x, y, s;

	printf("Enter the radius of circle: ");
	scanf("%lf", &r);
	printf("Enter the number of points: ");
	scanf("%d", &numPoints);

	s = 2 * r;

	int i, pointsInside = 0;
	double distanceLeftSquared, distanceRightSquared;
	for (i = 0; i < numPoints; i++)
	{
		x = ((double) rand()) / ((double) RAND_MAX) * s;
		y = ((double) rand()) / ((double) RAND_MAX) * s;

		printf("\nPoint No.%d (x=%lf,y=%lf): ", i + 1, x, y);

		distanceLeftSquared = (x * x) + (y - r) * (y - r);
		distanceRightSquared = (x - s) * (x - s) + (y - r) * (y - r);

		if(distanceLeftSquared < r * r || distanceRightSquared < r * r)
		{
			pointsInside++;
			printf("IN");
		} else {
			printf("OUT");
		}
	}
	printf("\n\n/******In Summary******/\n");
	printf("Points within circle areas: %d\n", pointsInside);
	printf("Points out of circle areas: %d\n", numPoints - pointsInside);
	printf("PI= %lf\n", 4 * (pointsInside / (double)(numPoints)));
	return 0;
}