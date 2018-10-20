/*************************************************************
 *                                                           *
 * HW04 Q1                                                   *
 * Student Name: ......                                      *
 * Student ID  : ......                                      *
 * Date        : ......                                      *
 * Points      : Write points what you believe to deserve    *
 *                                                           *
 *************************************************************/
#include <stdio.h>

#define PLAINTEXTFILE "Files/Q1/PlainMessagesToSent.txt"
#define ENCODEDFILE "Files/Q1/EncodedMessages.txt"
#define CRYPTEDFILE "Files/Q1/CryptedMessages.txt"

/*************************************************************
 * Gets FILE* to write file and character to encode          *
 * uses encoding table to convert plain text to              *
 * encoded message                                           *
 *************************************************************/
void 
encode_and_write_to_file(FILE *f_out_ptr, char character);

/*************************************************************
 * Gets FILE* f_in_ptr to read from plain text file and      *
 * FILE* f_out_ptr to write message to encoded file          *
 * return number of characters read from plain text          *
 *************************************************************/
int 
encode_message(FILE *f_in_ptr, FILE *f_out_ptr);

/*************************************************************
 * Gets FILE* f_in_ptr to read from encoded text file and    *
 * FILE* f_out_ptr to write message to encrypted file        *
 * return encoded character number                           *
 *************************************************************/
int 
crypt_message(FILE *f_in_ptr, FILE *f_out_ptr);

/*************************************************************
 * Reads plane text, creates encoded and crypted text files  *
 *************************************************************/
int 
main(int argc, char* argv[])
{
	FILE *f_plane_ptr, *f_encoded_ptr, *f_crypted_ptr;

	/* exit program and print error if plain text file could not be opened to read */

	/* exit program and print error if encoded text file could not be opened to write */

	encode_message(f_plane_ptr, f_encoded_ptr);

	/* close plain and encoded files */

	/* exit program and print error if crypted text file could not be opened to write */

	/* exit program and print error if encoded text file could not be opened to read */

	crypt_message(f_encoded_ptr, f_crypted_ptr);

	/* close crypted and encoded files */

	return 0;
}

/*************************************************************
 * Gets FILE* to write file and character to encode          *
 * uses encoding table to convert plain text to              *
 * encoded message                                           *
 *************************************************************/
void 
encode_and_write_to_file(FILE *f_out_ptr, char character)
{

	/* Hint: Use switch case while encoding character 
	 *		 Keep number of 1s and use it in a loop to
	 *		 write to file encoded value. You are going to
	 *		 call fprintf in the loop just number of 1s times
	 *		 Do not forget adding 0 at the end of value
	 */
	

	/*
	 *
	 Some magic here
	 *
	 */
}

/*************************************************************
 * Gets FILE* f_in_ptr to read from plain text file and      *
 * FILE* f_out_ptr to write message to encoded file          *
 * return number of characters read from plain text          *
 *************************************************************/
int 
encode_message(FILE *f_in_ptr, FILE *f_out_ptr)
{
	/* Hint: Keep reading from plain text until end of file
	 *		 while reading per character call encode_and_write_to_file
	 *		 function.
	 */
	int counter = 0;
	
	/*
	 *
	 Some magic here
	 *
	 */

	return counter;
}

/*************************************************************
 * Gets FILE* f_in_ptr to read from encoded text file and    *
 * FILE* f_out_ptr to write message to encrypted file        *
 * return number of characters read from encoded text file   *
 *************************************************************/
int 
crypt_message(FILE *f_in_ptr, FILE *f_out_ptr)
{
	/* Hint: Keep reading from encoded text until end of file
	 *		 while reading per character check if it is equal 
	 *		 to 1 or 0 and according to character write file '*'
	 *		 '_'
	 *		 Do not forget adding '-' character to proper places
	 *       Check sample encrypted messages and read objective 3
	 *
	 */
	int counter = 0;
	
	/*
	 *
	 Some magic here
	 *
	 */

	return counter;
}