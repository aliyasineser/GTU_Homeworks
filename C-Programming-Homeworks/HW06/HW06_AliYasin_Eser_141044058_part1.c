/*************************************************************
 *                                                           *
 * HW06_Part1                                                *
 * Student Name: Ali Yasin ESER                              *
 * Student ID  : 141044058                                   *
 * Date        : 05.04.2015                                  *
 *                                                           *
 *************************************************************/
#include <stdio.h>
#include <string.h>
#define NUM_EMPLOYEES 4
#define NUM_DAYS 7

/*Calisanlar ve gunler icin tip tanimlamalari*/
typedef enum { Ali, Ayse, Fatma, Mehmet } employee;
typedef enum { Monday ,Tuesday ,Wednesday 
	,Thursday ,Friday ,Saturday ,Sunday } day;

/*Fonksiyonlarin tanitilmasi*/
void read_matrix(const char* file_name, int m[NUM_EMPLOYEES][NUM_DAYS]);
void report(const char* file_name,
	 int job_scheduling[NUM_EMPLOYEES][NUM_DAYS]);
employee find_the_employer_of_the_day
	(int work_schedule[NUM_EMPLOYEES][NUM_DAYS], day day_name);
void create_work_plan(int job_schedule[NUM_EMPLOYEES][NUM_DAYS], 
	int m[NUM_EMPLOYEES][NUM_DAYS]);
employee find_the_employer_of_the_week(
	int work_schedule[NUM_EMPLOYEES][NUM_DAYS]);
void sort_of_pointers(int array[], int size, int en_arr[], int job_arr[] );
void sort(int array[], int size);
int max_array(int array[], int n);
void reverse_array(int a[], int n );


int
main()
{
	int job_energies[NUM_EMPLOYEES][NUM_DAYS];/*Degerler icin matris*/
	int schedule[NUM_EMPLOYEES][NUM_DAYS];/*Duzenlenmis tablo*/
	const char our_file[30]="Energies.txt";/*Enerji degerleri*/
	const char our_output[30]="Report.txt";/*Cikti tablosu*/
	
	
	
	read_matrix(our_file, job_energies);
	create_work_plan(schedule, job_energies);
	report(our_output ,schedule);
	
	
	return 0;
}



void read_matrix(const char* file_name, int m[NUM_EMPLOYEES][NUM_DAYS])
{
	int sayi;	/*Donguye girmesi icin ilk deger*/
	int i=0,j=0;	/*Matrisin elemanlari icin counter*/
	int control;
	FILE *iptr = fopen(file_name, "r");
	if(iptr == NULL)/* Acilmazsa uyari*/
		printf("The input file can't be read. Don't trust the output!");
		
		/*Matrisin okunan degerler doldurulmasi*/
	for(control = fscanf(iptr, "%d", &sayi); 
		control != EOF; 
		control = fscanf(iptr, " %d", &sayi))
	{
		if(j>= NUM_EMPLOYEES){
			i++;
			j=0;
			m[j++][i] = sayi;
			}
		else{
			m[j++][i] = sayi;
			}
	}
	fclose(iptr);	/*Dosyanin kapatilmasi*/
	
	
}
void report(const char* file_name, int job_scheduling[NUM_EMPLOYEES][NUM_DAYS])
{
	
	int i, j;	/**Counter'lar*/
	char for_name[20];
	employee our_emp;
	char for_day[20];
	day all_day;
	FILE *optr = fopen(file_name, "w");
	if(optr == NULL)/* Acilmazsa uyari*/
		printf("The output file can't be write.");
	
	/*Tablonun duzenli cikmasi icin*/
	for(i=0; i<10; i++)
		fprintf(optr, " ");
	
	/*Gunun yazdirilmasi icin*/
	for(all_day=Monday; all_day <= Sunday; all_day++)
	{
	
		switch(all_day)
		{
			case Monday:
				strcpy(for_day, "Monday");
				break;
			case Tuesday:
				strcpy(for_day, "Tuesday");
				break;
			case Wednesday:
				strcpy(for_day, "Wednesday");
				break;
			case Thursday:
				strcpy(for_day, "Thursday");
				break;
			case Friday:
				strcpy(for_day, "Friday");
				break;
			case Saturday:
				strcpy(for_day, "Saturday");
				break;
			case Sunday:
				strcpy(for_day, "Sunday");
				break;
		}
		
		fprintf(optr, "%-12s  ", for_day);
	}
	
	fprintf(optr,"\n");
	
	/*Matrisin basilmasi*/
	for(i=0; i< NUM_EMPLOYEES; i++)
	{
	/*Ismin basilmasi icin*/
		switch(i)
	{
		case 0:
			strcpy(for_name, "Ali");
			break;
		case 1:
			strcpy(for_name, "Ayse");
			break;
		case 2:
			strcpy(for_name, "Fatma");
			break;
		case 3:
		strcpy(for_name, "Mehmet");
			break;
	}
	
	
		fprintf(optr, "%-8s : ", for_name);
		
		for(j=0; j< NUM_DAYS; j++)
		{
			fprintf(optr, "%-12d  ", job_scheduling[i][j]);
		}
		fprintf(optr,"\n"); 
		
		
	}
	
	for(all_day=Monday; all_day <= Sunday; all_day++)
	{
		/*Gunun enerji degerlerine gore en iyinin bulunmasi*/
		our_emp = find_the_employer_of_the_day( job_scheduling, all_day);
		/*Isimlerin degismes*/
		switch((int)our_emp)
		{
			case 0:
				strcpy(for_name, "Ali");
				break;
			case 1:
				strcpy(for_name, "Ayse");
				break;
			case 2:
				strcpy(for_name, "Fatma");
				break;
			case 3:
			strcpy(for_name, "Mehmet");
				break;
		}
		/*Gunlerin degismesi*/
		switch(all_day)
		{
			case Monday:
				strcpy(for_day, "Monday");
				break;
			case Tuesday:
				strcpy(for_day, "Tuesday");
				break;
			case Wednesday:
				strcpy(for_day, "Wednesday");
				break;
			case Thursday:
				strcpy(for_day, "Thursday");
				break;
			case Friday:
				strcpy(for_day, "Friday");
				break;
			case Saturday:
				strcpy(for_day, "Saturday");
				break;
			case Sunday:
				strcpy(for_day, "Sunday");
				break;
		}
		
		fprintf(optr,"The best employer of %s : %s\n", for_day, for_name);
	}
	
		fprintf(optr, "\n");
		
		
		
	
		/*Gunun enerji degerlerine gore en iyinin bulunmasi*/	
		our_emp = find_the_employer_of_the_week( job_scheduling);
		
		/*Birinci icin degerleri*/
		switch((int)our_emp)
		{
			case 0:
				strcpy(for_name, "Ali");
				break;
			case 1:
				strcpy(for_name, "Ayse");
				break;
			case 2:
				strcpy(for_name, "Fatma");
				break;
			case 3:
			strcpy(for_name, "Mehmet");
				break;
		}
		
		fprintf(optr, "The best employer of the week is ");
		fprintf(optr, "%s :  Congratulations %s !!\n", for_name, for_name);
	
		
	
	
}



employee find_the_employer_of_the_day
	(int work_schedule[NUM_EMPLOYEES][NUM_DAYS], day day_name)
{
	int comp_arr[NUM_EMPLOYEES];	/*kontrol edilecek deger*/
	employee best;	/*Gunun enerji degerlerine gore en iyinin bulunmasi*/
	int i;
	
	
		
	for( i=0; i < NUM_EMPLOYEES; i++ )
		comp_arr[i] = work_schedule[i][day_name];
	
	i = max_array(comp_arr, NUM_EMPLOYEES);
	
	best = (employee)i;
	

	
	return best;
	
}
void create_work_plan(int job_schedule[NUM_EMPLOYEES][NUM_DAYS], 
						int m[NUM_EMPLOYEES][NUM_DAYS])
{
	day counter_of_days;
	int arr_ener[NUM_EMPLOYEES], i, total=0, j, k, r, z;
	int enerp[NUM_EMPLOYEES];
	int energ_irre[NUM_EMPLOYEES];
	
	/*Pazartesi gunu icin islemlerin baslangici*/
	for(i=0;i<NUM_EMPLOYEES;i++)
		energ_irre[i]=m[i][0];

	sort(energ_irre , NUM_EMPLOYEES);
	
	for(i=0;i<NUM_EMPLOYEES;i++)
		job_schedule[i][0]=energ_irre[i];
	/*Pazartesi gunu icin islemlerin bitisi*/


	for(counter_of_days=Tuesday; counter_of_days <= Sunday; counter_of_days++)
	{
		for(j=0; j<NUM_EMPLOYEES; j++)
		{
			for(i=0; i < (int)(counter_of_days); i++)
			{
				total += job_schedule[j][i];	/*Toplam enerjiler*/
			}
			
			arr_ener[j] = total;	
			energ_irre[j] = m[j][counter_of_days];
			
			
			total=0;
		}
		
		/* toplam enerji degerlerini gosterecek array */
		for(k=0; k<NUM_EMPLOYEES; k++)
		{
			 enerp[k] = k;
		}
		
		/*for(i=0;i<NUM_EMPLOYEES;i++)
			printf("%d	", arr_ener[i]);
			printf("\n");*/
		/*Duzenleme*/
		sort_of_pointers(arr_ener, NUM_EMPLOYEES, enerp, energ_irre);
		sort(energ_irre , NUM_EMPLOYEES);
		
		/*for(i=0;i<NUM_EMPLOYEES;i++){
				printf("%d	%d	%d\n", enerp[i], energ_irre[i], arr_ener[i]);}
				
			printf("\n\n");*/
			
				
		for(r=0; r<NUM_EMPLOYEES; r++)
			job_schedule[ NUM_EMPLOYEES - 
			enerp[r] - 1 ][counter_of_days] = energ_irre[r];
					
	
		
	
	}
		
	
}
employee find_the_employer_of_the_week(
int work_schedule[NUM_EMPLOYEES][NUM_DAYS])
{
	int j, i, comp_week[NUM_EMPLOYEES], best, total;

	/*O hafta icinde en cok enerji harcayani dondurur*/
	for(j=0; j<NUM_EMPLOYEES; j++)
		{
			for(i=0; i < (int)(Sunday); i++)
			{
				total += work_schedule[j][i];
			}
			
			comp_week[j] = total;	
			
			total=0;
		}	
	
	best = max_array(comp_week, NUM_EMPLOYEES);
	
	return (employee)best;
	
	
}

void sort(int array[], int size )
{
	/*Sayiyi buyukten kucuk dize*/
	int temp,i,j;
	for(i=0;i<size;i++){
		  for(j=i+1;j<size;j++){
		       if(array[i]<array[j])
		       {
		          temp=array[i];
		          array[i]=array[j];
		          array[j]=temp;
		       }}}
}

void sort_of_pointers(int array[], int size, int en_arr[],int job_arr[] )
{
	int temp;
	int i,j, k;
	int temp_arr[NUM_EMPLOYEES];
	
	/*Diziyi gosteren pointer dizinin duzenlenmesi*/

		for(i=0;i<size;i++)
		{
			temp=max_array(array, size);
			en_arr[i]=temp;
			array[temp]= -1;
		
		}

}
/* Dizideki maksimumun bulunmais */
int max_array(int array[], int n)
{
	int temp=0;/*En buyuk deger*/
	int i=1;
	
	
	
	
	for( i=1; i < n ; i++ )
		if( array[temp] <= array[i]  )
			temp = i;
		
			
			
	return temp;
}
/*###########################################################################*/
/*              End of HW06_Ali_Yasin_ESER_141044058_part1.c                      */
/*###########################################################################*/
