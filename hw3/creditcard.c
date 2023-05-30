/* creditcard.c is a program that calculates how many */
/* months it will take to bay off a balance using the */
/* user's inputted APR and monthly payment            */
/*                                                    */
/* author: Marco Costa                                */
/*                                                    */
/* modifications:                                     */
/* 03/03/23 Initial Version                           */

#include <stdio.h>

int main() {
    double limit, balance, apr, monthlyPayment;

    /* get user input */
    printf("Enter the credit limit\t: ");
    scanf("%lf", &limit);
    printf("Enter the balance on the card\t: ");
    scanf("%lf", &balance);
    printf("Enter the APR\t: ");
    scanf("%lf", &apr);
    printf("Enter the monthly payment\t: ");
    scanf("%lf", &monthlyPayment);

    printf("\nMonth   Balance      Interest      Payment      New Balance\n");

    int count = 0;
    double interest, tempBalance, sum = 0;
    while(balance > 0 && count < 15)
    {
        count++;
        tempBalance = balance;

        interest = balance * (apr / 100.0) / 12.0;
        
        if(monthlyPayment > balance)
        {
            monthlyPayment = balance + interest;
            balance = 0;
        }
        else
        {
            balance -= monthlyPayment - interest;
        }

        sum += monthlyPayment;

        /* Month | Balance | Interest | Payment | New Balance */
        printf("%*d\t%*.2f  \t%*.2f      %*.2f \t%*.2f\n", 3, count, 7 , tempBalance, 5, interest, 5, monthlyPayment, 7, balance);
    }

    printf("\nIt will take $%.2f over %d months to pay off this debt.\n", sum, count); 
    return 0;
}
