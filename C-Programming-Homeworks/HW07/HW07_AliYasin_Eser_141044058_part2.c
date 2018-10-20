/*************************************************************
 *                                                           *
 * HW07 Part2                                                *
 * Student Name: Ali Yasin Eser                              *
 * Student ID  : 141044058                                   *
 * Date        : 9/04/2015                                   *
 *                                                           *
 *************************************************************/
/*Kutuphane ve makrolarin tanimlanmasi*/
#include <stdio.h>
#define EQUAL_THING 0
#define FIRST 0
#define TWO_STAIRS_LIM 2
#define ZERO 0
#define SUB 1

/*Fonskyionlarin tanimlanmasi*/
int combination (int n , int k);
int ways (int n);
int ways_rec( int n, int k );

/*
    Onemli bir nokta olarak belirtilmelidir ki program kendini bir
    sentinel deger ile sinirlandiracak bir dongu barindiracak sekilde
    yazilmamistir. Ikinci istekler icin program tekrar baslatilmali.
*/

int
main()
{
    int step,   /*Adim sayisi*/
        comb_of_climb;  /*Toplam yol*/

    /*Adim sayisi istenir*/
    printf("Please enter the step of stairs.\n");
    scanf("%d", &step);
    /*Hesaplama yapilir ve yazdirilir.*/
    comb_of_climb = ways(step);
    printf("There are %d ways for climbing steps.\n", comb_of_climb);
    return 0;
}

/*Kombinasyon fonksiyonu*/
int combination (int n , int k)
{
    int result=ZERO;

    if( n==k || k==ZERO || n==ZERO )
        result++;
    else
        result += combination( n-SUB, k-SUB) + combination( n-SUB, k );

    return result;
}

/*Yolu bulan fonksiyon, ozyineli ikinci bir fonksiyon cagirir*/
int ways (int n)
{
    return ways_rec( n, ZERO);
}
/* toplam yol icin kombinasyon cagiran ozyineli fonksiyon*/
int ways_rec( int n, int k )
 {
     int num_of_ways=0;

     for(n; n >= k; n--, k++ )
        num_of_ways += combination( n, k );

    return num_of_ways;
 }
 /****************************************************************************
  * 						End of HW07 Part2                 				 *
  ****************************************************************************/
