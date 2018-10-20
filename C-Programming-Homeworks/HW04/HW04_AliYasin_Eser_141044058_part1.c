/*************************************************************
 *                                                           *
 * HW04 Q1                                                   *
 * Student Name: Ali Yasin Eser                              *
 * Student ID  : 141044058                                   *
 * Date        : 13/03/2015                                  *
 *                                                           *
 *************************************************************/
 
 /*Kutuphanelerin tanitimi*/
#include <stdio.h>

/*Dosyalar ve degerler icin makrolar*/
#define PLAINTEXTFILE "Files/Q1/PlainMessagesToSent.txt"
#define ENCODEDFILE "Files/Q1/EncodedMessages.txt"
#define CRYPTEDFILE "Files/Q1/CryptedMessages.txt"
#define TRUE 1
#define FALSE 0
#define FOR_M_AND_N 4	/*M ve N degerini 4 yapar, 5 kere doner*/

/*Fonksiyonlarin tanitilmasi*/
void encode_and_write_to_file(FILE *f_out_ptr, char character);
int encode_message(FILE *f_in_ptr, FILE *f_out_ptr);
int crypt_message(FILE *f_in_ptr, FILE *f_out_ptr);

int
main(int argc, char* argv[])
{
	/*Kullanilacak dosyanin tanitilmasi*/
	FILE *f_plane_ptr, *f_encoded_ptr, *f_crypted_ptr;
	/*Dosya acilmazsa program kapanir*/
	f_plane_ptr = fopen(PLAINTEXTFILE, "r");
	if(f_plane_ptr == FALSE)
	{
		printf("Plaint text has couldn't open to read.\n");
		return 0;
	}
	/*Dosya acilmazsa program kapanir*/
	f_encoded_ptr = fopen(ENCODEDFILE, "w");
	if(f_encoded_ptr == FALSE)
		{
			printf("Encoded text couldn't open to write.\n");
			return 0;
		}

	/*Mesajin 1 ve 0'lara donusturulmesi*/
	encode_message(f_plane_ptr, f_encoded_ptr);
	/*Dosyalarin kapatilmasi*/
	fclose(f_plane_ptr);
	fclose(f_encoded_ptr);
	/*Dosya acilmazsa program kapanir*/
	f_crypted_ptr = fopen(CRYPTEDFILE, "w");
	if(f_plane_ptr == FALSE)
	{
		printf("Crypted text couldn't open to write.\n");
		return 0;
	}
	/*Dosya acilmazsa program kapanir*/
	f_encoded_ptr = fopen(ENCODEDFILE, "r");
	if(f_plane_ptr == FALSE)
	{
		printf("Crypted text couldn't open to read.\n");
		return 0;
	}

	/*1 ve 0'ların * ve _ karakterine cevirilmesi, kurallarin uygulanmasi*/
	crypt_message(f_encoded_ptr, f_crypted_ptr);
	/*Dosya acilmazsa program kapanir*/
	fclose(f_crypted_ptr);
	fclose(f_encoded_ptr);


	/* close crypted and encoded files */

	return 0;
}

/*Karakterleri dosyadan okuyup tabloya gore cevirir*/
void encode_and_write_to_file(FILE *f_out_ptr, char character)
{
	int counter_of_ones;	/*1 degerinin tutulacagi counter*/

	switch(character)
	{
		case 'E' :
		case 'e' :
			fprintf(f_out_ptr, "0");
			break;
		case 'I':
		case 'i':
			for(counter_of_ones=0;
				counter_of_ones < 1;
				counter_of_ones++)
				{
					fprintf(f_out_ptr , "1");
				}
			fprintf(f_out_ptr, "0");
			break;
		case ' ':
			for(counter_of_ones=0;
				counter_of_ones < 2;
				counter_of_ones++)
				{
					fprintf(f_out_ptr , "1");
				}
			fprintf(f_out_ptr, "0");
			break;
		case 'T':
		case 't':
			for(counter_of_ones=0;
				counter_of_ones < 3;
				counter_of_ones++)
					fprintf(f_out_ptr , "1");
			fprintf(f_out_ptr, "0");
			break;
		case 'C':
		case 'c':
			for(counter_of_ones=0;
				counter_of_ones < 4;
				counter_of_ones++)
				fprintf(f_out_ptr , "1");
			fprintf(f_out_ptr, "0");
			break;
		case 'N':
		case 'n':
			for(counter_of_ones=0;
				counter_of_ones < 5;
				counter_of_ones++)
					fprintf(f_out_ptr , "1");
			fprintf(f_out_ptr, "0");
			break;
		case 'A':
		case 'a':
			for(counter_of_ones=0;
				counter_of_ones < 6;
				counter_of_ones++)
					fprintf(f_out_ptr , "1");
			fprintf(f_out_ptr, "0");
			break;
		case 'G':
		case 'g':
			for(counter_of_ones=0;
				counter_of_ones < 7;
				counter_of_ones++)
					fprintf(f_out_ptr , "1");
			fprintf(f_out_ptr, "0");
			break;
		case 'B':
		case 'b':
			for(counter_of_ones=0;
				counter_of_ones < 8;
				counter_of_ones++)
					fprintf(f_out_ptr , "1");
			fprintf(f_out_ptr, "0");
			break;
		case 'Z':
		case 'z':
			for(counter_of_ones=0;
				counter_of_ones < 9;
				counter_of_ones++)
					fprintf(f_out_ptr , "1");
			fprintf(f_out_ptr, "0");
			break;
		case 'H':
		case 'h':
			for(counter_of_ones=0;
				counter_of_ones < 10;
				counter_of_ones++)
					fprintf(f_out_ptr , "1");
			fprintf(f_out_ptr, "0");
			break;
		case 'L':
		case 'l':
			for(counter_of_ones=0;
				counter_of_ones < 11;
				counter_of_ones++)
					fprintf(f_out_ptr , "1");
			fprintf(f_out_ptr, "0");
			break;
		case 'U':
		case 'u':
			for(counter_of_ones=0;
				counter_of_ones < 12;
				counter_of_ones++)
					fprintf(f_out_ptr , "1");
			fprintf(f_out_ptr, "0");
			break;
		case 'V':
		case 'v':
			for(counter_of_ones=0;
				counter_of_ones < 13;
				counter_of_ones++)
					fprintf(f_out_ptr , "1");
			fprintf(f_out_ptr, "0");
			break;
		case 'R':
		case 'r':
			for(counter_of_ones=0;
				counter_of_ones < 14;
				counter_of_ones++)
					fprintf(f_out_ptr , "1");
			fprintf(f_out_ptr, "0");
			break;
		case 'S':
		case 's':
			for(counter_of_ones=0;
				counter_of_ones < 15;
				counter_of_ones++)
					fprintf(f_out_ptr , "1");
			fprintf(f_out_ptr, "0");
			break;
		case 'Y':
		case 'y':
			for(counter_of_ones=0;
				counter_of_ones < 16;
				counter_of_ones++)
					fprintf(f_out_ptr , "1");
			fprintf(f_out_ptr, "0");
			break;
		case '\n':
			break;
		default:
			fprintf(f_out_ptr , "%c", character);
	}


}

int encode_message(FILE *f_in_ptr, FILE *f_out_ptr)
{
	int counter = 0;
	char rec_char;	/*Okunan karakter degerleri icin*/
	int end_of_file_control;
	/*Dosyadan karakterleri okur, fonksiyona yollar*/
 	fscanf(f_in_ptr,"%c", &rec_char);
	for(end_of_file_control=0;
		end_of_file_control != EOF;
		end_of_file_control = fscanf(f_in_ptr,"%c", &rec_char)){	
			encode_and_write_to_file( f_out_ptr, rec_char );
			counter += 1;}
	return counter;
}

int crypt_message(FILE *f_in_ptr, FILE *f_out_ptr)
{
	int counter = 0;
	char rec_char;
	int end_of_file_control;
    int M=FOR_M_AND_N, N=FOR_M_AND_N;	/* '-' karakteri icin*/
    int count_for_dash;	/*M icin kontrol degikeni*/
	count_for_dash = M;	/*ilk atama*/



	end_of_file_control = fscanf(f_in_ptr,"%c", &rec_char);
    while(end_of_file_control != EOF)
    {
        if(rec_char == '1'){
            fprintf(f_out_ptr, "*");
            counter++;}
        else if(rec_char == '0'){
            fprintf(f_out_ptr, "_");
            counter++;}
        else{
            fprintf(f_out_ptr ,"%c", rec_char);
            counter++;}


        if(count_for_dash != 0)
            count_for_dash--;
        else 
        {
            fprintf(f_out_ptr, "-");
			counter++;
        	if(M != 0 ){
                M--;
				count_for_dash = M;}
            else{
                M=N;
				count_for_dash = M;}
		}

        end_of_file_control = fscanf(f_in_ptr," %c ", &rec_char);
    }
	return counter;
}
/*****************************************************************************
 * 						End of HW04 Q1                       				 *
 *****************************************************************************/
