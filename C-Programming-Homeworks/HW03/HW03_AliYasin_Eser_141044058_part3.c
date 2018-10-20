/*###########################################################################*/
/*HW03_Ali_Yasin_Eser_141044058_part3.c  						  			 */
/*_______________________________								  		     */
/*Ali Yasin Eser tarafindan 9 Mart 2015'de yazilmistir.			  			 */
/*																  			 */	
/*Aciklama														  			 */
/*___________ 													  			 */
/*	Ziplayan bir topun yatay diyagramini cizen bir programdir				 */
/*Girilen degerler:												  			 */
/*	-Ilk yukseklik															 */
/*	-1 feet uzunluk															 */
/*	-Cizilecek yol icin kullanilacak karakter								 */
/*	-Tepe noktasi icin kullanilacak karakter								 */
/*Cikis degerleri:															 */
/*	-Cizilen diyagram														 */
/*	-Diyagram icin kullanilmis karakter sayisi								 */
/*###########################################################################*/
/*																  			 */
/*---------------------------------------------------------------------------*/
/*							Icerik								 			 */
/*---------------------------------------------------------------------------*/

/*Kutuphane ve makrolarin tanitilmasi*/
#include <stdio.h>
#define TRUE 1

/*Fonksiyonlarin tanitilmasi*/
int draw_ver_diag_of_bb(int first_height, int feet_height, 
char the_peak_point, char the_road_point);
void increment_space(int space_ch, int feet_space);
int increment_character(int count_ch, int feet_height, char the_road_point);
int print_peak_part(int feet_space, int the_peak_point);
void decrement_space(int space_ch, int feet_space);
int decrement_character(int count_ch, int feet_height, char the_road_point);
int draw_diag_step(int first_height, int feet_height, 
char the_peak_point, char the_road_point);
int finish_diag(int length);

int
main()
{
	int count;	/*Diyagram icin kullanilacak karakter sayisi*/
	
	count = draw_diag_step(3,6,'+','-');
	printf("%d character has been used for diag.\n", count);

	count = draw_diag_step(7,4,'O','*');
	printf("%d character has been used for diag.\n", count);

	count = draw_diag_step(6,5,'$','#');
	printf("%d character has been used for diag.\n", count);

	return 0;
	

}

/*Diyagram cizimini saglayan fonksiyon*/
int draw_diag_step(int first_height, int feet_height, 
char the_peak_point, char the_road_point)
{
	int count_of_diag_ch=0, /*Dondurulecek karakter degeri*/
		length_for_finish;	/*Bitis icin uzunluk degeri*/
	

	printf("^\n");	/*Y koordinatinin ok kismi*/

	/*Diyagram koordinatinin uzunlugunun ayarlanmasi*/
	length_for_finish = first_height*feet_height + 1;

	/*Ilk yukseklik azaltilarak topun dusus diyagraminin olusturulmasi*/
	for(first_height; first_height > 0; first_height--)
	{
	count_of_diag_ch += draw_ver_diag_of_bb(first_height, feet_height, 
	the_peak_point, the_road_point); /* Diygram cizimi ve karakter hesabi*/
	}
	finish_diag(length_for_finish);	/*Bitis fonksiyonu*/

	return count_of_diag_ch;
}

/*Diyagramdaki hareketin bir inis-cikis kismini cizen fonksiyon*/
int draw_ver_diag_of_bb(int first_height, int feet_height, 
char the_peak_point, char the_road_point)
{
	int count = 0, 
		space_characters=0, /*Eklenecek bosluklarin dongu icin ara degiskeni*/	
		count_characters=1,/*Eklenecek karakterlerin dongu icin ara degiskeni*/
		special_count, /*Inis ve cikis dongusu icin ara degisken*/
		feet_space;	/*Bosluk karakterinin eklenmesi icin ara degisken*/

	feet_space = feet_height;	/*Ilk bosluk degerinin tanimlanmasi*/
	
		printf("I");/*Koordinat icin*/
		/*Topun cikis kisminin olusturulmasi icin dongu*/
		for(special_count=0; special_count < first_height*feet_height; 
		special_count += feet_height)
			{
			/*Bosluk karakterlerinin eklenmesi*/
	/*Dongunun ilk kisminda bosluk olmamasi icin != kullanilmistir.*/
			if(space_characters != 0){	
			increment_space(space_characters, feet_space);/*Bosluk eklenmesi*/
			feet_space += feet_height;}/*Her adimda boslugun artmasi icin*/

			space_characters = 1;	/*Bosluk eklenmesi icin update*/
			count += increment_character(count_characters, feet_height, 
			the_road_point); /*Karakter eklenmesi ve sayisinin dondurulmesi*/
			}

	/*Zirve noktasinin eklenmesi ve eklenen karakter sayisinin dondurulmesi*/
	count += print_peak_part(feet_space, the_peak_point);	
	feet_space -= feet_height;	/*Fazla boslugun dengelenmesi*/

		/*Topun inis kisminin cizildigi dongu*/
		for(special_count; special_count >= 1; special_count -= feet_height)

			{
			if(space_characters != feet_space){	/*Bosluk kontrolu*/
			decrement_space(space_characters, feet_space);/*Bosluk eklenmesi*/
			feet_space -= feet_height;}/*Boslugu giderek azalmasi icin update*/

			/*space_characters ile feet_space esitligi icin update*/
			space_characters = feet_height-(feet_height-1);
			
		/*Karakterlerin eklenmesi ve eklenen karakter sayisinin dondurulmesi*/
			count += decrement_character(count_characters, feet_height, 
			the_road_point);	
			}


	

	return count;
}

/*Cikis icin bosluk ekleyen fonksiyon*/
void increment_space(int space_ch, int feet_space)
{
	printf("I");/*Y koordinati icin*/
	for(space_ch; space_ch<= feet_space; space_ch +=1)
	{	
			printf(" ");
	}
}
/*Ciks icin karakter ekleyen fonksiyon*/
int increment_character(int count_ch, int feet_height, char the_road_point)
{
	int count=0;	/*Dondurulecek eklenen karakter sayisi*/

	for(count_ch; count_ch <= feet_height; count_ch += 1)
	{
		printf("%c", the_road_point);
		count += 1;
	}

	printf("\n");
	return count;
}

/*Zirve noktasi icin karakter ekleyen fonksiyon*/
int print_peak_part(int feet_space, int the_peak_point)
{
	int add_count =0; /*Eklenen karakterin sayi olarak dondurulmesi*/
	printf("I");	/*Y koordinati icin*/
	for(feet_space; feet_space >= 1; feet_space -= 1)
		{
		printf(" ");
		}
	printf("%c\n", the_peak_point);
	add_count += 1;
	return	add_count;
}

/*Inis kismi icin bosluk ekleyen fonksiyon*/
void decrement_space(int space_ch, int feet_space)
{
	printf("I");
	for(space_ch; space_ch <= feet_space; space_ch +=1)
	{
			printf(" ");
	}
}
/*Inis kismi icin karakter ekleyen fonksiyon*/
int decrement_character(int count_ch, int feet_height, char the_road_point)
{
	int count=0;	/*Eklenen karakter sayisinin dondurulmesi icin*/

	for(count_ch; count_ch <= feet_height; count_ch += 1){
			printf("%c", the_road_point);
			count += 1;}
	printf("\n");
	return count;
}
/*Biten diyagramin X ekseni eklenmesi ile sonlandirilmasi*/
int finish_diag(int length)
{
	printf("L");
	for(length; length >= 0; length--)
	{
		printf("-");
	}
	printf(">\n");

	return TRUE;
}

/*###########################################################################*/
/*				HW03_Ali_Yasin_Eser_141044058_part3.c sonu					 */
/*###########################################################################*/
