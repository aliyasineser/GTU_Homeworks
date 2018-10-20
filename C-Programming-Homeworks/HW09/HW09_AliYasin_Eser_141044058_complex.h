/*************************************************************
 *                                                           *
 * HW09 Part2 Header                                         *
 * Student Name: Ali Yasin Eser                              *
 * Student ID  : 141044058                                   *
 * Date        : 26/04/2015                                  *
 *                                                           *
 *************************************************************/
#include <stdio.h>
#include <math.h>

/* User-defined complex number type */
typedef struct{
                double real, imag;
              } complex_t;
/*
* Complex number input function returns standard scanning error code
* 1 => valid scan, 0 => error, negative EOF value => end of file
*/
extern int scan_complex(complex_t *c);

/*
* Complex output function displays value as (a + bi) or (a - bi),
* dropping a or b if they round to 0 unless both round to 0
*/
extern void print_complex(complex_t c);

/*
* Returns sum of complex values c1 and c2
*/
extern complex_t add_complex(complex_t c1, complex_t c2);

/*
* Returns difference c1 and  c2
*/
extern complex_t subtract_complex(complex_t c1, complex_t c2);

/*
* Returns product of complex values c1 and c2
*/
extern complex_t multiply_complex(complex_t c1, complex_t c2);

/*
* Returns quotient of complex values (c1 / c2)
*/
extern complex_t divide_complex(complex_t c1, complex_t c2);

/*
* Returns absolute value of complex number c
*/
extern complex_t abs_complex(complex_t c);

/*****************************************************************************
 * 			        	End of HW09 Part2 Header               				 *
 *****************************************************************************/
