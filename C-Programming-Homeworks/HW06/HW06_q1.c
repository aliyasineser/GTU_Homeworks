/*This file is written by Meltem Çetiner*/
#include <stdio.h>
#include <stdio.h>
#include <string.h>

typedef enum {Ali, Ayse, Fatma, Mehmet}employee;
typedef enum {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday}day; 

#define NUM_EMPLOYEES 4
#define NUM_DAYS 7
#define ENERGIES "Energies.txt"
#define REPORT "report.txt"

void read_matrix(const char* file_name, int m[NUM_EMPLOYEES][NUM_DAYS]);
void create_work_plan(int job_schedule[NUM_EMPLOYEES][NUM_DAYS], int m[NUM_EMPLOYEES][NUM_DAYS]);
int index_sort(const int m[],const int n,int ordinal);
void sort(int* mat1,int* mat2,const int size );
employee find_the_employer_of_the_day(int work_schedule[NUM_EMPLOYEES][NUM_DAYS], day day_name);
employee find_the_employer_of_the_week(int work_schedule[NUM_EMPLOYEES][NUM_DAYS]);
void report(const char* file_name, int job_scheduling[NUM_EMPLOYEES][NUM_DAYS]);

int main()
{
	printf("..starting.\n");
	int job_energies[NUM_EMPLOYEES][NUM_DAYS], schedule[NUM_EMPLOYEES][NUM_DAYS]; 
        
	read_matrix(ENERGIES, job_energies);
        create_work_plan(schedule, job_energies);

	report(REPORT, schedule);
	printf("..finishing.\n");
    
}

void read_matrix(const char* file_name, int m[NUM_EMPLOYEES][NUM_DAYS])
{
    day c_day;
    employee c_employee; //counters 
    
    FILE *inp;
    inp = fopen(file_name,"r");

    if( inp == NULL)
      printf( " The file [ %s ] couldnt be found ..\n", file_name);
    
    else
    {
    	for(c_day=Monday; c_day < NUM_DAYS; c_day++)
    	{
    		for( c_employee=Ali; c_employee < NUM_EMPLOYEES; c_employee++)
    		{  
    		    	if( fscanf( inp, "%d", &m[c_employee][c_day]) == EOF)
				m[c_employee][c_day] = 0;
		}
	}
    }

    fclose(inp);
}

void create_work_plan(int job_schedule[NUM_EMPLOYEES][NUM_DAYS], int m[NUM_EMPLOYEES][NUM_DAYS])
{
	day c_day;
        employee c_employee;
        int c_job, counter=0; 
        int total_energies[NUM_EMPLOYEES]={0,0,0,0};
	int daily_works[]={0,0,0,0};
        
        /*initializing*/
	for ( c_employee=Ali ; c_employee<NUM_EMPLOYEES ; c_employee++)
	{
		for( c_day=Monday; c_day<NUM_DAYS; c_day++)
			job_schedule[ c_employee ][ c_day ] = 0 ;
		daily_works[c_employee] = 0 ;	
	}		
	        
	/*filling the job_schedule matrix*/
	for( c_day=Monday; c_day<NUM_DAYS; c_day++)
	{
		for ( c_employee=Ali; c_employee<NUM_EMPLOYEES ; c_employee++)
			daily_works[c_employee]=m[c_employee][c_day];

		int ordinality[]={ 0 , 1 , 2 , 3};

		sort(daily_works,ordinality, NUM_EMPLOYEES);
		
		for ( c_job=0 ; c_job<NUM_EMPLOYEES ; c_job++)
		{
			int index_employee = index_sort(total_energies,NUM_EMPLOYEES,c_job);
			//printf("index %d : \t",index_employee);
			job_schedule[ index_employee ][ c_day ] =daily_works[NUM_EMPLOYEES-(c_job+1)];
			//printf("job_schedule[ %d ][ %d ] =%d :\n", index_employee , c_day , daily_works[ c_job ] );			
			
		}
		
		for ( c_job=0 ; c_job<NUM_EMPLOYEES ; c_job++)
			total_energies[ c_job ] += job_schedule[ c_job ][ c_day ] ;
		
	}
}

employee find_the_employer_of_the_day(int work_schedule[NUM_EMPLOYEES][NUM_DAYS], day day_name)
{	

	int i, max = work_schedule[0][(int)day_name];
	employee employee = 0;

	for(i=1; i < NUM_EMPLOYEES; i++)
	{
		if(max < work_schedule[i][(int)day_name])
		{
			max = work_schedule[i][(int)day_name];
			employee = i;
		}
	}
	
	return employee;	
	
}	

employee find_the_employer_of_the_week(int work_schedule[][NUM_DAYS])
{
	int i, j, sum, max = -1;
	employee employee = 0;
	
	for(i=Ali; i < NUM_EMPLOYEES; i++)
	{
		sum = 0;
		
		/* find total energy  of the employee */ 
		
		for(j=0; j < NUM_DAYS; j++)
		{
			sum += work_schedule[i][j];
		}	
		
		/* compare it to maximum sum value */
		
		if(max < sum)
		{
			max = sum;
			employee = i;
		}	
	}

	return employee;
}
	
void report(const char* file_name, int job_scheduling[][NUM_DAYS])
{
	
	/* I've created strings same order in enumerated types for ease printing. */
	
	char employees[NUM_EMPLOYEES][20] = {"Ali", "Ayse", "Fatma", "Mehmet"};
	char days[NUM_DAYS][10] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"}; 
	int i, j, employee;
	FILE *output;
	
	output = fopen(file_name, "w");
	
	fprintf(output, "\nReport:\n\n");

	fprintf(output, "	");
	
	/* print days to file */
	
	for(i=Monday; i < NUM_DAYS; i++)
	{
		fprintf(output, " %s", &days[i][0]);
	}
	
	fprintf(output, "\n\n");
	
	for(i=Ali; i < NUM_EMPLOYEES; i++)
	{
		/*  print i. employee's name to file */
		
		fprintf(output, "%s", &employees[i][0]);
	
		/* print i. employee's job schedule to file */
		 
		for(j=0; j < NUM_DAYS; j++)
		{
			fprintf(output, "	   %d", job_scheduling[i][j]);
		}	
		
		fprintf(output, "\n\n");
	}
	
	/* find the most worked employee for each day and print to file */
	
	for(i=Monday; i < NUM_DAYS; i++)
	{
		employee = find_the_employer_of_the_day(job_scheduling, (day)i);

		fprintf(output, "The best employer of %s: %s\n\n", &days[i][0], &employees[(int)employee][0]);
	}
	
	/* find the employer of week and print to file */

	
	employee = find_the_employer_of_the_week(job_scheduling);

	fprintf(output, "The best employer of week is %s ... Congratulations %s\n\n", &employees[(int)employee][0], &employees[(int)employee][0]);
 		
	fclose(output);
}	



/* params: this function takes an array m with size n and 	*/
/*         an ordinal number                                    */
/* aim   : it finds the index of m matrix on ordinal number	*/
/* returns its index						*/
/*								*/
/* for example; we have m[4]={100,60,70,50}         		*/
/* if we call (m,4,2)                               		*/
/*        it finds 2.biggest number 70 and returns 2    	*/
/* for another example; 					*/
/*   lets say there are some equal numbers  and we have		*/
/*   m[4]={100,60,60,50}                        		*/
/* if we call (m,4,2)                               		*/
/*        it finds 2.biggest number 60 and returns 1    	*/
/* it will returns first finding index	 			*/
int index_sort(const int m[],const int n,const int ordinal)
{
	int counter;
        int sorted_m[n],sorted_index[n];

	for( counter=0; counter<n; counter++ )
	{
		sorted_m[counter]  = m[counter];
		sorted_index[counter] = counter;
	}
		
	sort(sorted_m,sorted_index,n);
        
        return sorted_index[ordinal];
}


/*this function takes two paralel matrices with their size	*/
/*and sorts both of them from biggest to smallest in sync       */
/*								*/
/*For example; mat1[4]={100,40,60,50} mat2[4]={0,1,2,3}		*/
/*------------------after sorting-------------------------------*/
/*             mat1[4]={100,60,50,40} mat2[4]={0,2,3,1}		*/
void  sort(int* mat1,int* mat2,const int size )
{
	int c_a,c_b, temp;
	
        for( c_a=0; c_a<size ; c_a++)
	{
		for( c_b=(c_a+1) ; c_b<size ; c_b++)
		{
			if( mat1[c_a] < mat1[c_b])
			{
 				temp      = mat1[c_a];
				mat1[c_a] = mat1[c_b];
				mat1[c_b] = temp;

				temp      = mat2[c_a];
				mat2[c_a] = mat2[c_b];
				mat2[c_b] = temp;
			}
		}
	}

}

