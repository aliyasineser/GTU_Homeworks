/*###########################################################################*/
/*HW02_Ali_Yasin_Eser_141044058_part2.c  						  			 */
/*_______________________________								  		     */
/*Ali Yasin Eser tarafindan 28 Subat 2015'de yazilmistir.		  			 */
/*																  			 */	
/*Aciklama														  			 */
/*___________ 													  			 */
/*5 ogrencinin notlarindan ortalama notu ve ortalamaya katkisini bulur		 */
/*Girilen degerler:												  			 */
/*	-5 ogrencinin isim ve soyisim bas harfleri								 */
/*	-Ogrencilerin vize1, vize2, final notlari					 			 */
/*Cikis degerleri:															 */
/*	-Ortalama not		 													 */
/*	-Genel okul ortalamasina katkisi										 */
/*###########################################################################*/
/*																  			 */
/*---------------------------------------------------------------------------*/
/*							Icerik								 			 */
/*---------------------------------------------------------------------------*/


/*Kutuphane ve makro tanitimi*/
#include <stdio.h>
#include <stdlib.h>
#define MID_EFF 0.3	/*Vizelerin ortalamaya katkisi*/
#define FINAL_EFF 0.4	/*Finalin ortalamaya katkisi*/
#define COURSE_CRED 3.0	/*Dersin kredi degeri*/
#define ALL_CRED 20.0	/*Ogrencilerin derslerinin toplam kredisi*/

/*Harf notlarinin verdigi kredi karsiliklari*/
#define LET_A 4
#define LET_B 3
#define LET_C 2
#define LET_D 1
#define LET_F 0


/*Fonksiyonlarin tanitimi*/
int Calc_aver(int midt_1, int midt_2, int final_1);	/*Ortalama not hesaplar*/
char find_letter_grade(int take_res);	/*Harf notu bulur*/
double calc_contrib(char let_gra); /*Genel okul ortalamasina katkiyi hesaplar*/


int
main()
{
	/*Ogrencilerin isim ve soyisim bas harfleri*/
	char ogr1_n, ogr1_sn;
	char ogr2_n, ogr2_sn;
	char ogr3_n, ogr3_sn;
	char ogr4_n, ogr4_sn;
	char ogr5_n, ogr5_sn;

	/*Ogrencilerin vize1, vize2, final notlari*/
	int ogr1_mid_1, ogr1_mid_2, ogr1_fin_1;
	int ogr2_mid_1, ogr2_mid_2, ogr2_fin_1;
	int ogr3_mid_1, ogr3_mid_2, ogr3_fin_1;
	int ogr4_mid_1, ogr4_mid_2, ogr4_fin_1;
	int ogr5_mid_1, ogr5_mid_2, ogr5_fin_1;

	/*Ortalama puan*/
	int res_grade_1, res_grade_2, res_grade_3, res_grade_4, res_grade_5;

	/*Harf notlarinin tutulacagi degiskenler*/
	char ogr1_harf, ogr2_harf, ogr3_harf, ogr4_harf, ogr5_harf;

	/*Genel Ortalamaya katki*/
	double ogr1_contrib, ogr2_contrib, ogr3_contrib, 
	ogr4_contrib, ogr5_contrib;

	/*Ogrenci bilgilerinin alinacagi ve sonucun yazilacagi dosyalar*/
	FILE *stu_in;
	FILE *stu_out;

	/*Giris ve cikis degerleri icin dosyalarin acilmasi*/
	stu_in = fopen("Students.txt", "r");
	stu_out = fopen("Grades.txt", "w");

	/*Ogrenci bilgilerinin okunmasi*/
	fscanf(stu_in,"%c%c%d%d%d\n""%c%c%d%d%d\n""%c %c%d%d%d\n"
	"%c%c%d%d%d\n""%c%c%d%d%d",
	&ogr1_n, &ogr1_sn, &ogr1_mid_1, &ogr1_mid_2, &ogr1_fin_1,
	&ogr2_n, &ogr2_sn, &ogr2_mid_1, &ogr2_mid_2, &ogr2_fin_1,
	&ogr3_n, &ogr3_sn, &ogr3_mid_1, &ogr3_mid_2, &ogr3_fin_1,
	&ogr4_n, &ogr4_sn, &ogr4_mid_1, &ogr4_mid_2, &ogr4_fin_1,
	&ogr5_n, &ogr5_sn, &ogr5_mid_1, &ogr5_mid_2, &ogr5_fin_1);
	
	/*Ortalama puanlarin hesaplanmasi*/
	res_grade_1 = Calc_aver(ogr1_mid_1, ogr1_mid_2, ogr1_fin_1);
	res_grade_2 = Calc_aver(ogr2_mid_1, ogr2_mid_2, ogr2_fin_1);
	res_grade_3 = Calc_aver(ogr3_mid_1, ogr3_mid_2, ogr3_fin_1);
	res_grade_4 = Calc_aver(ogr4_mid_1, ogr4_mid_2, ogr4_fin_1);
	res_grade_5 = Calc_aver(ogr5_mid_1, ogr5_mid_2, ogr5_fin_1);

	/*Harf notlarinin bulunmasi*/
	ogr1_harf = find_letter_grade(res_grade_1);
	ogr2_harf = find_letter_grade(res_grade_2);
	ogr3_harf = find_letter_grade(res_grade_3);
	ogr4_harf = find_letter_grade(res_grade_4);
	ogr5_harf = find_letter_grade(res_grade_5);

	/*Ortalamaya katkinin bulunmasi*/
	ogr1_contrib = calc_contrib( ogr1_harf );
	ogr2_contrib = calc_contrib( ogr2_harf );
	ogr3_contrib = calc_contrib( ogr3_harf );
	ogr4_contrib = calc_contrib( ogr4_harf );
	ogr5_contrib = calc_contrib( ogr5_harf );

	/*Sonuclarin dosyaya yazdirilmasi*/
	fprintf(stu_out, "%c%c %d\n", ogr1_n, ogr1_sn, res_grade_1);
	fprintf(stu_out, "%c%c %d\n", ogr2_n, ogr2_sn, res_grade_2);
	fprintf(stu_out, "%c%c %d\n", ogr3_n, ogr3_sn, res_grade_3);
	fprintf(stu_out, "%c%c %d\n", ogr4_n, ogr4_sn, res_grade_4);
	fprintf(stu_out, "%c%c %d\n", ogr5_n, ogr5_sn, res_grade_5);

	/*Sonuclarin konsola yazdirilmasi*/
	printf("Ogrenci %c%c, %d puan ortalamasina sahiptir", ogr1_n, 
	ogr1_sn, res_grade_1);
	printf(" ve bu ders, agirlikli not ortalamasina %.2f ", 
	ogr1_contrib);	
	printf("puan katki yapmistir.\n");

	printf("Ogrenci %c%c, %d puan ortalamasina sahiptir", ogr2_n, 
	ogr2_sn, res_grade_2);
	printf(" ve bu ders, agirlikli not ortalamasina %.2f ", 
	ogr2_contrib);	
	printf("puan katki yapmistir.\n");

	printf("Ogrenci %c%c, %d puan ortalamasina sahiptir", ogr3_n, 
	ogr3_sn, res_grade_3);
	printf(" ve bu ders, agirlikli not ortalamasina %.2f ", 
	ogr3_contrib);	
	printf("puan katki yapmistir.\n");

	printf("Ogrenci %c%c, %d puan ortalamasina sahiptir", ogr4_n, 
	ogr4_sn, res_grade_4);
	printf(" ve bu ders, agirlikli not ortalamasina %.2f ", 
	ogr4_contrib);	
	printf("puan katki yapmistir.\n");

	printf("Ogrenci %c%c, %d puan ortalamasina sahiptir", ogr5_n, 
	ogr5_sn, res_grade_5);
	printf(" ve bu ders, agirlikli not ortalamasina %.2f ", 
	ogr5_contrib);	
	printf("puan katki yapmistir.\n");	


	/*Dosyalarin kapatilmasi*/
	fclose(stu_in);
	fclose(stu_out);

	return 0;
}



int Calc_aver(int midt_1, int midt_2, int final_1)
{
	int res; /*Dondurulecek sonuc degiskeni*/

	/*Ortalama puanin hesaplanmasi*/
	res = ( midt_1 * MID_EFF ) + ( midt_2 * MID_EFF ) + (final_1 * FINAL_EFF );
	
	/*Sonucun dondurulmesi*/
	return res;
}


char find_letter_grade(int take_res)
{
	/*Sonuclarin dondurulecegi harf notlari*/
	char A='A', B='B', C='C', D='D', F='F';
	
	/*Araliklara gore harf notlarinin dondurulmesi islemi*/
	if( take_res >= 85 )
		return A;
	else if( take_res >= 70 )
		return B;
	else if( take_res >= 65 )
		return C;
	else if( take_res >=40 )
		return D;
	else 
		return F;	

}


double calc_contrib(char let_gra)
{
	/*Harf notlari karsinda verilen kredi ile katki hesabi*/
	switch(let_gra){
		case 'A' : 
			return (( LET_A * COURSE_CRED ) / ALL_CRED );
			break;		
		case 'B' :
			return (( LET_B * COURSE_CRED ) / ALL_CRED );
			break;
		case 'C' :
			return (( LET_C * COURSE_CRED ) / ALL_CRED );
			break;
		case 'D' :
			return (( LET_D * COURSE_CRED ) / ALL_CRED );
			break;
		case 'F' :
			return LET_F;
			break;
		default : 
			printf("I don't know your grade, do you?");
	}
}

/*###########################################################################*/
/*				HW02_Ali_Yasin_Eser_141044058_part2.c sonu					 */
/*###########################################################################*/
