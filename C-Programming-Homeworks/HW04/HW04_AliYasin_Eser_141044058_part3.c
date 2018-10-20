/******************************************************************************
 *                                                        				      *
 * HW04 Q3                                                   			      *
 * Student Name: Ali Yasin Eser                              			      *
 * Student ID  : 141044058                                   			      *
 * Date        : 14/03/2015                                 			      *
 *                                                           			      *
 *****************************************************************************/
 
 /*Kutuphanelerin tanitilmasi*/
#include <stdio.h>

/*Dosyalar ve Dogru/Yanlis degerleri icin makrolar*/
#define TRUE 1
#define FALSE 0
#define CHARACTERFILE "Files/Q3/CharacterList.txt"
#define SAMPLEFILE "Files/Q3/Sample.txt"
#define ENCODEDFILE "Files/Q3/XUniversityEncoded.txt"
#define PLAINTEXTFILE "Files/Q3/XUniversityMessage.txt"
#define A_ON_ASCII 65
#define Z_ON_ASCII 90

/*Integer degerleri degistirmek icin */
void swap_int(int *a, int *b); 
/*Karakterleri degistirmek icin*/
void swap_char(char *a, char *b);
/*Harfleri siralamak icin*/
void sort(char *a, int a_num, char *b, int b_num, char *c, int c_num);
/*Alinan karakterin buyuk harf olmasini degerlendirmek icin*/
int  is_letter(char c);
/*Karakterleri okumak icin*/
int  read_character_list(FILE* f_in_ptr, char *c1, char *c2, char *c3);
/*Her karakterin kac kere kullanildigini saymak icin*/
void count_letters(FILE *f_in_ptr, char *c1, char *c2, char *c3);
/*Sifreli yazinin cozumu icin*/
void decode(FILE *f_in_ptr, FILE *f_out_ptr, char c1, char c2, char c3);


int 
main(int argc, char* argv[])
{
	/*Dosyalarin ve karakterlerin tanitilmasi*/
	FILE *f_character_list_ptr, *f_sample_file_ptr, 
	*f_encoded_ptr, *f_plain_text_ptr;
	int character_number;	/*3 karakter okunup okunmamasi durumu icin*/
	char c1, c2, c3;

	/*Karakterlerin alinacagi dosyanin okunmasi*/
	f_character_list_ptr = fopen(CHARACTERFILE, "r");
	/*Dosyanin acilmazsa program biter*/
	if(f_character_list_ptr == FALSE)
	{
		printf("Character list text has couldn't open to read.\n");
		return 0;
	}
	
	/*3'den az veya fazla karakter okunduysa program biter*/
	character_number = read_character_list( 
	f_character_list_ptr,  &c1,  &c2,  &c3);
	if(character_number != 3){
		return 0;}
	/*Karakterlerin okundugu dosyanin kapatilmasi*/
	fclose(f_character_list_ptr);
	/*Karakterlerin ne kadar kullanildigini anlamak icin ornek 
	* dosya, sifredeki karakterleri anlamak icin*/
	f_sample_file_ptr = fopen(SAMPLEFILE, "r");
	/*Dosyanin acilmazsa program biter*/
	if(f_sample_file_ptr == FALSE)
	{
		printf("Sample text has couldn't open to read.\n");
		return 0;
	}

	/*Karakterlerin ne kadar kullanildiginin bulunmasi*/
	count_letters(f_sample_file_ptr ,&c1, &c2, &c3);
	/*Ornek dosyanin kapatilmasi*/
	fclose(f_sample_file_ptr);
	/*Sifrelenmis dosyanin acilmasi*/
	f_encoded_ptr = fopen(ENCODEDFILE, "r");
	/*Dosya acilmazsa program biter*/
	if(f_encoded_ptr == FALSE)
	{
		printf("Encoded text has couldn't open to read.\n");
		return 0;
	}
	/*Sifrenin cozuldukten sonra yazilacagi dosya*/
	f_plain_text_ptr = fopen(PLAINTEXTFILE,"w");
	/*Dosya acilmazsa program biter*/
	if(f_plain_text_ptr == FALSE)
	{
		printf("Plain text has couldn't open to write.\n");
		return 0;
	}
	/*Sifrenin cozulmesi*/
	decode(f_encoded_ptr, f_plain_text_ptr,  c1,  c2,  c3);
	/*Dosyanin kapatilmasi*/
	fclose(f_encoded_ptr);
	fclose(f_plain_text_ptr);
	return 0;
}

/*Integer 2 degerin ara degisken kullanilarak yer degistirmesi*/
void swap_int(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

/*Karakter 2 degerin ara degisken kullanilarak yer degistirmesi*/
void swap_char(char *a, char *b)
{
	char temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

/*Elde edilen karakter ve kullanilma sayilarinin siralanmasi*/
void sort(char *a, int a_num, char *b, int b_num, char *c, int c_num)
{
	if(a_num < c_num){
		swap_int(&a_num, &c_num);
		swap_char(a,c); }
	if(a_num < b_num){
		swap_int(&a_num, &b_num);
		swap_char(a,b); }
	if(b_num < c_num){
		swap_int(&b_num, &c_num);
		swap_char(b,c); }		
}

/*Okunan karakterin harf ve buyuk olma durumunu degerlendirme*/
int is_letter(char c)
{
	if(c >= A_ON_ASCII && c <= Z_ON_ASCII)
		return TRUE;
	else
		return FALSE;
}

/*Karakterleri okuyup kontrol eden fonksiyon*/
int read_character_list(FILE* f_in_ptr, char *c1, char *c2, char *c3)
{	
	int counter = 0;	/*Okunulan harf sayisi*/
	char temp;	/*Atanmadan once kontrol edilmesi icin degisken*/
	int big_letter;	/*Buyuk harf kontrolu icin degisken*/
	int end_of_file_control;	/*Dosyanin bitisini kontrol*/
	int big_letter1, /*Okunan karakterlerin buyuk harf olup olmadigini*/
		big_letter2, /* kontrol etmek icin her karakter degiskenine   */
		big_letter3; /* kontrol yapilir. Esitlik yoksa atanir         */
	int null_letter; /* Ucten daha fazla karakter icin 				  */							
	char c4;	/*Ucten fazla karakterden sonrasi icin*/

/*Ilk basta kontrol amacli olarak olmamasi gereken degerler verilir*/
	*c1='a'; *c2='b'; *c3='c'; c4 = 'n';
	end_of_file_control = fscanf(f_in_ptr, "%c", &temp);/*Ilk karakter*/
	while(end_of_file_control != EOF)
	{
		/*Her karakter icin buyuk harf kontrolu*/
		/*Onceden atanmis degerlerin atlanmasi icin*/
		big_letter = is_letter(temp);
		big_letter1 = is_letter(*c1);
		big_letter2 = is_letter(*c2);
		big_letter3 = is_letter(*c3);
		null_letter = is_letter(c4);	
		/*Okunan karakter buyuk bir harfse donguye girilir*/
		if(big_letter == TRUE )
		{
			if(big_letter != big_letter1){
				*c1 = temp;
				counter += 1;}
			else if(big_letter != big_letter2){
				*c2 = temp;
				counter += 1;}
			else if(big_letter != big_letter3){
				*c3 = temp;
				counter += 1;}
			else if(big_letter != null_letter){
				c4 = '\0';} /* NULL, istenmeyen fazla karakterlere*/
		}
		/*Guncelleme kismi*/
		end_of_file_control = fscanf(f_in_ptr, "%c", &temp);
	}
	return counter;
}

/*Karakterlerin kac kere kullanildiginin bulunmasi ve siralanmasi*/
void count_letters(FILE *f_in_ptr, char *c1, char *c2, char *c3)
{
	/*Karakterlerin kullanim sayilarini tutacak count'lar*/
	int count_for_most=0, count_for_middle=0, count_for_least=0;
	int end_of_file_control;
	char rec_char;
	/*Karakterleri tek tek okuyup count artiran dongu*/
	end_of_file_control = fscanf(f_in_ptr, "%c", &rec_char);
	while(end_of_file_control != EOF)
	{
		if(rec_char == *c1){
			count_for_most += 1;}
		else if(rec_char == *c2){
			count_for_middle += 1;}
		else if(rec_char == *c3){
			count_for_least += 1;}
		end_of_file_control = fscanf(f_in_ptr, "%c", &rec_char);		
	}
	/*Karakterleri kullanimlarina gore siralayip duzenleme */
	sort(c1, count_for_most, c2, count_for_middle, c3, count_for_least);
}
/*Sifrenin cozulmesi icin kullanilan fonksiyon*/
void decode(FILE *f_in_ptr, FILE *f_out_ptr, char c1, char c2, char c3)
{
	char rec_char;
	int end_of_file_control;
	int count_of_ones = 0;
	/*0 gorene kadar 1'ler artirilir, count guncellenir*/
	/*count'lara gore switch ile harfi yazdirir*/
 	end_of_file_control = fscanf(f_in_ptr,"%c", &rec_char);
 	for(end_of_file_control=0;
		end_of_file_control != EOF;
		end_of_file_control = fscanf(f_in_ptr,"%c", &rec_char))
		{
			if(rec_char == '1'){
				count_of_ones +=1;}
			else if(rec_char == '0'){
				switch(count_of_ones)
				{
					case 0:
						fprintf(f_out_ptr, "%c", c1);
						break;
					case 1:
						fprintf(f_out_ptr, "%c", c2);
						break;
					case 2:
						fprintf(f_out_ptr,"%c", c3);
						break;
					default:
						break;
				}
				count_of_ones = 0;}			
		}
}

/*****************************************************************************
 * 						End of HW04 Q3                       				 *
 *****************************************************************************/
