/*************************************************************
 *                                                           *
 * HW09 Part1                                                *
 * Student Name: Ali Yasin Eser                              *
 * Student ID  : 141044058                                   *
 * Date        : 26/04/2015                                  *
 *                                                           *
 *************************************************************/
/*Kutuphanelerin ve makrolarin tanimlanmasi*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 30
#define ARR_SIZE 100
#define COMMA 5
#define FIRST 0
#define SECOND 1
#define THIRD 2
#define FOURTH 3
#define FIFTH 4
#define INPUT_FILE "part1.txt"
#define OUTPUT_FILE "part1.bin"
#define FALSE 0
#define TRUE 1

/*Tiplerin tanimlanmasi*/
typedef struct {
	char name[SIZE],
		surname[SIZE],
		department[SIZE],
		first_class[SIZE],
		second_class[SIZE];
	double salary;

}type_I;

typedef struct {
	char name[SIZE],
		surname[SIZE];
	double salary;
	char store_degree;

}type_E;

typedef union{
	type_I Ins;
	type_E Emp;
}type_t;

typedef struct{
	type_t work_pos;
	char iore;
}combine_type;

/*Fonksiyonlarin tanimlanmasi*/
combine_type salary_rise(combine_type person_info);
void fromtxt_tobin( FILE *txtfile, FILE *binfile );

int
main()
{
	FILE *fortxt, *forbin;

	fortxt = fopen(INPUT_FILE, "r");
	if(fortxt == FALSE)
	{
		printf("Input text file couldn't be opened to read.\n");
		exit(1);
	}
	forbin = fopen(OUTPUT_FILE, "wb");
	if(forbin == FALSE)
	{
		printf("Input text file couldn't be opened to read.\n");
		exit(1);
	}

	fromtxt_tobin( fortxt, forbin );

	return 0;

}
/*Calisanlarin yillik maas degerlerini gunceller*/
combine_type salary_rise(combine_type person_info)
{
	if( person_info.iore == 'E' || person_info.iore == 'e' )
		switch(person_info.work_pos.Emp.store_degree)
		{
		case 'a':
			person_info.work_pos.Emp.salary +=
			(person_info.work_pos.Emp.salary*(17.5)/100.0);
			break;
		case 'b':
			person_info.work_pos.Emp.salary +=
			(person_info.work_pos.Emp.salary*(12.0)/100.0);
			break;
		case 'c':
			person_info.work_pos.Emp.salary +=
			(person_info.work_pos.Emp.salary*(9.0)/100.0);
			break;
		default:
			printf("There is a mistake with %s %s\n",
			person_info.work_pos.Emp.name, person_info.work_pos.Emp.surname);
			break;
		}
	else if( person_info.iore == 'I' || person_info.iore == 'i' )
		person_info.work_pos.Ins.salary +=
		(((person_info.work_pos.Ins.salary/2) * 5.0) / 100.0) +
		(((person_info.work_pos.Ins.salary/2) * 5.3) / 100.0);
	else
		printf("There is a mistake in person's working position: %c\n",
		person_info.iore);
	return person_info;
}


/*Text'ten aldigi calisan degerlerini guncelletip Binary olarak yazar*/
/*Virgullerin yerini saptayip stringleri farkli yerlerden bolerek	 */
/*okuma yapar, okuduklarini struct'a atip oradan binary olarak yazar */
void fromtxt_tobin( FILE *txtfile, FILE *binfile )
{
	char status;
	char temp_str[ARR_SIZE];
	int i,j, comma_count=0, k;
	int size_str;
	char temp[SIZE];
	int comma_arr[COMMA];
	char supertemp[SIZE];
	char *hypertemp;
	combine_type our_comb;

	while( fgets(temp_str, ARR_SIZE, txtfile) != '\0' )
	{
		size_str = strlen(temp_str);
		temp_str[size_str-1] = '\0';

		if( temp_str[FIRST] == 'E' || temp_str[FIRST] == 'e' )
		{
			our_comb.iore = 'E';
			sscanf(temp_str, "%s %s %s %lf, %c", temp,
			our_comb.work_pos.Emp.name,
			our_comb.work_pos.Emp.surname, &(our_comb.work_pos.Emp.salary),
			&(our_comb.work_pos.Emp.store_degree));

			i = strlen(our_comb.work_pos.Emp.surname);
			our_comb.work_pos.Emp.surname[i-1] = '\0';

			/*printf( "%s %s, %.2f, %c\n" ,our_comb.work_pos.Emp.name,
			our_comb.work_pos.Emp.surname, our_comb.work_pos.Emp.salary	,
			our_comb.work_pos.Emp.store_degree );*/
		}
		else if( temp_str[FIRST] == 'I' || temp_str[FIRST] == 'i' )
		{
			our_comb.iore = 'I';
			/*Virgullerin konumlarinin bulunmasi*/
			for( i=0; i < size_str; i++ )
				if( temp_str[i] == ',' )
				{
					comma_arr[comma_count] = i;
					comma_count++;
				}
			sscanf(&(temp_str[comma_arr[FIRST]+1]), "%s %s",
			our_comb.work_pos.Ins.name,	our_comb.work_pos.Ins.surname);
			i = strlen(our_comb.work_pos.Ins.surname);
			our_comb.work_pos.Ins.surname[i-1] = '\0';

			hypertemp =
			strtok( &temp_str[comma_arr[SECOND]+2], ",," );

			for( i=0; hypertemp[i] != '\0'; ++i )
				our_comb.work_pos.Ins.department[i] = hypertemp[i];

			our_comb.work_pos.Ins.department[i] = '\0';

			sscanf( &temp_str[comma_arr[THIRD]+1], "%s",
			our_comb.work_pos.Ins.first_class);

			i = strlen(our_comb.work_pos.Ins.first_class);
			our_comb.work_pos.Ins.first_class[i-1] = '\0';

			sscanf( &temp_str[comma_arr[FOURTH]+1], "%s",
			our_comb.work_pos.Ins.second_class);

			i = strlen(our_comb.work_pos.Ins.second_class);
			our_comb.work_pos.Ins.second_class[i-1] = '\0';

			sscanf( &temp_str[comma_arr[FIFTH]+1], "%lf",
			&(our_comb.work_pos.Ins.salary));

			/*printf("%s %s, %s, %s, %s, %.2f\n", our_comb.work_pos.Ins.name,
			our_comb.work_pos.Ins.surname, our_comb.work_pos.Ins.department,
			our_comb.work_pos.Ins.first_class, our_comb.work_pos.Ins.second_class,
			our_comb.work_pos.Ins.salary);*/

		}
		our_comb = salary_rise(our_comb);
		fwrite( &our_comb, sizeof(combine_type), 1, binfile );

		comma_count=0;
	}


}
/*****************************************************************************
 * 						End of HW09 Part1                     				 *
 *****************************************************************************/
