/*###########################################################################*/
/*HW01_Ali_Yasin_Eser_141044058.c  								  			 */
/*_______________________________								  		     */
/*Ali Yasin Eser tarafindan 21 Subat 2015'de yazilmistir.		  			 */
/*																  			 */	
/*Aciklama														  			 */
/*___________ 													  			 */
/*Tanitilan g(x) ve f(x) fonksiyonlarindan bileske fonksiyonlari bulma		 */
/*Girilen degerler:												  			 */
/*	-Degisken olarak x degeri												 */
/*	-Sabit makro olarak y degeri								 			 */
/*Cikis degerleri:															 */
/*	-gof(x) ve fog(x) bileske fonksiyonlarinin sonuclari		 			 */
/*###########################################################################*/
/*																  			 */
/*---------------------------------------------------------------------------*/
/*							Icerik								 			 */
/*---------------------------------------------------------------------------*/

#include <stdio.h>
#include <math.h>
#define Y_CONS 8	/*Kullanilacak y degeri*/
#define PI 3.141592654	
#define US 2.5	/*f(x) fonksiyonundaki kuvvet degeri*/

/*Fonksiyonlarin tanitilmasi*/
double g(double x);	/*g(x) fonksiyonu*/
double f(double z);	/*f(x) fonksiyonu*/
void PrintResult(double x, double y, double z); /*Sonucu yazdiran fonksiyon*/

int
main()
{
	/*Degiskenlerin tanimlanmasi*/
	FILE *iptr;	/*Dosyanin tanitilacagi degisken*/
	int x;	/*Dosyadan okunacak deger*/
	double fog_res, gof_res;  /*Sonuclarin atilacagi degisken*/

	iptr = fopen("Variables.txt", "r");	/*Degiskene dosyanin tanimlanmasi*/
	fscanf(iptr,"%d", &x);	/*Dosyadan degerin okunmasi*/
	fog_res = f(g(x));	/*fog(x) fonksiyonunun sonucu*/
	gof_res = g(f(x));	/*gof(x) fonksiyonunun sonucu*/
	PrintResult(x, fog_res, gof_res);	/*Sonuclarin yazdirilmasi*/
	
	/*Dosyanin kapatilmasi*/
	fclose(iptr);
	
	return (0);
}


double g(double x)
{     
	/*Gecici degiskenlerin tanitilmasi*/	
	double consp, toppa, bolp, cev_deg;
	
	/*Fonksiyonun islemleri*/
	consp =  ( Y_CONS / ( 2 * x ));	
	bolp = ( x + consp );	
	toppa = ( 1 / bolp);	
	
	/*Sonucun dondurulmesi*/
	return (x + toppa);
}
            
double f(double z)
{ 
	/*Fonksiyon islemleri icin gerekli gecici degerlerin tanimlanmasi*/
	double us, log_ans, koklu_ans, top_kis, tri_ic, kuv_ifd, res_sin, don_deg;

	us = pow (3 , z); /*En icteki degerin ussunun alinmasi*/
	log_ans = log10 ( us / ( ( 2 * z ) + 1 ) );	/*Sonucun log10 degeri*/
	koklu_ans = sqrt( log_ans );	/*Logaritmasi alinan degerin karekoku*/
	top_kis = ( ( z + Y_CONS ) / z );	/*Koklu deger ile toplanacak ifade*/
	kuv_ifd = ( top_kis  + koklu_ans );	 /*Buyuk parantezin toplam degeri*/
	tri_ic = pow( kuv_ifd, US);	/*Buyuk parantezin kuvveti*/
	res_sin = sin( tri_ic );	/*Sonucun sinus degeri*/
	return res_sin;	
	
}

void PrintResult(double x, double y, double z)
{
	/*Yazilacak dosyanin tanitilmasi*/
	FILE *optr;

	/*Fonksiyon operasyonlari*/

	/*Dosyanin acilmasi*/
	optr = fopen("Results1.txt", "w"); 
	
	/*Sonuclarin dosyaya yazilmasi*/
	fprintf(optr,"%f	%f",y, z);	
	
	/*Sonucun ekrana yazilmasi*/
	printf("fog(%f) = %f\ngof(%f) = %f\n", x , y, x, z);	
	
	/*Dosyanin kapatilmasi*/
	fclose(optr);	
	
	return  ;

}

/*###########################################################################*/
/*				HW01_Ali_Yasin_Eser_141044058.c sonu						 */
/*###########################################################################*/
