/*###########################################################################*/
/*HW02_Ali_Yasin_Eser_141044058_part1.c  						  			 */
/*_______________________________								  		     */
/*Ali Yasin Eser tarafindan 28 Subat 2015'de yazilmistir.		  			 */
/*																  			 */	
/*Aciklama														  			 */
/*___________ 													  			 */
/*	1 ile 10 arasinda bir sayi tahmin isteyen bir oyun programidir.			 */
/*	Iki tahmin hakki sunar, ikisini de yanlis tahmin ederseniz oyun biter.	 */
/*Girilen degerler:												  			 */
/*	-Birinci tahmin, yanlis oldugu takdirde ikinci tahmini de girersiniz	 */
/*Cikis degerleri:															 */
/*	-Tahmin ve bulunmasi gereken deger arasindaki farka gore uyari mesaji	 */
/*	-Basarili veya basarisiz tahmine gore degisen sonuc mesaji				 */
/*###########################################################################*/
/*																  			 */
/*---------------------------------------------------------------------------*/
/*							Icerik								 			 */
/*---------------------------------------------------------------------------*/

/*Kutuphanelerin ve makrolarin tanitilmasi*/
#include <stdio.h>
#include <stdlib.h>	
#define TRUE 1	/*Dogru degeri*/
#define FALSE 0	/*Yanlis degeri*/

/*Fonksiyonlarin tanitilmasi*/

int RNG(void);	/*Sistem zamanina gore sayi uretir*/

/*Tahmin ve gercek deger arasindaki farki hesaplayan fonksiyon*/
int CalculateTheDifference(int gue, int ran_num);

int WarnThePlayer(int diff_func); /*Farka gore uyari verir*/

int
main()
{
	/*Tahminin, degerin ve farkin tanitilmasi*/
	int number, guess, difference;
	int check; /*Sonuc kontrolu*/
	
	printf("Welcome to \"Guess the integer number\" game.You have 2 chances.");
	printf("Please guess an integer between in 1 and 10.\n");

	/*Tahmin edilecek sayinin elde edilmesi*/	
	number = RNG();
	
	scanf( "%d", &guess );	/*Tahminin okunmasi*/
	difference = CalculateTheDifference(guess, number);	/*Farkin hesaplanmasi*/
	check = WarnThePlayer(difference);	/*Fark ile kontrol yapilmasi*/

/*Ilk sonucun dogru ve yanlisligina gore ikinci test veya dogru sonuc mesaji*/
	if( check == TRUE )	/*Sonuc dogruysa program biter*/
			return 0;
	else	/*Sonuc yanlissa ikinci hak taninir*/
	{	
		/*Ikinci sansi yazdiran mesaj*/
		printf("So, try one more again! Choose well the last.\n");
		
		scanf( "%d", &guess );	/*Yeni tahminin okunmasi*/
		difference = CalculateTheDifference
		(guess, number);	/*Farkin hesaplanmasi*/
		check = WarnThePlayer(difference);	/*Sonuc kontrolu*/
		
		if(check == TRUE)	/*Ikinci tahmin dogru ise program biter*/
			return 0;
		else{	/*Ikinci tahminin de yanlis ise "oyun bitti" mesaji verilir*/
			printf("Sorry, game over!\n");
			return 0;	/*Mesaj sonrasi program biter*/
			}
	}
		
		
	
}


int RNG(void)
{
	/*Dondurulecek tahmin degeri*/
	int gue_num;
	/*Sistem zamani fonksiyondan gecirilerek sayi uretilir*/
	srand(time(NULL));
	/*Uretilen sayinin 10 ile modu alinir ve 0 cikmamasi icin 1 eklenir*/
	gue_num = ( ( rand() % 10 ) + 1 );
	/*Sonucun dondurulmesi*/
	return gue_num;
}

int CalculateTheDifference(int gue, int ran_num)
{
	/*Dondurulecek fark degeri*/
	int diff;
	
	if( gue > ran_num )	/*Tahmin buyukse yapilacak islem*/
		diff = ( gue - ran_num );
	else	/*Sayi buyukse yapilacak islem*/
		diff = ( ran_num - gue );
	/*Farkin dondurulmesi*/
	return diff;
	
}

int WarnThePlayer(int diff_func)
{
	/*Farkin buyuklugune gore uyari mesaji*/
	if( diff_func >= 5 ){	/*Fark 5 ve daha buyukse*/
		printf( "You are too far from the number\n" );
		return FALSE;}
	else if( diff_func >= 3 ){	/*Fark 3 veya daha buyukse*/
		printf("You are far from the number\n");
		return FALSE;}
	else if( 0 < diff_func && diff_func <= 2){	/*Fark (0,2] araligindaysa*/
		printf("You are close to the number\n");
		return FALSE;}	
	else( diff_func == 0 ); {	/*Fark 0 ise dogru tahmin*/
		printf("Congratulations, you guessed right the number!\n");
		return TRUE;
		}
	
}

/*###########################################################################*/
/*				HW02_Ali_Yasin_Eser_141044058_part1.c sonu					 */
/*###########################################################################*/
