/*################################################################*/
/*HW00_Ali_Yasin_Eser_141044058.c  								  */
/*_______________________________								  */
/*Written by Ali Yasin Eser on February 12, 2015				  */
/*																  */	
/*Description													  */
/*___________ 													  */
/*Calculates the multiplication of 2 polynomials of 2nd degree	  */
/*Inputs:														  */
/*	-Coefficients of the first 2nd degree polynomial			  */
/*	-Coefficients of the second 2nd degree polynomial			  */
/*Outputs:														  */
/*	-Resulting polynomial										  */
/*################################################################*/
/*																  */
/*----------------------------------------------------------------*/
/*						Includes								  */
/*----------------------------------------------------------------*/
#include <stdio.h>


int
main(){
	double bk2, bk1, bk0;	/* Coefficents of first polynomial */
	double ik2, ik1, ik0;	/* Coefficents of second polynomial */	
	double rp4, rp3, rp2, rp1, rp0;	 /* Coefficents of resulting polynomial */

	/* Get the first polynomial's coefficents */
	/* Two printf for 80 column limit */
	printf
	("Enter the coefficents of the first polynomial "); 
	printf("(from higher to lower order)\n");
	scanf("%lf%lf%lf", &bk2, &bk1, &bk0);
	
	/* Get the second polynomial's coefficents */
	/*Two printf for 80 column limit*/
	printf("Enter the coefficents of the second polynomial ");
	printf("(from higher to lower order)\n");
	scanf("%lf%lf%lf", &ik2, &ik1, &ik0);

	/* Calculating the resulting poly */
	rp4 = bk2 * ik2;
	rp3 = (bk2 * ik1) + (bk1 * ik2);
	rp2 = (bk2 * ik0) + (bk0 * ik2) + (bk1 * ik1);
	rp1 = (bk1 * ik0) + (bk0 * ik1);
	rp0 = (bk0 * ik0);
	
	/* Output the resulting poly */
	printf
	("The resulting polynomial is %5.2fx^4+%5.2fx^3+%5.2fx^2+%5.2fx+%5.2f.\n",
	rp4, rp3, rp2, rp1, rp0);

	return 0;
}
/*################################################################*/
/*			End of HW00_Ali_Yasin_Eser_141044058.c          	  */
/*################################################################*/
