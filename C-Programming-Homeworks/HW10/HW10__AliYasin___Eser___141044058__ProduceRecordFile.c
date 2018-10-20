/*****************************************************************
 *                                                               *
 * HW10 Produce Record File Full Program                         *
 * Student Name: Ali Yasin Eser                                  *
 * Student ID  : 141044058										 *
 * Date        : 20.05.2015                                      *
 *                                                               *
 ****************************************************************/
 
 /*Program icinde 3 ve katlari sayilar bulunan bir text dosyasi bulundugu *
  *ve bu text dosyasinin ismi dogru verildigi durumda calisir.			  */
 
#include <stdio.h>
#include <string.h>

typedef struct{
	int app_id,
		patient_id,
		hour;
}Appointment_t;

void read_and_write(FILE *text, FILE* binary, int size );

int
main()
{
  int size_arr=0, i, a, b, c;
  FILE *iptr, *optr;

  iptr = fopen("HyperPatient.txt", "r");
  optr = fopen("Records.bin", "wb");

  for(i=fscanf(iptr, "%d %d %d", &a, &b, &c);
      i != EOF;
      i=fscanf(iptr, "%d %d %d", &a, &b, &c))
  {
    size_arr ++;
  }
  fclose(iptr);
  iptr = fopen("HyperPatient.txt", "r");
  read_and_write(iptr, optr, size_arr);

  fclose(iptr);
  fclose(optr);

  return 0;
}

void read_and_write(FILE *text, FILE* binary, int size )
{
  int i,status;
  Appointment_t temp_arr;
  
  fwrite(&size, sizeof(int), 1, binary);
  for(i=0; i<size; i++)
  {
    fscanf(text, "%d %d %d", &(temp_arr.app_id), &(temp_arr.patient_id),
    &(temp_arr.hour));
    fwrite(&temp_arr, sizeof(Appointment_t), 1, binary);
  }

}
/*###########################################################################*/
/*        End of HW10_AliYasin_Eser_141044058_ProduceRecordFile.c            */
/*###########################################################################*/
