/*###########################################################################*/
/*HW01_Ali_Yasin_Eser_141044058.c  								  			 */
/*_______________________________								  			 */
/*Ali Yasin Eser tarafindan 21 Subat 2015'de yazilmistir.		  			 */
/*																  			 */	
/*Aciklama														  			 */
/*___________ 													  			 */
/*Iki lineer dogrudan x ve y degerlerini bularak fonksiyonda kullanir		 */
/*Girilen degerler:												  			 */
/*	-Birinci lineer dogrunun x, y katsayilari ve esit oldugu deger			 */
/*	-Ikinci lineer dogrunun x, y katsayilari ve esit oldugu deger			 */
/*	-f(x,y) fonksiyonundaki x ve y degerlerinin katsayilari					 */
/*Cikis degerleri:															 */
/*	-x ve y degerleri									  		 			 */
/*	-f(x,y) fonksiyonunun sonucu						  		 			 */
/*###########################################################################*/
/*																  			 */
/*---------------------------------------------------------------------------*/
/*							Icerik								 			 */
/*---------------------------------------------------------------------------*/

#include <stdio.h>

/*Fonksiyonlarin tanitilmasi*/

/*x ve y degerini bulan, f(x,y) fonksiyonundan sonucu alip yazdiran fonksiyon*/
int bil_bul(
double kat_a, double kat_b, double kat_c, 
double kat_d, double kat_e, double kat_f, 
double func_coef1, double func_coef2);	

/*f(x,y) sonucunu bulan fonksiyon*/
double f(double x, double y, double coef_1, double coef_2);	

int
main (void)
{
	/*Degiskenlerin ve dosyalarin tanitilmasi*/
	FILE *iptr, *funcco;
	double coefa, coefb, coefc;
	double coefd, coefe, coeff;
	double coefk, coeft;
	double x, y;
	
	/*Lineer dogru katsayilarini iceren dosya*/
	iptr = fopen("EqCoefficients.txt", "r");
 
	/*Fonksiyon katsayilarini iceren dosya*/
	funcco = fopen("FuncCoefficients.txt", "r");	

	/*Lineer dogrularin katsayilarinin dosyadan degiskenlere atanmasi*/
	fscanf(iptr ,"%lf%lf%lf%lf%lf%lf", 
	&coefa, &coefb, &coefc, &coefd, &coefe, &coeff);

	/*Fonksiyondaki x ve y degerlerinin katsayilarinin degiskenlere atanmasi*/
	fscanf(funcco, "%lf%lf", &coefk, &coeft);
	
	/*x ve y degerini bulup yazdiran fonksiyonun cagirilmasi*/
	bil_bul( coefa, coefb, coefc, coefd, coefe, coeff, coefk, coeft );
	
	/*Dosyalarin kapatilmasi*/
	fclose(iptr);
	fclose(funcco);
		
	return (0);
}


int bil_bul(
double kat_a, double kat_b, double kat_c, double kat_d, double kat_e, double kat_f, 
double func_coef1, double func_coef2
)
{
	/*Degiskenlerin ve output dosyasinin tanimlanmasi*/
	FILE *optr;
	double oran, temp_d, temp_f,top_x, top_res, res_x, res_y, fonk_s;	

	/*Output dosyasinin acilmasi*/
	optr = fopen("Results2.txt", "w");
	
	/*Katsayi bulma islemleri*/
	oran = (-kat_b / kat_e); /* y degerleri arasindaki oranin bulunmasi*/
	
	/*Oranin ikinci denklemle carpilmasi*/
	
	/*Ikinci denklemle carpilma sebebi ilk denklemin ikinci denkleme  */
	/*oraninin alinmasidir. Tam tersi icin islem farkli yazilmalidir. */
	temp_d = (oran * kat_d);
	temp_f = (oran * kat_f);
	
	/*Denklemlerin toplanmasi*/
	top_x = (kat_a + temp_d);
	top_res = (kat_c + temp_f);
	
	/*x ve y degerinin bulunmasi*/
	res_x = (top_res / top_x);
	res_y = ((kat_c - (kat_a * res_x)) / kat_b);

	/*f(x) degerini hesaplayan fonksiyonun cagirilmasi*/
	/*Fonksiyon degerinin fonk_s degiskenine atanmasi*/
	fonk_s = f(res_x, res_y, func_coef1, func_coef2);

	/*Sonuclarin dosyaya yazdirilmasi*/
	fprintf(optr, "%f	%f	%f", res_x, res_y, fonk_s);

	/*Sonuclarin ekrana yazdirilmasi*/
	printf("x degeri = %5.2f\ny degeri = %5.2f\nf(%5.2f,%5.2f) = %5.2f\n", 
	res_x, res_y, res_x, res_y, fonk_s);

	/*Dosyanin kapatilmasi*/
	fclose(optr);
	
	return 0;
}

double f(double x, double y, double coef_1, double coef_2)
{
	/*Islem sonucunun dondurulmesi*/
	return ( coef_1 * x ) + ( coef_2 * y );
	
}

/*###########################################################################*/
/*				HW01_Ali_Yasin_Eser_141044058.c sonu						 */
/*###########################################################################*/
