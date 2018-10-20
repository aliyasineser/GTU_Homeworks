/*************************************************************
 *                                                           *
 * HW07 Part1                                                *
 * Student Name: Ali Yasin Eser                              *
 * Student ID  : 141044058                                   *
 * Date        : 9/04/2015                                   *
 *                                                           *
 *************************************************************/
/*Kutuphane ve makrolarin tanimlanmasi*/
#include <stdio.h>
#include <string.h>
#define STR_SIZE 100
#define EQUAL_THING 0
#define FIRST 0
#define NON 0
#define ADDONE 1
#define FORANOTHER 1

/*Fonskyionlarin tanimlanmasi*/
int find_size(const char *string);
int char_number(const char *string, const char *wish_to_find);

int
main()
{
    char str[STR_SIZE],
         our_wish[STR_SIZE];
    int z;
    /*Bir string istenir*/
    printf("Please enter a string.\n");
    fgets( str , STR_SIZE , stdin );

    /*String uzunlugu hesaplanir ve basilir*/
    z = find_size( str );
    printf("Length of string is %d.\n", z);

    /*Bir string ve icinde aranan ikinci bir string girilir*/
    printf( "Please enter a string that we can compare.\n" );
    fgets( str , STR_SIZE , stdin );
    printf("Please enter a string or character that you want to find.\n");
    fgets( our_wish , STR_SIZE , stdin );
    /*Stringlerin sonuna Null karakteri konur*/
    str[find_size(str)] = '\0';
    our_wish[find_size(our_wish)] = '\0';
    /*Ifadenin kac kere gectigi bulunu ve basilir*/
    z = char_number( str , our_wish);

    printf("Found  \"%s\" string  %d times in \"%s\" string.\n",
        our_wish, z, str);


    return 0;
}


/*String uzunlugunu bulan fonksiyon*/
int find_size(const char *string)
{
    int res;
    /*NULL veya newline karakterine kadar kendini cagirarak count artirir*/
    if(string[FIRST] == '\0' || string[FIRST] == '\n')
        res = NON;
    else
        res = ADDONE + find_size( &string[1] );


    return res;

}
/*String icinde baska bir stringin kac defa gectigini bulur*/
int char_number(const char *string, const char *wish_to_find)
{
    int count=FIRST,
        is_equal;
    char temp[STR_SIZE];    /*Gecici array*/

    if( find_size(string) >= find_size(wish_to_find) )
    {
        /*Aranan string uzunlugu kadar bir uzunluk gecici array'e atilir*/
        strncpy( temp, string, find_size(wish_to_find) );
        temp[ find_size(wish_to_find) ] = '\0';
        /*String'ler esitse count artirilir*/
        is_equal = strcmp( temp , wish_to_find );
        if( is_equal == EQUAL_THING )
            count += ADDONE + char_number( &string[1], wish_to_find );
        else
             count = char_number( &string[FORANOTHER], wish_to_find );

    }



    return count;

}
/****************************************************************************
 * 						End of HW07 Part1                     			    *
 ****************************************************************************/
