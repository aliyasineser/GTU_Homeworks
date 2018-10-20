/*###########################################################################*/
/*HW03_Ali_Yasin_Eser_141044058_part2.c  						  			 */
/*_______________________________								  		     */
/*Ali Yasin Eser tarafindan 6 Mart 2015'de yazilmistir.		  				 */
/*																  			 */	
/*Aciklama														  			 */
/*___________ 													  			 */
/*		-Rastgele olarak bir yukseklik ve sonraki dusus icin yukseklik kaybi */
/*	katsayisi verilmis olan ziplayan topun tepe yuksekligi ve toplam aldigi  */
/*	dusey yolu verir.														 */
/*Girilen degerler:												  			 */
/*	-Deger girilmemektedir. Rastgele deger secilmektedir.					 */
/*Cikis degerleri:															 */
/*	-Ziplama no, yukseklik, alinan dusey yol								 */
/*###########################################################################*/
/*																  			 */
/*---------------------------------------------------------------------------*/
/*							Icerik								 			 */
/*---------------------------------------------------------------------------*/

/*Kutuphane ve makrolarin tanimlanmasi*/
#include <stdio.h>
#include <stdlib.h>
#define LIM_HE 1 /*1 feet siniri*/

/*Fonksiyonlarin tanitilmasi*/
void report_first(FILE *optr, int count, double new_height, double total_dist);
int random_height();
double random_ratio();
double calculate_the_new_height(double current, double ratio);
double calculate_the_vertical_distance(double new_dis);
int count_the_number(int count_ball);
void report(FILE *optr, int count, double new_height, double total_dist);

int
main()
{
	/*Degiskenlerin tanimlanmasi*/
	FILE *optr;	/*Output dosyasi*/
	int first_height;	/*Ilk yukseklik*/
	double ratio;	/*Yukseklik kaybi katsayisi*/
	double  current_height, /*Dongu icin ara deger*/
			new_height,	/*Dongu icin ikinci ara deger*/
			total_dist;	/*Toplam alinan dusey yol*/
	int count = 1; /*Ziplama no sayici*/

	/*Degerlerin rastgele secilmesi*/
	first_height = random_height();
	ratio = random_ratio();


	/*Ara degerlerin atanmasi*/
	current_height = first_height;
	new_height = first_height;
	total_dist = first_height;	
	optr = fopen("Result_Table.txt", "w");	/*Output dosyasi*/
	
	/*Konsola tablonun degerlerinin ve output tablo basliginin yazilmasi*/
	printf("First height of ball is %d feet\n", first_height);
	printf("Ratio of ball is %f\n", ratio);
	printf("No – The Rebouncing Height -- The Total Vertical Distance\n");

	/*Ilk dusus degeri, donguden bagimsiz ve her durumda ayni*/
	printf("%2d%6c%6.3f%17c%6.3f\n", count, ' ', new_height, ' ', new_height);
	fprintf(optr, "%2d%6c%6.3f%17c%6.3f\n", count, ' ', new_height, ' ', 
	new_height);


	while(current_height > LIM_HE)	/*1 feet sinirina kadar dongu*/
	{
		/*Top ziplama sayisini artirma*/
		count = count_the_number(count);
		/*Yeni yuksekligin bulunmasi*/
		new_height = calculate_the_new_height(current_height, ratio);
		/*Alinan toplam yolun hesaplanmasi*/
		total_dist += calculate_the_vertical_distance(new_height);
		/*1 feet kontrolu, dongunun son degerini test etmek icin*/
		if(new_height > LIM_HE){
		report(optr, count, new_height, total_dist);
		}
		/*Ara degerin degistirilmesi, dongunun devami icin update*/
		current_height = new_height;
	}

	fclose(optr);	/*Dosyanin kapatilmasi*/
	return 0;
}


int random_height()	/*Rastgele yukseklik secen fonksiyon*/
/*Rastgele --> Sistem zamani uzerinden fonksiyon calisir.*/
{
	int num_he;
	srand(time(NULL)); /*Sistem zamani ile rastgele*/
	num_he = ( ( rand() % 31 ) + 10 ); /*10-40 feet araliginda deger*/
	return num_he;
}

double random_ratio() /*Yukseklik kayip katsayisini rastgele secen fonksiyon*/
/*Rastgele --> Sistem zamani uzerinden fonksiyon calisir.*/
{
	double num_rt;
	srand(time(NULL));	/*Sistem zamani ile rastgele*/
	num_rt = ( ( ( rand()  % 5 ) + 4.0) / 10.0) ; /* 0.4-0.8 arasi */
	return num_rt;
}

double calculate_the_new_height(double current, double ratio)
{
	return current * ratio;	/*Yukseklik kaybedildiginde yeni yukseklik*/
}

double calculate_the_vertical_distance(double new_dis)
{
	return (2*new_dis); /*Alinan dusey yol( Cikis & Inis )*/
}


void report(FILE *optr, int count, double new_height, double total_dist)
{
	/*Hesaplanan degerin tabloya eklenmesi, dosyaya yazilmasi*/
	printf("%2d%6c%6.3f%17c%6.3f\n", count, ' ', new_height, ' ', total_dist);
	fprintf(optr, "%2d%6c%6.3f%17c%6.3f\n", count, ' ', 
	new_height, ' ', total_dist);

}

int count_the_number(int count_ball)
{
	return count_ball += 1;	/*Top ziplama sayisinin artirilmasi*/
}

/*###########################################################################*/
/*				HW03_Ali_Yasin_Eser_141044058_part2.c sonu					 */
/*###########################################################################*/
