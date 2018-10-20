/*************************************************************
 *                                                           *
 * HW04 Q2                                                   *
 * Student Name: ......                                      *
 * Student ID  : ......                                      *
 * Date        : ......                                      *
 * Points      : Write points what you believe to deserve    *
 *                                                           *
 *************************************************************/
#include <stdio.h>

#define PLAINTEXTFILE "Files/Q2/ReceivedMessage.txt"
#define ENCODEDFILE "Files/Q2/EncodedInput.txt"
#define CRYPTEDINPUT "Files/Q2/CryptedInput.txt"

/*************************************************************
 * Gets FILE* to write file and character to decode          *
 * uses encoding table to convert encoded message to         *
 * plain text message                                        *
 *************************************************************/
void 
decode_and_write_to_file(FILE *f_out_ptr, int number_of_ones);

/*************************************************************
 * Gets FILE* f_in_ptr to read from encoded text file and    *
 * FILE* f_out_ptr to write message to plain text file       *
 * return number of characters read from encoded text        *
 *************************************************************/
int 
decode_message(FILE *f_in_ptr, FILE *f_out_ptr);

/*************************************************************
 * Gets FILE* f_in_ptr to read from encrypted text file and  *
 * FILE* f_out_ptr to write message to encoded file          *
 * return encrypted character number                         *
 *************************************************************/
int 
decrypt_message(FILE *f_in_ptr, FILE *f_out_ptr);

/*************************************************************
 * Reads encrypted text and creates encoded and              *
 * plain text files                                          *
 *************************************************************/
int 
main(int argc, char* argv[])
{
	FILE *f_plane_ptr, *f_encoded_ptr, *f_crypted_ptr;

	/* exit program and print error if encrypted text file could not be opened to read */

	/* exit program and print error if encoded text file could not be opened to write */

	decrypt_message(f_crypted_ptr, f_encoded_ptr);

	/* close encrypted and encoded files */

	/* exit program and print error if plain text file could not be opened to write */

	/* exit program and print error if encoded text file could not be opened to read */

	decode_message(f_encoded_ptr, f_plane_ptr);

	/* close encoded and plain files */

	return 0;
}

/*************************************************************
 * Gets FILE* to write file and character to decode          *
 * uses encoding table to convert encoded message to         *
 * plain text message                                        *
 *************************************************************/
void 
decode_and_write_to_file(FILE *f_out_ptr, int number_of_ones)
{

	/* Hint: Use switch case while encoding character 
	 *		 According to number_of_ones write character 
	 *		 to file
	 */
	

	/*
	 *
	 Some magic here
	 *
	 */
	
}

/*************************************************************
 * Gets FILE* f_in_ptr to read from encoded text file and    *
 * FILE* f_out_ptr to write message to plain text file       *
 * return number of characters read from encoded text        *
 *************************************************************/
int 
decode_message(FILE *f_in_ptr, FILE *f_out_ptr)
{
	/* Hint: While reading from encoded text file keep reading 
	 *		 character by character. Use ASCII difference from 0
	 *		 to determine number is 0 or 1. If we try reading it
	 *		 as integer, it overflows. Overflow is bad if you are 
	 *		 not hacker and do not want to crash system deliberately.
	 *		 Call decode_and_write_to_file function when you detect 0.
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

/*************************************************************
 * Gets FILE* f_in_ptr to read from encrypted text file and  *
 * FILE* f_out_ptr to write message to encoded file          *
 * return encrypted character number                         *
 *************************************************************/
int 
decrypt_message(FILE *f_in_ptr, FILE *f_out_ptr)
{
	/* Hint: While reading from encrypted text file check if character 
	 *		 equals to '*' or '_' and write to file 1 or 0
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