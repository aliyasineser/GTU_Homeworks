/*************************************************************
 *                                                           *
 * HW04 Q3                                                   *
 * Student Name: ......                                      *
 * Student ID  : ......                                      *
 * Date        : ......                                      *
 * Points      : Write points what you believe to deserve    *
 *                                                           *
 *************************************************************/
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define CHARACTERFILE "Files/Q3/CharacterList.txt"
#define SAMPLEFILE "Files/Q3/Sample.txt"
#define ENCODEDFILE "Files/Q3/XUniversityEncoded.txt"
#define PLAINTEXTFILE "Files/Q3/XUniversityMessage.txt"

/*************************************************************
 * Swaps values of two integers                              *
 *************************************************************/
void 
swap_int(int *a, int *b);

/*************************************************************
 * Swaps values of two characters                            *
 *************************************************************/
void 
swap_char(char *a, char *b);

/*************************************************************
 * Sorts characters according to counts. At the end          *
 * make sure that *c1 keeps most frequent used letter, *c3   *
 * keeps least frequent used letter and *c2 keeps remained   *
 * letter                                                    *
 *************************************************************/
void
sort(char *a, int a_num, char *b, int b_num, char *c, int c_num);

/*************************************************************
 * Check whether character is big ASCII letter or not        *
 * return TRUE or FALSE                                      *
 *************************************************************/
int 
is_letter(char c);

/*************************************************************
 * Read characters from character list file and if character *
 * is letter assign characters to c1, c2 and c3.             *
 * If file has not three letters assign NULL to input char   *
 * by order. For ex. file has two letters assign proper      *
 * letters to c1 and c2 and assign NULL to c3. If file has   *
 * four letters assign c1, c2 and c3 first three letters.    *
 * Return number of letters in character list file.          *
 * Do not forget to count only proper letters with your      *
 * is_letter function. Return number of letters not chars    *
 *************************************************************/
int 
read_character_list(FILE* f_in_ptr, char *c1, char *c2, char *c3);

/*************************************************************
 * Read letters from Sample file and compute frequency of    *
 * letters. Then sort it inside this function. Call sort     *
 * function. At the end make sure that *c1 keeps most        *
 * frequent used letter, *c3 keeps least frequent used       *
 * letter and *c2 keeps remained letter                      *
 *************************************************************/
void 
count_letters(FILE *f_in_ptr, char *c1, char *c2, char *c3);

/*************************************************************
 * Read from XUniversityEncoded file to decode message and   *
 * write decoded (plain text) message to XUniversityMessage  *
 * file. Make sure c1 keeps most frequent used letter,  c3   *
 * keeps least frequent used letter and  c2 keeps remained   *
 * letter while calling function. According to frequency     *
 * you know their codes. c1: 0, c2: 10, c3: 110.             *
 *************************************************************/
void 
decode(FILE *f_in_ptr, FILE *f_out_ptr, char c1, char c2, char c3);

/*************************************************************
 * Learns XUniversity's encoding system from given files ,   *
 * decodes their encoded messages and writes as plain text to*
 * a file                                                    *
 *************************************************************/
int 
main(int argc, char* argv[])
{
	FILE *f_character_list_ptr, *f_sample_file_ptr, *f_encoded_ptr,
		*f_plain_text_ptr;
	int character_number;
	char c1, c2, c3;
	
	/* exit program and print error if character list file could not be opened to read */
	
	/* call read_character_list function and get return value *
	 * if number of letter read is not equal to three exit    *
	 * program                                                */
	
	/* close character list file */

	/* exit program and print error if sample file could not be opened to read */

	/* Call count_letters function and swap letters inside function *
	 * according to number of counts                                */	
	
	/* close sample file */

	/* exit program and print error if encoded file could not be opened to read */
	
	/* exit program and print error if plain text file could not be opened to write */
	
	/* Call decode function */	

	/* close encoded and plain text file */

	return 0;
}

/*************************************************************
 * Swaps values of two integers                              *
 *************************************************************/
void 
swap_int(int *a, int *b)
{
	/*
	 *
	 Some magic here
	 *
	 */
}

/*************************************************************
 * Swaps values of two characters                            *
 *************************************************************/
void 
swap_char(char *a, char *b)
{
	/*
	 *
	 Some magic here
	 *
	 */
}

/*************************************************************
 * Sorts characters according to counts. At the end          *
 * make sure that *c1 keeps most frequent used letter, *c3   *
 * keeps least frequent used letter and *c2 keeps remained   *
 * letter                                                    *
 *************************************************************/
void
sort(char *a, int a_num, char *b, int b_num, char *c, int c_num)
{
	
}

/*************************************************************
 * Check whether character is big ASCII letter or not        *
 * return TRUE or FALSE                                      *
 *************************************************************/
int 
is_letter(char c)
{
	/* Hint: Look for difference with 'A' to understand 
	 * character is a big letter or not. Use ASCII codes to
	 * determine if it is a big letter or not          
	 */

	/*
	 *
	 Some magic here
	 *
	 */
}

/*************************************************************
 * Read characters from character list file and if character *
 * is letter assign characters to c1, c2 and c3.             *
 * If file has not three letters assign NULL to input char   *
 * by order. For ex. file has two letters assign proper      *
 * letters to c1 and c2 and assign NULL to c3. If file has   *
 * four letters assign c1, c2 and c3 first three letters.    *
 * Return number of letters in character list file.          *
 * Do not forget to count only proper letters with your      *
 * is_letter function. Return number of letters not chars    *
 *************************************************************/
int 
read_character_list(FILE* f_in_ptr, char *c1, char *c2, char *c3)
{	
	int counter = 0;
	
	/*
	 *
	 Some magic here
	 *
	 */

	return counter;
}

/*************************************************************
 * Read letters from Sample file and compute frequency of    *
 * letters. Then sort it inside this function. Call sort     *
 * function. At the end make sure that *c1 keeps most        *
 * frequent used letter, *c3 keeps least frequent used       *
 * letter and *c2 keeps remained letter                      *
 *************************************************************/
void 
count_letters(FILE *f_in_ptr, char *c1, char *c2, char *c3)
{

	/* Hint: Read character by character and increment counter
	 * of proper counter of read character.
	 */

	/*
	 *
	 Some magic here
	 *
	 */

}

/*************************************************************
 * Read from XUniversityEncoded file to decode message and   *
 * write decoded (plain text) message to XUniversityMessage  *
 * file. Make sure c1 keeps most frequent used letter,  c3   *
 * keeps least frequent used letter and  c2 keeps remained   *
 * letter while calling function. According to frequency     *
 * you know their codes. c1: 0, c2: 10, c3: 110.             *
 *************************************************************/
void 
decode(FILE *f_in_ptr, FILE *f_out_ptr, char c1, char c2, char c3)
{
	
	/* Hint: While reading from encoded text file keep reading 
	 *		 character by character. Use ASCII difference from 0
	 *		 to determine number is 0 or 1. If we try reading it
	 *		 as integer, it overflows. Overflow is bad if you are 
	 *		 not hacker and do not want to crash system deliberately.
	 */

	/*
	 *
	 Some magic here
	 *
	 */

}