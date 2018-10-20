/*************************************************************
 *                                                           *
 * HW06_Part2                                                *
 * Student Name: Ali Yasin ESER                              *
 * Student ID  : 141044058                                   *
 * Date        : 05.04.2015                                  *
 *                                                           *
 *************************************************************/
/*Kutuphane ve makrolarin tanimlanmasi*/
#include <stdio.h>
#include <string.h>
#define VOWELS "Vowels.txt"
#define NOUNS "Nouns.txt"
#define PLURAL "Plural.txt"
#define FOR_ARR 8	/*Kurallarin harfleri icin*/
#define FOR_NOUN 20	/*Kelimeler icin*/
#define FOR_PLUR 30	/*Kelimeler ve donusumler icin*/
#define FOR_COUNT 0
#define FOR_LIMIT 10

/*tip tanimlamasi*/
typedef enum { FALSE, TRUE } bool;
typedef enum { HARD, SOFT, CONSONANT_MAJ } major_type;
typedef enum { FLAT, ROUND, CONSONANT_MIN } minor_type;


/*Fonksiyonlarin tanitilmasi*/
bool is_major_vh_word(const char* word,
	 const char* v_hard, const char* v_soft);
	 
major_type major(const char ch1, const char* v_hard, const char* v_soft);
bool is_minor_vh_word( const char* word, 
	const char* v_flat, const char* v_soft);
	
minor_type minor(const char ch1, const char* v_flat, const char* v_round);

major_type find_last_type(const char* word, 
const char *v_hard , const char * v_soft);
 
char* make_plural(const char* noun , char* plural_noun,
const char * v_hard , const char * v_soft );

int
main()
{
	char buffer;
	bool control;
	int i;
	char nouns[FOR_NOUN], 
		 plural[FOR_PLUR], 
		 hard[FOR_ARR],	/*Sert unluler*/
		 soft[FOR_ARR],	/*Yumusak unluler*/
		 flat[FOR_ARR],	/*Duz unluler*/
		 round[FOR_ARR]; /*Yuvarlak unluler*/
	/*Dosyalarin acilmasi*/
	FILE *inpvow=fopen(VOWELS, "r");
	FILE *inpnouns=fopen(NOUNS, "r");
	
	if(inpvow == NULL)/* Acilmazsa uyari*/
		printf("The input file can't be read. Don't trust the output!");
		
	if(inpnouns == NULL)/* Acilmazsa uyari*/
		printf("The input file can't be read. Don't trust the output!"); 
	
	/*Degerlerin alinip atanma yapilmasi*/
     fscanf(inpvow, "%s", hard); 
     fscanf(inpvow, "%s", soft);
     fscanf(inpvow, "%s", flat);
     fscanf(inpvow, "%s", round);         
  
    /*printf("%s\n" , hard);
    printf("%s\n" , soft);
    printf("%s\n" , flat);
    printf("%s\n" , round);*/

	/* Duzenleme icin*/
    for(i=FOR_COUNT;i<FOR_LIMIT;i++)
      printf(" ");

    printf("%-10s%-10s", "Major", "Minor");
    printf("\n");
	/*Kelimelerin okunmasi*/
    for(i=fscanf(inpnouns, "%s", nouns);
        i != 0 && i != EOF;
        i=fscanf(inpnouns, "%s", nouns))
    {
       printf("%-10s", nouns);
       /*Buyuk unlu uyumu kontrolu*/
        control = is_major_vh_word( nouns, hard, soft );
      	if(control == TRUE)
        	printf("%-10c", 'T');
        else if(control == FALSE)
        	printf("%-10c", 'F');
        else
        	printf("There is a problem, check that please.\n");
        /*Kucuk unlu uyumu kontrolu*/
       	control = is_minor_vh_word( nouns, flat, round );
       	
        if(control == TRUE)
        	printf("%-10c\n", 'T');
        else if(control == FALSE)
        	printf("%-10c\n", 'F');
        else
        	printf("There is a problem, check that please.\n");
        	
    }
   

    


	return 0;
}


/*Kelimenin buyuk unlu uyumuna bakip kontrol ediyor*/
bool is_major_vh_word(const char* word, const char* v_hard, const char* v_soft)
{


	int i;	/*counter*/
	bool flag=TRUE;	/*Aksi durum olmadikca dogru gonderir*/
	major_type control;
	
	
	
	/*Kelimeyi okumasi ve degerlerndirmeye yollamasi icin*/
    for(i=FOR_COUNT; word[i] != '\0' && control != CONSONANT_MAJ; i++)
    	control = major( word[i], v_hard, v_soft );
        
	
	if(control == HARD)
	{
	    do{
	        i++;
	        control = major( word[i], v_hard, v_soft );
	      }
	    while( control != SOFT || word[i] != '\0');
	        if(control == SOFT)
	            flag= FALSE;
	 }
	else if(control == SOFT)
	{
	    do{
	        i++;
	        control = major( word[i], v_hard, v_soft );
	      }
	    while( control != HARD || word[i] != '\0');
	    if(control == HARD)
	        flag= FALSE;
	}
	
	return flag;
}
/*karakterin durumunu kontrol ediyor*/
major_type major(const char ch1, const char* v_hard, const char* v_soft)
{
	
	int counter;
	major_type cond = CONSONANT_MAJ;	/*Aksi yoksa unsuz dondurur*/
	
	for(counter=FOR_COUNT; cond != HARD && v_hard[counter] != '\0'; counter++)
	    if(ch1 == v_hard[counter])
	        cond = HARD;
	for(counter=FOR_COUNT; cond != SOFT && v_hard[counter] != '\0'; counter++)
	    if(ch1 == v_soft[counter])
	        cond = SOFT;
	   if(cond== SOFT)
	   
	
	return cond;
	
}
/*Kelimenin kucuk unlu uyumuna bakip kontrol ediyor*/
bool is_minor_vh_word( const char* word, 
const char* v_flat, const char* v_round)
{
	int i;
	bool flag=TRUE;
	major_type control;
	
	
	/*Unsuz'e gelince duracak, ilk elemanin hard mi soft olduguna bakilacak */
    for(i=FOR_COUNT; word[i] != '\0' && control != CONSONANT_MIN; i++)
        control = minor( word[i], v_flat, v_round );
	
	/*Kontrol*/
	if(control == FLAT)
	{
	    do{
	        i++;
	        control = minor( word[i], v_flat, v_round );
	      }
	    while( control != ROUND || word[i] != '\0');
	        if(control == ROUND)
	            flag= FALSE;
	 }
	else if(control == ROUND)
	{
	    do{
	        i++;
	        control = minor( word[i], v_flat, v_round );
	      }
	    while( control != FLAT || word[i] != '\0');
	    if(control == FLAT)
	        flag= FALSE;
	}
	
	return flag;
}
/*karakterin durumunu kontrol ediyor*/
minor_type minor(const char ch1, const char* v_flat, const char* v_round)
{
	int counter;
	minor_type cond = CONSONANT_MIN;	/*Aksi yoksa unsuz dondurur*/
	
	for(counter=FOR_COUNT; cond != FLAT && v_flat[counter] != '\0'; counter++)
	    if(ch1 == v_flat[counter])
	        cond = FLAT;
	for(counter=FOR_COUNT; cond != ROUND && v_round[counter] !='\0'; counter++)
	    if(ch1 == v_round[counter])
	        cond = ROUND;
	   
	
	return cond;
}
/*Son unluyu bulur*/
major_type find_last_type(const char* word, 
const char *v_hard , const char * v_soft)
{
	int i;
	major_type flag=CONSONANT_MAJ;
	major_type sec_flag=CONSONANT_MAJ;
	
	for( i=FOR_COUNT; i < strlen(word); i++ ){
		flag = major( word[i], v_hard, v_soft );
		if( flag != CONSONANT_MAJ )
			sec_flag=flag;
		}
	
	return sec_flag;
	
}
/*Son unlu harfe gore cogul eki verir*/
char* make_plural(const char* noun , char* plural_noun,
const char * v_hard , const char * v_soft )
{
	major_type cond;
	int length;	
	
	cond = find_last_type( noun, v_hard, v_soft );
	
	length = strlen( noun);
	
	if( cond == HARD ){
		strncpy( plural_noun, noun, length );
		strcat( plural_noun, "lar" );}
	else if( cond == SOFT ){
		strncpy( plural_noun, noun, length );
		strcat( plural_noun, "ler" );}
	else
		printf("Don't trust the output!\n");		
	
	return plural_noun;
	
}
/*###########################################################################*/
/*              End of HW06_Ali_Yasin_ESER_141044058_part2.c                 */
/*###########################################################################*/
