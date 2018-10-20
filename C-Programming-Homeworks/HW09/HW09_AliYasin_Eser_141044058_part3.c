/*************************************************************
 *                                                           *
 * HW09 Part3                                                *
 * Student Name: Ali Yasin Eser                              *
 * Student ID  : 141044058                                   *
 * Date        : 26/04/2015                                  *
 *                                                           *
 *************************************************************/
 /*Kutuphanelerin ve makrolarin tanimlanmasi*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*Dosya ismi sabittir, farkli dosya icin buradan degistirilebilir*/
#define INPUT_FILE "a.txt"
#define OUTPUT_FILE "our_bin_output.bin"

#define MAX_SIZE 10
#define TABLE_MAX 125
#define SIZE 100
#define FALSE 0
#define TRUE 1
#define FIRST 0
#define SOME_VALUE 9999
#define STOP_VALUE (-1)

/*Pozitif kombinasyonlar icin struct*/
typedef struct{
    int pos1,
        pos2,
        pos3;
}triplet_t;

/*Her bir satir icin genel struct*/
typedef struct{
    triplet_t comb_of_pos;
    int mpn,
        lower_bound,
        upper_bound;
}Row;
/*Fonksiyonlarin tanimlanmasi*/
void Into_Binary(FILE *text_input, FILE *binary_output);

int Load_Mpn_table(FILE *binary_input_file,Row mpn_table[], int maxsize);

void search( Row mpn_table[], int actual_size,
const triplet_t triplet_to_search);


int
main()
{
    int i,j,k, size=FIRST,
        actual_size=FIRST,
        size_temp=SOME_VALUE,
        decision=FIRST;
    char temp[SIZE];
    triplet_t triplet_param;
    Row our_table[TABLE_MAX];
    FILE* text_file, *bin_file;

    /*Dosyalarin acilmasi*/
    text_file = fopen(INPUT_FILE, "r");
    if( text_file == FALSE )
    {
        printf("Text file couldn't be opened to read.\n");
        exit(1);
    }

    bin_file = fopen(OUTPUT_FILE, "wb");
    if( bin_file == FALSE )
    {
        printf("Binary file couldn't be opened to write.\n");
        exit(1);
    }

    /*i sayisi text dosyasindaki okunacak Row'un sayisini tutacak*
     * Yani bir nevi actual_size burada hesaplaniyor.            */
    for(i=0; fgets(temp, SIZE, text_file) != '\0'; ++i);

    fclose(text_file);
    text_file = fopen(INPUT_FILE, "r");

    /*Binary dosyanin doldurulmasi*/
    for( j = FIRST ; j < (int)((i/10.0)+1) ; j++)
        Into_Binary(text_file, bin_file);

    fclose(bin_file);
    bin_file = fopen(OUTPUT_FILE, "rb");
    if( bin_file == FALSE )
    {
        printf("Binary file couldn't be opened to write.\n");
        exit(1);
    }
    /*Binary dosyadan array'in doldurulmasi*/
    for( k=FIRST; size_temp != 0; k += 10 )
    {
        size_temp = Load_Mpn_table( bin_file, &(our_table[k]), MAX_SIZE );
        if( size_temp != 0 )
            actual_size += size_temp;
    }

    triplet_param.pos1 = 0;

    /*Asil isin yapildigi, istenen kombinasyonun arandigi kisim*/
    /*Dongu ile tekrar saglanmistir.*/
    do
    {
        printf("Please enter the combination of positives, ");
        printf("seperate them with white-space characters:\n");
        scanf("%d %d %d", &(triplet_param.pos1), &(triplet_param.pos2),
        &(triplet_param.pos3));

        search(our_table, actual_size, triplet_param);

        printf("If you want to search another positive combination, ");
        printf("enter \"1\" or enter \"-1\" value ");
        printf("for exit the program.\n ");
        do
        {
            scanf("%d", &decision);
            if( decision != 1 && decision != -1 )
                printf("You can enter 1 or -1 value:\n");
        }while( decision != 1 && decision != -1 );

    }while( decision != STOP_VALUE );


    return 0;
}

/*Text dosyasindaki degerleri Binary dosyaya struct olarak yazar*/
void Into_Binary(FILE *text_input, FILE *binary_output)
{

    Row temp;
    int i, status, j, k;
    char temp_str[SIZE];

    for( i=0; i< MAX_SIZE ; i++)
    {

        status = fscanf( text_input, "%d %s %d %s %d %d %d %d",
        &(temp.comb_of_pos.pos1), temp_str, &(temp.comb_of_pos.pos2),
        temp_str, &(temp.comb_of_pos.pos3),
        &(temp.mpn), &(temp.lower_bound), &(temp.upper_bound));
        if( status != 0 )
        {

            fwrite( &temp, sizeof(Row), 1 , binary_output );
        }

    }



}
/*Binary dosyadan Row tipinden array'e degerleri atar*/
int Load_Mpn_table(FILE *binary_input_file,Row mpn_table[], int maxsize)
{
    int res;

    res = fread( mpn_table, sizeof(Row), maxsize, binary_input_file );
    return res;

}

/*Istenilen sonucun bulunup bulunmadigini arar ve sonucu verir*/
void search( Row mpn_table[], int actual_size,
const triplet_t triplet_to_search)
{

    int i, flag=0;

    for( i=0; i<actual_size; i++ )
    {
        if( mpn_table[i].comb_of_pos.pos1 == triplet_to_search.pos1 &&
            mpn_table[i].comb_of_pos.pos2 == triplet_to_search.pos2 &&
            mpn_table[i].comb_of_pos.pos3 == triplet_to_search.pos3 &&
            flag != 1)
        {
            printf("MPN=%d; 95%% of samples contain ", mpn_table[i].mpn);
            printf("between %d and %d bacteria/ml.\n",
            mpn_table[i].lower_bound, mpn_table[i].upper_bound);

            flag = 1;
        }
    }

    if( flag == 0 )
    {
        printf("There is no match between the numbers ");
        printf("you entered and our research database.\n");
    }
}
/*****************************************************************************
 * 						End of HW09 Part3                     				 *
 *****************************************************************************/
