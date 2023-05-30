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

	printf("************************************\n");
	printf("** Welcome to CENG 231 BlackJack! **\n");
	printf("************************************\n");
	int playersCard = rand() % 13 + 1;
	int dealersCard = rand() % 13 + 1;
	int playersValue = playersCard;
	int dealersValue = dealersCard;

	printf("Your first card is: %d\n", playersCard);

	int hit = 1;
	while (hit)
	{
		printf("Do you want another card?\nType 1 for Yes, 0 for No: ");
		scanf("%d", &hit);

		if (hit)
		{
			int playersCard = rand() % 13 + 1;
			printf("Your next card is: %d\n", playersCard);

			if (playersCard > 10)
			{
				playersCard = 10;
			}

			playersValue += playersCard;
			printf("Your combined value is: %d\n", playersValue);

			/*If the player's score is over 21, they bust. End the game and declare the dealer the winner */
			if (playersValue > 21)
			{
				printf("Sorry. You lose!\n");
				return 0;
			}
		}
	}

	while (dealersValue < playersValue && dealersValue <= 21)
	{
		int dealersCard = rand() % 13 + 1;
		printf("Dealer draws another card.\nDealer's card is: %d\n", dealersCard);

		if (dealersCard > 10)
		{
			dealersCard = 10;
		}

		dealersValue += dealersCard;
		printf("Dealer's value is %d, you have %d.\n", dealersValue, playersValue);
	}

	/*If the player's score is over 21, they bust. End the game and declare the dealer the winner */
	if (dealersValue > 21)
	{
		printf("Dealer loses. You win!\n");
	}
	else if (dealersValue == playersValue)
	{
		printf("Dealer wins. You lose.\n");
	}
	else
	{
		printf("Dealer wins. You lose.\n");
	}
	return 0;
}