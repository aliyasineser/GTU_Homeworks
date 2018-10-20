/*************************************************************
 *                                                           *
 * HW05 Q2                                                   *
 * Student Name: Ali Yasin Eser                              *
 * Student ID  : 141044058                                   *
 * Date        : 24/03/2015                                  *
 *                                                           *
 *************************************************************/
#include <stdio.h>
#define NUM_ARR 9/*Dizinin eleman sayisi*/

/*Dogru ve yanlisin tanimi*/
typedef enum
	{FALSE, TRUE}
	bool;
/*Fonksiyonlar*/
int max_array(int array[], int n);
int second_max_array(int array[], int n);
int sum_all_array (int array[], int n);
int count_array(int array[], int n, int value);	
bool search_array (int array[], int n, int value);

int
main()
{
	int search_control;/*Dizide deger arama fonksiyonu icin*/
	int our_arr[NUM_ARR] = {6,8,3,3,12,8,3,8,2};/*Dizinin tanimlanmasi*/	
	
	
	printf("Maximum array is %d.\n\n", max_array(our_arr,NUM_ARR));
	printf("Maximum second array is %d.\n\n", 
	second_max_array(our_arr,NUM_ARR));
	printf("Sum of integers in the array %d.\n\n", 
	sum_all_array(our_arr,NUM_ARR));
	printf("Count of value 6 is %d.\n\n", count_array(our_arr, NUM_ARR, 6));
	printf("Count of value 8 is %d.\n\n", count_array(our_arr, NUM_ARR, 8));
	printf("Count of value 3 is %d.\n\n", count_array(our_arr, NUM_ARR, 3));
	
	
/*Dizide deger araniz False donerse bulunamadi mesaji verir*/
	search_control = search_array( our_arr, NUM_ARR, 2 );
	if(search_control == FALSE)
		printf("There is not any 2 in the array");
	search_control = search_array( our_arr, NUM_ARR, 8 );
	if(search_control == FALSE)
		printf("There is not any 8 in the array");
	search_control = search_array( our_arr, NUM_ARR, 12 );
	if(search_control == FALSE)
		printf("There is not any 12 in the array");
		
	return 0;
}
/*Dizideki en buyuk sayiyi bulur*/
int max_array(int array[], int n)
{
	int temp=0;/*En buyuk deger*/
	int i;
	
	for( i=1; i<n ; i++ )
		if( array[temp] < array[i] )
			temp = i;
	return array[temp];
}

/*Dizideki en buyuk ikinci sayiyi bulur*/
int second_max_array(int array[], int n)
{
	int temp=0;/*En buyuk deger*/
	int sec_max=0;/*En buyuk ikinci*/
	int i;/*Dongu icin*/
	/*En yuksek degeri bulur*/
	for( i=1; i<n ; i++ )
		if( array[temp] < array[i] )
			temp = i;	
	/*En yuksek ikinci degeri bulur*/
	for( i=1; i<n ; i++ )	
		if( array[sec_max] < array[i] && array[i] < array[temp] )
			sec_max = i;	
	return array[sec_max];	
}


int sum_all_array (int array[], int n)
{
	int count;/*Dongu icin*/
	int total=0;/*Toplam deger*/
	for(count=0; count < n; count++)
		total += array[count];
	return total;	
}
/*Dizi icerisinde sorulan degerin kac tane oldugunu belirtir*/
int count_array(int array[], int n, int value)
{
	int i;/*Dongu icin*/
	int count_for_value=0;
	for(i=0; i < n; i++)
		if(array[i] == value)
			count_for_value ++;	
	return count_for_value;
}
/*Dizi icinde sayi arar, sayinin yerini dondurur*/
bool search_array (int array[], int n, int value)
{
	int i;/*Dongu icin*/
	int is_there = FALSE;/*Bulunup bulunmadigini dondurecek deger*/
	int where;/*Bulunan degerin dizideki konumu*/
	for(i=0; i<n; i++)
		if(array[i] == value && is_there != TRUE){
			is_there = TRUE;
			where = i;}
	if(is_there == TRUE){/*Eger dizide aranan deger varsa konsola yazdirilir*/
		printf("Value %d is at %d\n\n", value, where);}
	
	return is_there;
}
/*****************************************************************************
 * 						End of HW04 Q2                       				 *
 *****************************************************************************/
