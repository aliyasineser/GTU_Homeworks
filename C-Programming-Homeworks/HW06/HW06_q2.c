/*Author : Bekircan Ağaoğlu , Modified by : Meltem Çetiner  */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define VOWELS "Vowels.txt"
#define NOUNS "Nouns.txt"
#define PLURALS "Plural.txt"
/* Caution! If you want process nouns more than current constant value you have to change value below		*/		
#define NUM_NOUN 20
#define FOUR 4

typedef enum {FALSE, TRUE} bool;
typedef enum {HARD, SOFT, CONS_MAJ} major_type;
typedef enum {FLAT, ROUND, CONS_MIN} minor_type;

bool major_vh_word(const char word[], const char* n);
major_type is_major(const char ch, const char* n);
bool minor_vh_word(const char* word, const char* n);
minor_type is_minor(const char ch1, const char* n);
void make_plural(const char* noun , char* plural_noun, const char* n); 
major_type find_last_type(const char* word,const char* n);

int main()
{
	char vowels[FOUR*3],   	/*hard,soft,flat,round*/ 
	     nouns[NUM_NOUN][15],  	/*nouns*/
	     plurals[NUM_NOUN][18];	/*nouns+lar/ler =plurals*/
	int i, j,counter=0;
	char empty;

	FILE *read, *write;
	printf("Reading the vowels..\n\n");
	read = fopen(VOWELS, "r");
	
        if(!read)   printf(" The file [ %s ] couldn't be found...\n",VOWELS);

	/* read vowels in file. */
	for(i=0; i < FOUR ; i++)
	{
		for(j=0; j< 3 ; j++)	
		{
			fscanf(read, "%c", &vowels[(i*3)+j]);	
		}
		fscanf(read, "%c", &empty);	
	}
		
	
	printf("Reading the nouns..\n\nThe maintaince of the harmonies:\n\n	 Major	 Minor\n\n");		
	
	read = fopen(NOUNS, "r");
        //if(read!)   printf(" The file [ %s ] couldn't be found...\n",NOUNS);

	write = fopen(PLURALS, "w");
	
	for(i=0; i<NUM_NOUN && (fscanf(read, "%s", &nouns[i][0])==1); i++ ,counter++)
	{		
		printf("%s", &nouns[i][0]);  /* print the noun  */
		
		/* find whether the noun maintaince the major and the minor harmony and print T for true and F otherwise  */
		if(major_vh_word(&nouns[i][0], vowels) == TRUE)
			printf("	   T");
		else
			printf("	   F");
		
		if(minor_vh_word(&nouns[i][0], vowels) == TRUE)
			printf("	   T\n\n");
		else
			printf("	   F\n\n");
		
		/* create plural of the noun */
		make_plural(&nouns[i][0], &plurals[i][0], vowels); 
		
		/* write the plural */
		fprintf(write, "%s ", &plurals[i][0]);
	}	
		
	fclose(read);
	fclose(write);
	
	printf("Writing the plurals of the nouns...\n\n");

	return 0;
}	

bool major_vh_word(const char word[],const char* n)
{
	major_type type2=CONS_MAJ, type1=CONS_MAJ;
	bool flag = TRUE;
	int i=0, string_lenght;
	
	string_lenght = strlen(word);
		
	for(i=0; i < string_lenght &&  type1==CONS_MAJ ; i++) /*find the first vowel and its major type*/
		type1 = is_major(word[i], n);
		
	for(i; i < string_lenght &&  flag ; i++)
	{	
		type2 = is_major(word[i], n);  /*find the others and its major type*/
		if(   type2 != CONS_MAJ  )     /*if it s vowel */
		{
			if( type1 != type2 )   	flag = FALSE;  /*and not maintaince the harmony  , return  false*/
			
			type1 = type2; /*and if it maintains the harmony ,change new first type and continue..*/
		}
	}
	
	return flag;	
}

major_type is_major(const char ch,const char* n)
{
	int i;
	bool flag = FALSE;
	major_type type  = CONS_MAJ;
	
	/* check if input character is hard or soft */ 
	for( i = 0 ; i < 3 && !flag ; i++)
	{
 		if(ch == n[ ((int)HARD*3) + i ])  
		{
			type = HARD;
			flag = TRUE;
		}	
		else if(ch == n[ ((int)SOFT*3)+ i ])
		{
			type = SOFT;
			flag = TRUE;
		}
	}
	
	return type;
}	

bool minor_vh_word(const char* word,const char* n)
{
        if(!major_vh_word(word,n)) return FALSE;
	else
	{
		minor_type min_type1=CONS_MIN, min_type2=CONS_MIN;
		major_type maj_type1=CONS_MAJ, maj_type2=CONS_MAJ;
		bool flag = TRUE;
		int i = 0, string_lenght;
	
		string_lenght = strlen(word);/*  find word's lenght */
	
		/* find the first vowel and its minor and major type */
		for(i; i < string_lenght && min_type1 == CONS_MIN; i++)
		{	
			min_type1 = is_minor(word[i], n);
		
		}
		
		for(i; i < string_lenght && flag; i++)
		{
			min_type2 = is_minor(word[i], n);
						
			if(  min_type2 != CONS_MIN )
	            	{
				if( min_type1 == FLAT )
                        	{		
					if( min_type2 != FLAT )    /*a--> a or e,i-->e,i */
						 flag = FALSE;
				}
		      		else          /*o-->u,a  or u -->u,a*/
				{
					if( word[i] == 'o' )  flag  = FALSE;
				}
			}
		}

		
        	return flag;	
	}
}	

minor_type is_minor(const char ch,const char* n)
{
	int i, flag = FALSE;
	minor_type type = CONS_MIN;
	
	/* check if input character is flat or round */ 
	for(i=0; i < 3 && !flag; i++)
	{
		if(ch == n[((2+(int)FLAT)*3)+i])
		{
			type = FLAT;
			flag = TRUE;
		}	
		else if(ch == n[(2+(int)ROUND)*3+i])
		{
			type = ROUND;
			flag = TRUE;
		}
		else
			type = CONS_MIN;
	}
	
	return type;	
}	

void make_plural(const char* noun , char* plural,const char* n) 
{
	major_type type;
	int i, string_lenght;
	
	string_lenght = strlen(noun);/* for find word's lenght */

	/*find last major type ,and add plural suffix */
	type = find_last_type(noun, n);
	
	if(type == HARD)
		sprintf(plural, "%slar", noun);
	else
		sprintf(plural, "%sler", noun);
	
	plural[string_lenght + FOUR] = '\0';/* add null character to string */
}	

major_type find_last_type(const char* word,const char* n)
{	
	major_type type=CONS_MAJ;
	int i, string_lenght;
	
	string_lenght = strlen(word);/* for find word's lenght */
		
	/* start to read chars from end of the word until finding a vowel  and define its major type */
	for(i=string_lenght - 1 ; i >= 0 && type == CONS_MAJ; i--)
		type = is_major(word[i], n);
	
	return type;
}	
