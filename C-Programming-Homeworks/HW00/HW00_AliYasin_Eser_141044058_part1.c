/*################################################################*/
/*HW00_Ali_Yasin_Eser_141044058.c  								  */
/*_______________________________								  */
/*Written by Ali Yasin Eser on February 11, 2015				  */
/*																  */	
/*Description													  */
/*___________ 													  */
/*Takes the Integral of a given 1st degree polynomial			  */
/*Inputs:														  */
/*	-Coefficients of the 1st degree polynomial					  */
/*	-Zero input value of the resulting polynomial				  */
/*Outputs:														  */
/*	-Resulting 2nd degree polynomial							  */
/*################################################################*/
/*																  */
/*----------------------------------------------------------------*/
/*						Includes								  */
/*----------------------------------------------------------------*/
#include <stdio.h>


int
main(){
	double ia0, ia1;	/* coefficents of the input poly*/
	double p0;			/*value of the resulting poly*/
	double ra0, ra1, ra2;	/*coefficents of the resulting poly*/

	/*Get the 1st degree input polynomial*/
	printf
	("Enter the coefficents of the polynomial(from higher or lower order)>");
	scanf("%lf%lf", &ia1, &ia0);
	/*Get the zero input value of the resulting poly*/
	printf("Enter p(0) value for the resulting polynomial>");
	scanf("%lf", &p0);
	
	/*Calculate the resulting poly*/
	ra2 = ia1/(2);
	ra1 = ia0;
	ra0 = p0; /* Constant value of resulting poly */

	/*Output the resulting poly*/
	printf
	("The resulting polynomial is %5.2fx^2+%5.2fx+%5.2f\n.", ra2, ra1, ra0);
	
	return 0;
}
/*################################################################*/
/*			End of HW00_Ali_Yasin_Eser_141044058.c          	  */
/*################################################################*/
