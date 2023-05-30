/* distance.c a program that takes miles, yards, feet */
/* and inches as input twice and converts them to the */
/* minimum value of each that still represents the    */
/* total distance inputted                            */
/* author: Marco Costa                                */
/*                                                    */
/* modifications:                                     */
/* 02/20/23 Initial Version                           */

#include <stdio.h>

int main() {
    int m1, y1, f1, i1, m2, y2, f2, i2;
    int sum_inch1, sum_inch2, total_inches;
    int miles, yards, feet, inches;

    printf("Please enter two distance values m1, y1, f1, i1, m2, y2, f2, and i2.\n");
    
    /* get user input for the first distance */
    printf("i1: ");
    scanf("%d", &i1);
    printf("f1: ");
    scanf("%d", &f1);
    printf("y1: ");
    scanf("%d", &y1);
    printf("m1: ");
    scanf("%d", &m1);
    
    /* convert to inches */
    sum_inch1 = i1 + (f1 * 12) + (y1 * 36) + (m1 * 63360); 
    
    /* calculate miles, yards, feet and inches using sum_inch to avoid truncating values */
    i1 = sum_inch1 % 12;
    f1 = (sum_inch1 % 36) / 12;
    y1 = (sum_inch1 % 63360) / 36;
    m1 = sum_inch1 / 63360;
    
    printf("Distance 1 is %d miles, %d yards, %d feet, %d inches.\n",
        m1, y1, f1, i1);
        
    /* get user input for the second distance */
    printf("i2: ");
    scanf("%d", &i2);
    printf("f2: ");
    scanf("%d", &f2);
    printf("y2: ");
    scanf("%d", &y2);
    printf("m2: ");
    scanf("%d", &m2);
    
    /* convert second distance to inches */
    sum_inch2 = i2 + (f2 * 12) + (y2 * 36) + (m2 * 63360); 
    
    /* same calculation for miles, yards, feet and inches as above */
    i2 = sum_inch2 % 12;
    f2 = (sum_inch2 % 36) / 12;
    y2 = (sum_inch2 % 63360) / 36;
    m2 = sum_inch2 / 63360;
 
    printf("Distance 2 is %d miles, %d yards, %d feet, %d inches.\n",
        m2, y2, f2, i2);
    
    /* Calculate the sum of sum_inch1 and sum_inch2 as total_inches and then use
    it to calculate the total miles, yards, feet and inches */
    total_inches = sum_inch1 + sum_inch2;
    inches = total_inches % 12;
    feet = (total_inches % 36) / 12;
    yards = (total_inches % 63360) / 36;
    miles = total_inches / 63360;
        
    printf("The sum of the distances is %d miles, %d yards, %d feet, and %d inches.\n",
        miles, yards, feet, inches);
    return 0;
}
