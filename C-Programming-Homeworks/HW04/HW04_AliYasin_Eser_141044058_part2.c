/*************************************************************
 *                                                           *
 * HW04 Q2                                                   *
 * Student Name: Ali Yasin Eser                              *
 * Student ID  : 141044058                                   *
 * Date        : 12/03/2015                                  *
 *                                                           *
 *************************************************************/
 
 /*Kutuphanelerin tanitilmasi*/
#include <stdio.h>
/*Dosya ve degerler icin makrolar*/
#define PLAINTEXTFILE "Files/Q2/ReceivedMessage.txt"
#define ENCODEDFILE "Files/Q2/EncodedInput.txt"
#define CRYPTEDINPUT "Files/Q2/CryptedInput.txt"
#define TRUE 1
#define FALSE 0

/*Fonksiyonlarin tanitilmasi*/
void decode_and_write_to_file(FILE *f_out_ptr, int number_of_ones);
int decode_message(FILE *f_in_ptr, FILE *f_out_ptr);
int decrypt_message(FILE *f_in_ptr, FILE *f_out_ptr);


int 
main(int argc, char* argv[])
{
	/*Dosyalar icin pointer tanimlanmasi*/
	FILE *f_plane_ptr, *f_encoded_ptr, *f_crypted_ptr;
	/*Dosyalarin ve karakterlerin tanitilmasi*/
	f_crypted_ptr = fopen(CRYPTEDINPUT, "r");
	if(f_crypted_ptr == FALSE){
		printf("Crypted text has couldn't open to read.\n");
		return 0;}
	/*Dosyalarin ve karakterlerin tanitilmasi*/
	f_encoded_ptr = fopen(ENCODEDFILE, "w");
	if(f_encoded_ptr == FALSE){
		printf("Encoded text has couldn't open to write.\n");
		return 0;}
	/*'*' ve '_' karakterlerinin 1 ve 0'da donusturulmesi*/
	decrypt_message(f_crypted_ptr, f_encoded_ptr);
	/*Dosyalarin kapatilmasi*/
	fclose(f_crypted_ptr);
	fclose(f_encoded_ptr);
	/*Dosyalarin ve karakterlerin tanitilmasi*/
	f_plane_ptr = fopen(PLAINTEXTFILE, "w");
	if(f_encoded_ptr == FALSE){
		printf("Plain text has couldn't open to write.\n");
		return 0;}
	/*Dosyalarin ve karakterlerin tanitilmasi*/
	f_encoded_ptr = fopen(ENCODEDFILE, "r");
	if(f_encoded_ptr == FALSE){
		printf("Encoded text has couldn't open to read.\n");
		return 0;}
	/*1 ve 0'larin yaziya cevirilmesi*/
	decode_message(f_encoded_ptr, f_plane_ptr);
	/*Dosyalarin kapatilmasi*/
	fclose(f_plane_ptr);
	fclose(f_encoded_ptr);

	return 0;
}

/*1 rakaminin sayisina gore tablodaki harfi yazan fonksiyon*/
void decode_and_write_to_file(FILE *f_out_ptr, int number_of_ones)
{
	char rec_char;	
	switch(number_of_ones){
		case 0:
				fprintf(f_out_ptr ,"E");
				break;
		case 1:
				fprintf(f_out_ptr ,"I");
				break;
		case 2:
				fprintf(f_out_ptr ," ");
				break;
		case 3:
				fprintf(f_out_ptr ,"T");
				break;
		case 4:
				fprintf(f_out_ptr ,"C");
				break;
		case 5:
				fprintf(f_out_ptr ,"N");
				break;
		case 6:
				fprintf(f_out_ptr ,"A");
				break;
		case 7:
				fprintf(f_out_ptr ,"G");
				break;
		case 8:
				fprintf(f_out_ptr ,"B");
				break;
		case 9:				
				fprintf(f_out_ptr ,"Z");
				break;
		case 10:				
				fprintf(f_out_ptr ,"H");
				break;
		case 11:				
				fprintf(f_out_ptr ,"L");
				break;
		case 12:				
				fprintf(f_out_ptr ,"U");
				break;
		case 13:		
				fprintf(f_out_ptr ,"V");
				break;
		case 14:				
				fprintf(f_out_ptr ,"R");
				break;
		case 15:				
				fprintf(f_out_ptr ,"S");
				break;
		case 16:				
				fprintf(f_out_ptr ,"Y");
				break;
		}
}

/*1 rakamini okuyup fonksiyona yollar*/
int decode_message(FILE *f_in_ptr, FILE *f_out_ptr)
{	
	int counter = 0;
	int count_of_ones=0;
	char rec_char;
	int end_of_file_control;

 	fscanf(f_in_ptr,"%c", &rec_char);
 	for(end_of_file_control=0;
		end_of_file_control != EOF;
		end_of_file_control = fscanf(f_in_ptr,"%c", &rec_char))
		{
			if(rec_char == '1'){
				count_of_ones +=1;
				counter += 1;}
			else if(rec_char == '0'){
				decode_and_write_to_file( f_out_ptr, count_of_ones );
				count_of_ones = 0;}			
				counter += 1;
		}
	return counter;
}

/*'*' ve '_' karakterlerini okuyup 1 ve 0'a cevirir*/
int decrypt_message(FILE *f_in_ptr, FILE *f_out_ptr)
{
	int counter = 0;
	int end_of_file_control;
	char rec_char;
	
 	fscanf(f_in_ptr,"%c", &rec_char);
 	for(end_of_file_control=0;
		end_of_file_control != EOF;
		end_of_file_control = fscanf(f_in_ptr,"%c", &rec_char))
		{
		
			if(rec_char == '*'){
				fprintf(f_out_ptr, "1");
				counter += 1;}
			else if(rec_char == '_'){
				fprintf(f_out_ptr, "0");}			
				counter += 1;
		}
	return counter;
}
/*****************************************************************************
 * 						End of HW04 Q2                       				 *
 *****************************************************************************/
