/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *            HW05_Kaan_Ucar_141044089_part2.c               *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description                                               *
 *___________________________________________________________*
 *	 This program calculates maximum value,second maximum    *
 * value,sum of array.Counts all different values in array   *
 * and searches values in array until user wants to quit.    *
 * Prints all results to the screen.                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *-----------------------------------------------------------*
 *                          Includes                         *
 *-----------------------------------------------------------*/
#include <stdio.h>
#include <conio.h>

/*-----------------------------------------------------------*
 *                     Defines                               *
 *-----------------------------------------------------------*/
typedef enum{FALSE,TRUE} bool;

/*-----------------------------------------------------------*
 *                Function Prototypes                        *
 *-----------------------------------------------------------*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Finds maximum value in an array.                          * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
int max_array(const int array[], int n);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Finds second maximum value in an array.                   * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
int second_max_array(const int array[], int n);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Calculates sum of all values in an array.                 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
int sum_all_array (const int array[], int n);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Counts number of value in an array.                       * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
int count_array(const int array[], int n, int value);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Searches a value in an array.                          * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
bool search_array (const int array[], int n, int value);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Prints maximum value,second maximum value and sum of      *
 * array.Counts all values in array and print them.Does not  *
 * count same values more than one time.Gets a value from    *
 * user and searches it in array.Then asks user for another  *
 * search.Keeps taking value and searching it in array until *
 * user does not want to search.                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
int main()
{
	int myarray[9]={6,8,3,3,12,8,3,8,2},size=9,result,value,i,j;
	bool check=TRUE;
	char selection;

	printf("+++++++++++++++++++++++++++++++++++++++++++++++\n");
	result=max_array(myarray, size);
	printf("Maximum array is %d\n",result);

	printf("+++++++++++++++++++++++++++++++++++++++++++++++\n");
	result=second_max_array(myarray, size);
	printf("Maximum second array is %d\n",result);

	printf("+++++++++++++++++++++++++++++++++++++++++++++++\n");
	result=sum_all_array(myarray, size);
	printf("Sum of all array is %d\n",result);

	printf("+++++++++++++++++++++++++++++++++++++++++++++++\n");
	result=count_array(myarray,size,myarray[0]);
	printf("Count of value %d is %d\n",myarray[0],result);
	for(i=1;i<size;++i)
	{
		for(j=0;j<i;++j)
		{
			if(myarray[i]==myarray[j])
				check=FALSE;
		}
		if(check==TRUE)
		{
			result=count_array(myarray,size,myarray[i]);
			printf("Count of value %d is %d\n",myarray[i],result);
		}
		check=TRUE;
	}

	printf("+++++++++++++++++++++++++++++++++++++++++++++++\n");
	do{
		printf("\nEnter a value for learn to location of it.\n");
		scanf("%d",&value);
		check=search_array (myarray,size,value);
		if(check==FALSE)
			printf("\nThere is no %d in this array\n",value);
		printf("+++++++++++++++++++++++++++++++++++++++++++++++\n");
		printf("Do you want to search another value?(Y/N)\n");
		do{
			scanf("%c",&selection);
		}while(selection!='Y'&&selection!='N'&&selection!='y'&&selection!='n');
	}while(selection=='Y'||selection=='y');

	return 0;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Takes first element of array as max.Reads array elements  *
 * starting by 1.When finds bigger value assigns it to max.  *
 * Returns max.                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
int max_array(const int array[], int size)
{
	int max,i;

	max=array[0];
	for(i=1;i<size;++i)
	{
		if(max<array[i])
			max=array[i];
	}
	return max;
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Takes first element of array as max.Reads array elements  *
 * starting by 1.When finds bigger value assigns it to max   *
 * and assigns old max to second_max.Returns second_max.     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
int second_max_array(const int array[], int size)
{
	int max,i,second_max;

	max=array[0];
	second_max=array[0];
	for(i=1;i<size;++i)
	{
		if(max<array[i])
		{
			second_max=max;
			max=array[i];
		}
	}
	if(max==array[0])
	{
		second_max=array[1];
		for(i=2;i<size;++i)
		{
			if(second_max<array[i])
				second_max=array[i];
		}


}
	return second_max;
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Takes an array and size of it.Returns sum of all array.   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
int sum_all_array (const int array[], int size)
{
	int sum,i;

	sum=array[0];
	for(i=1;i<size;++i)
		sum+=array[i];

	return sum;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Takes a value, an array and size of it.Counts number of   *
 * value and returns it.                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
int count_array(const int array[], int size, int value)
{
	int count=0,i;

	for(i=0;i<size;++i)
	{
		if(array[i]==value)
			++count;
	}

	return count;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Takes a value, an array and size of it.Reads all array    *
 * elements and checks whether the same value.If finds a     *
 * element as same value returns TRUE and prints the location*
 * of element.Else returns FALSE.                            *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
bool search_array (const int array[], int size, int value)
{
	int i;
	bool check=FALSE;

	for(i=0;i<size;++i)
	{
		if(value==array[i])
		{
			printf("%d is at [%d]\n",value,i);
			check=TRUE;
		}
	}
	return check;
}
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *            End of HW05_Kaan_Ucar_141044089_part2.c        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */ 
