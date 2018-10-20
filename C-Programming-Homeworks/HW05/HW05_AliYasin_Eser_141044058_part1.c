/*************************************************************
 *                                                           *
 * HW05 Q1                                                   *
 * Student Name: Ali Yasin Eser                              *
 * Student ID  : 141044058                                   *
 * Date        : 24/03/2015                                  *
 *                                                           *
 *************************************************************/
#include <stdio.h>
#include <math.h>
#define ROAD_NUMS 50	/*Yollarin numaralari, "01234..." icin array siniri*/
#define CARS_ROAD 50	/*Arabalarin isaretlenmesi ve yol ici array siniri*/
#define ROAD_BEGINS 0

/*Konsola ne yazilacagini belirlemek icin ozel tip tanimlanir*/
typedef enum
	{PLAY, CRASH, END}
	object_state;
/*Fonksiyonlar*/
void make_move(char *object1, double *position1, double *speed1, int weight1,
char *object2, double *position2, double *speed2, int weight2, object_state
*game_state);

double car_crash_time(double position1, double position2, double speed1, 
double speed2);

void print_game_state(char object1, double position1, char object2, 
double position2, object_state game_state);

void get_info(char *name1, char *name2, int *weight1, int *weight2, 
double *speed1, double *speed2);

int
main()
{
	/*Araba agirliklari*/
	int w_car1,
		w_car2;
	/*Arabalar icin temsili isimler*/
	char name_car1,
		 name_car2;
	/*Araba hizlari ve pozisyonlari*/
	double speed_of_car1,
		   speed_of_car2,
	  	   position_of_car1 = ROAD_BEGINS,
		   position_of_car2 = (CARS_ROAD-1);
	object_state game_state = PLAY;/*Baslangic durumu*/


	printf("Araba carpisma simulatorune hos geldiniz.\n");
	/*Bilgiler alinir*/
	get_info(&name_car1, &name_car2, &w_car1, 
	&w_car2, &speed_of_car1, &speed_of_car2);
	speed_of_car2 = -fabs(speed_of_car2);
	/*Harekete baslanir ve bitirilir*/
	make_move( &name_car1, &position_of_car1, &speed_of_car1, w_car1,
	&name_car2, &position_of_car2, &speed_of_car2, w_car2, &game_state );

/*	printf("%f", car_crash_time( position_of_car1, position_of_car2,
	speed_of_car1, speed_of_car2 )); */
	
/*	print_game_state( name_car1, position_of_car1 ,name_car2, position_of_car2
	, PLAY  );*/
	
		
	return 0;
	
}
/*Tum hareketi kontrol eden ana fonksiyon*/
void make_move(char *object1, double *position1, double *speed1, int weight1,
char *object2, double *position2, double *speed2, int weight2, object_state
*game_state)
{
	int i;/*Dongu icin*/
	double cr_time,/*Carpisma zamani icin*/
		   speed3;/*Carpisma sonrasi momentum korunumundan elde edilen */
	
	cr_time = car_crash_time(*position1, *position2, *speed1, *speed2);
	/*Carpisana kadarki kisim yazdirilir*/
	/*Test sarti carpisana kadar gecen genel sureyi ele aldigindan dogrudur*/
	for( i=0; i < (int)cr_time; i++) 
	{
		print_game_state(*object1, *position1, 
		*object2, *position2, *game_state);
		/*Guncelleme*/
		*position1 += *speed1;
		*position2 += *speed2;
	}
		
	*game_state = CRASH;/*Carpisma durumu*/
	cr_time = car_crash_time(*position1, *position2, *speed1, *speed2);
	/*Esnek olmayan carpisma formulunden yeni hiz*/
	speed3 = ((weight1)*(*speed1) + 
	((weight2) * (*speed2 )) / ( weight1 + weight2 ));
	/*Hizlarin durumuna gore hareket yonu*/
	if( fabs(*speed2)*weight2 > fabs(*speed1)*weight1 ){
		*position1 = *position1 - (*speed2 * cr_time);
		while( *position1 >= ROAD_BEGINS ){
			print_game_state(*object1, *position1, 
			*object2, *position2, *game_state);
			*position1 -= fabs(speed3); }}
	else if( fabs(*speed2)*weight2 < fabs(*speed1)*weight1){
		*position1 = *position2 - (*speed1 * cr_time);
		while(  *position1 <= CARS_ROAD ){
			print_game_state(*object1, *position1, 
			*object2, *position2, *game_state);
			*position1 += fabs(speed3);}}
			
	*game_state = END;/*Sonlanma durumu*/
	print_game_state(*object1, *position1, 
	*object2, *position2, *game_state);
}
/*Carpisma zamaninin hesaplanmasi*/
double car_crash_time(double position1, double position2, double speed1, 
double speed2)
{
	return (position2-position1) / (speed1-speed2);
}

/*Tum islemlerin konsola yazdirilip gorsel bolumun elde edilmesi*/
void print_game_state(char object1, double position1, char object2, 
double position2, object_state game_state)
{
	int for_road[ROAD_NUMS],/*Rakamlarin yazildigi yol uzunlugu*/
		count_for_fill, /*Yolun cizilmesi icin*/
		var_for_assign,	/*Rakam dolu dizi icin*/
		i;/*Dongu icin*/
	char for_cars[CARS_ROAD];	/*Yol uzunlugu*/
	
	if(game_state == PLAY){/*Carpisma oncesi*/
	/*Diziler olusturulur, arabalarin bulundugu kisim degistirilir */
	/*Boylece dizi konsola yazdirildiginda arabalar da yerinde olur*/
		for(count_for_fill = 0; count_for_fill < ROAD_NUMS; count_for_fill++)
		{	var_for_assign = (count_for_fill+1) % 10;
			for_road[count_for_fill] = var_for_assign;}
		for(i = 0; i < CARS_ROAD; i++)
			for_cars[i] = '_';

		for_cars[(int)position1] = object1;
		for_cars[(int)position2] = object2;
	
		for(i = 0; i < CARS_ROAD; i++)
			printf("%c", for_cars[i]);
		printf("\n");
		for(i = 0; i < ROAD_NUMS; i++)
			printf("%d", for_road[i]);
		printf("\n");}
		
	else if (game_state == CRASH){/*Carpisma ve sonrasi*/
	/*Tek bir hiz degeri uzerinden islem ve degisiklik yapar*/
	for(count_for_fill = 0; count_for_fill < ROAD_NUMS; count_for_fill++){
			var_for_assign = (count_for_fill+1) % 10;
			for_road[count_for_fill] = var_for_assign;}
		
		for(i = 0; i < CARS_ROAD; i++)
			for_cars[i] = '_';
		for_cars[(int)position1] = 'X' ;
		for(i = 0; i < CARS_ROAD; i++)	
			printf("%c", for_cars[i]);
		printf("\n");
		for(i = 0; i < ROAD_NUMS; i++)
			printf("%d", for_road[i]);
		printf("\n");
	}		
	
	
	else if(game_state == END){
	/*Carpisma sonrasi arabalarin olusturdugu yiginin durmasi*/
		for(count_for_fill = 0; count_for_fill < ROAD_NUMS; count_for_fill++){
			var_for_assign = (count_for_fill+1) % 10;
			for_road[count_for_fill] = var_for_assign;}
		
		for(i = 0; i < CARS_ROAD; i++)
			for_cars[i] = '_';
		
		for_cars[(int)position1] = 'X' ;

		for(i = 0; i < CARS_ROAD; i++)	
			printf("%c", for_cars[i]);
		printf("\n");
		for(i = 0; i < ROAD_NUMS; i++)
			printf("%d", for_road[i]);
		printf("\n");}
		
}
/*Kullanicidan degerlerin alinmasi*/
void get_info(char *name1, char *name2, int *weight1, int *weight2, 
double *speed1, double *speed2)
{

	printf("Ilk arabayi temsil edecek karakteri giriniz:\n");
	scanf(" %c", name1);
	printf("Ikinci arabayi temsil edecek karakteri giriniz:\n");
	scanf(" %c", name2);
	printf("Ilk arabanin agirligini giriniz:\n");
	scanf("%d", weight1);
	printf("Ikinci arabanin agirligini giriniz:\n");
	scanf("%d", weight2);
	printf("Ilk arabanin hizini giriniz:\n");
	scanf("%lf", speed1);
	printf("Ikinci arabanin hizini giriniz:\n");
	scanf("%lf", speed2);

}
/*****************************************************************************
 * 						End of HW05 Q1                      				 *
 *****************************************************************************/
