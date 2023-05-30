/* roulette.c has the use play a game of roulette.    */
/* The user enters the amount they wand to play with  */
/* and chooses to bet on odd or even as the winning   */
/* number.                                            */
/* author: Marco Costa                                */
/*                                                    */
/* modifications:                                     */
/* 03/10/23 Initial Version                           */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	/*Seed the random number generator with the current time */
	srand(time(NULL));
	int choice, randNum;
	double money, bet;

	printf("Entering the casino, how much money do you have? $");
	scanf("%lf", &money);
	printf("We are playing Roulette, odd or even bets only.");
	printf("\nPlace your bet!");

	/* This while look will continue until the user enters 0. There is a break statement within it */
	while(1) {	
		printf("\nEnter 1 for odd, 2 for even, 0 to quit: ");
		scanf("%d", &choice);
		if(choice == 0)
		{
			printf("Your exit the casino $%.2lf\n", money);
			break;
		}
		printf("How much money do you want to bet? $");
		scanf("%lf", &bet);
		printf("You bet $%.2lf on odd numbers.", bet);

		randNum = rand() % 36;
		printf("\nThe winning number is %d!", randNum);

		/* Determine if the user won or lost and calculate earnings */
		if((choice == 1 && randNum % 2 == 1) || (choice = 2 && randNum % 2 ==0))
		{
			money += bet;
			printf("\nYou Win!");
		} else {
			money -= bet;
			printf("\nYou Lose!");
		}
		printf("\nYour balance is $%.2lf!!", money);
	}

	return 0;
}