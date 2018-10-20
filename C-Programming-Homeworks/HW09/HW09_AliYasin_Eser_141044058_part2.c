/*************************************************************
 *                                                           *
 * HW09 Part2                                                *
 * Student Name: Ali Yasin Eser                              *
 * Student ID  : 141044058                                   *
 * Date        : 26/04/2015                                  *
 *                                                           *
 *************************************************************/
#include "complex.h"

int
main(void)
{
	complex_t com1, com2;

	/* Gets two complex numbers */
	printf("Enter the real and imaginary parts of a complex number\n");
	printf("separated by a space> ");
	scan_complex(&com1);
	printf("Enter a second complex number> ");
	scan_complex(&com2);

	/* Forms and displays the sum */
	printf("\n");
	print_complex(com1);
	printf(" + ");
	print_complex(com2);
	printf(" = ");
	print_complex(add_complex(com1, com2));
	printf("\n");

	/* Forms and displays the difference */
	printf("\n");
	print_complex(com1);
	printf(" - ");
	print_complex(com2);
	printf(" = ");
	print_complex(subtract_complex(com1, com2));
	printf("\n");

	/* Forms and displays the absolute value of the first number */
	printf("\n|");
	print_complex(com1);
	printf("| = ");
	print_complex(abs_complex(com1));
	printf("\n");

	/*Forms and displays product of complex values*/
	printf("\n");
	print_complex(com1);
	printf(" * ");
	print_complex(com2);
	printf(" = ");
	print_complex(multiply_complex(com1, com2));
	printf("\n");

	/*Forms and displays product of complex values*/
	printf("\n");
	print_complex(com1);
	printf(" / ");
	print_complex(com2);
	printf(" = ");
	print_complex(divide_complex(com1, com2));
	printf("\n");




	return (0);
}
/*****************************************************************************
 * 						End of HW09 Part2                     				 *
 *****************************************************************************/
