/*###########################################################################*/
/*HW03_Ali_Yasin_Eser_141044058_part1.c  						  			 */
/*_______________________________								  		     */
/*Ali Yasin Eser tarafindan 29 Mart 2015'de yazilmistir.		  			 */
/*																  			 */	
/*Aciklama														  			 */
/*___________ 													  			 */
/*	1 ile 10 arasinda bir sayi tahmin isteyen bir oyun programidir.			 */
/*	Sinirsiz tahmin hakki sunar, oyun bitene kadar devam eder.				 */
/*	Kisi diledigi takdirde oyun surekli devam eder veya biter.				 */
/*Girilen degerler:												  			 */
/*	-Sayiyi bulmak icin bir tahmin											 */
/*Cikis degerleri:															 */
/*	-Tahmin ve bulunmasi gereken deger arasindaki farka gore uyari mesaji	 */
/*	-Tekrar oynayip oynamayacaginizi soran uyari mesaji						 */
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
	int check=0; /*Sonuc kontrolu*/
	char answer; /* Play ve Exit sonucunu alacak degisken*/
	
	/*Oyunun baslamasi, oyunun oynanilip oynanilmamasinin sorgusu*/
	printf("Welcome to \"Guess the integer number\" game.\n");
	printf("If you want to play, Enter P or you can exit with E.\n");
	printf("P/E?\n");
	scanf("%c", &answer);	/*Cevap aliniyor*/
	
/*Cevap 'P' ise oyun baslar, tahmin edilene kadar dongu devam eder*/
		while(answer == 'P' || answer == 'p')
		{
			printf("Let's Play!");
			number = RNG(); /*Rastgele sayi*/
			check = 0; /*Donguye girisin onceden hazirlanmasi*/
/*Check ayarlanmadigi takdirde donguye bir kere girilmektedir.*/
			while( check == 0 ){
				printf("Please guess an integer between 1 and 10 >>> ");
				scanf("%d", &guess);
				difference = CalculateTheDifference(guess, number);
				check = WarnThePlayer(difference);
				}
			printf("Do you want to play again? ");
			printf("If you want to play, Enter P or you can exit with E.\n"); 
			printf("P/E?\n");
			answer = ' ';
			scanf("\n%c", &answer);
		}
	if (answer == 'e' || answer == 'E')/*Cevap 'E' ise program sonlanir*/
		printf("As you wish. See ya!\n");
	else{	/*'P' ve 'E' disindaki karakterler icin uyari ve cikis mesaji*/
		printf("You entered wrong character and i'm afraid you can't play.");
		printf("See ya!\n");
		}


	return 0;
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
/*				HW03_Ali_Yasin_Eser_141044058_part1.c sonu					 */
/*###########################################################################*/
