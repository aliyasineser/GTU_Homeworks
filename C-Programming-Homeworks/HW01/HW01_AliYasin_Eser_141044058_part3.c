/*###########################################################################*/
/*HW01_Ali_Yasin_Eser_141044058.c  								  			 */
/*_______________________________								  			 */
/*Ali Yasin Eser tarafindan 21 Subat 2015'de yazilmistir.		  			 */
/*																  			 */	
/*Aciklama														  			 */
/*___________ 													  			 */
/*Verilen uc arabanin belirtilen yol icin ihtiyaci olan tutar				 */
/*Girilen degerler:												  			 */
/*	-Arabalarin kodlari														 */
/*	-Kilometre basina harcanan benzin miktari(Litre cinsinden)	 			 */
/*	-1 Litre benzinin fiyati(TL ve Kurus cinsinden)							 */
/*	-Arabanin yaptigi veya yapmasi gereken yol(Kilometre cinsinden)			 */
/*Cikis degerleri:															 */
/*	-Alinacak yol icin gerekli tutar							 			 */
/*###########################################################################*/
/*																  			 */
/*---------------------------------------------------------------------------*/
/*							Icerik								 			 */
/*---------------------------------------------------------------------------*/
#include <stdio.h>


/*Fonksiyonlarin tanitilmasi*/
double tot_fuel_cost(double x, double y, double z);	/*Tutari bulan fonksiyon*/

void PrintResult(int fcar_1, double fcost_1, 
int fcar_2, double fcost_2, 
int fcar_3, double fcost_3);	/*Sonucu yazdiran fonksiyon*/


int
main(void)
{
	/*Degiskenlerin ve dosyalarin tanitilmasi*/
	int car1, car2, car3;
	double per_km1, per_km2, per_km3;
	double pr_fuel1, pr_fuel2, pr_fuel3;
	double tot_km1, tot_km2, tot_km3;
	double cost_1, cost_2, cost_3;
	FILE *iptr;
	
	/*Dosyanin acilmasi*/
	iptr = fopen("Cars.txt", "r");
	
	/*Dosyadan degerlerin atanmasi*/
	fscanf(iptr, "%d%lf%lf%lf%d%lf%lf%lf%d%lf%lf%lf",
	&car1, &per_km1, &pr_fuel1, &tot_km1,
	&car2, &per_km2, &pr_fuel2, &tot_km2,
	&car3, &per_km3, &pr_fuel3, &tot_km3);
	
	/*tot_fuel_cost fonksiyonu ile degerlerin bulunmasi*/
	cost_1 = tot_fuel_cost(per_km1, pr_fuel1, tot_km1);
	cost_2 = tot_fuel_cost(per_km2, pr_fuel2, tot_km2);
	cost_3 = tot_fuel_cost(per_km3, pr_fuel3, tot_km3);
	
	/*Sonuclarin ekrana ve dosyaya yazdirilmasi*/
	PrintResult(car1, cost_1, car2, cost_2, car3, cost_3);
	
	/*Dosyanin kapatilmasi*/
	fclose(iptr);

	return 0;
}

double tot_fuel_cost(double x, double y, double z)
{
	/*Sonuc degerinin dondurulmesi*/
	return x*y*z;

}

void PrintResult(int fcar_1, double fcost_1,
 int fcar_2, double fcost_2,
 int fcar_3, double fcost_3)
{
	/*Degiskenlerin ve dosyanin tanitilmasi*/
	FILE *optr;	
	int car_int_1, car_int_2, car_int_3;
	double kurus_1, kurus_2, kurus_3;

	/*Dosyanin acilmasi*/
	optr = fopen("TotalFuelCosts.txt", "w");

	/*Birinci araba icin sonuclarin hesaplanmasi*/	
	car_int_1 = fcost_1;	/*Kurus degerinin dondurulmesi islemi icin*/
	kurus_1 = fcost_1 - car_int_1;

	/*Ikinci araba icin sonuclarin hesaplanmasi*/
	car_int_2 = fcost_2;	/*Kurus degerinin dondurulmesi islemi icin*/
	kurus_2 = fcost_2 - car_int_2;

	/*Ucuncu araba icin sonuclarin hesaplanmasi*/
	car_int_3 = fcost_3;	/*Kurus degerinin dondurulmesi islemi icin*/
	kurus_3 = fcost_3 - car_int_3;

	/*Birinci araba icin sonucun ekrana yazdirilmasi*/
	printf("The total fuel cost of the car %d is %d TL and %.2f Kurus.\n", 
	fcar_1, car_int_1, kurus_1);

	/*Ikinci araba icin sonucun ekrana yazdirilmasi*/
	printf("The total fuel cost of the car %d is %d TL and %.2f Kurus.\n", 
	fcar_2, car_int_2, kurus_2);

	/*Ucuncu araba icin sonucun ekrana yazdirilmasi*/
	printf("The total fuel cost of the car %d is %d TL and %.2f Kurus.\n", 
	fcar_3, car_int_3, kurus_3);

	/*Sonuclarin dosyaya yazdirilmasi*/
	fprintf(optr, "%d	%.2f\n", fcar_1, fcost_1);
	fprintf(optr, "%d	%.2f\n", fcar_2, fcost_2);
	fprintf(optr, "%d	%.2f\n", fcar_3, fcost_3);
	
	/*Dosyanin kapatilmasi*/
	fclose(optr);

	return ;

}

/*######################################################################*/
/*				HW01_Ali_Yasin_Eser_141044058.c sonu					*/
/*######################################################################*/
