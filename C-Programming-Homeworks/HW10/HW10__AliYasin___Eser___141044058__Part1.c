/*****************************************************************
 *                                                               *
 * HW10 Part1 Implementation File                                *
 * Student Name: Ali Yasin Eser                                  *
 * Student ID  : 141044058										 *
 * Date        : 20.05.2015                                      *
 *                                                               *
 ****************************************************************/
#include "HW10_<AliYasin>_<Eser>_<141044058>_Part1.h"
#define ONE 1
#define TRUE 1
#define FALSE 0
#define TWO 2
#define ZERO 0


/*Global olarak tanimlanmis default dosya isimleri*/
const char *records_file = "Records.bin";
const char *param_file = "Parameters.txt";
const char *delete_file = "Delete.txt";
const char *patient_file = "Patients.xml";
const char *readable_rec_file = "Records.xml";
const char *accepted_appo_file = "Appointments.csv";

/*###########################################################################*/

Appointment_t* getRequests(const Files_t* files, int* size)
{
	int i;
	Appointment_t *aptr;	/*Array icin pointer*/
	FILE *iptr;

	iptr = fopen(files->records_file_n, "rb");
	if(iptr == FALSE)
	{
		printf("Records file is missing.\n");
		exit(ONE);
	}
	fread(size, sizeof(int), ONE ,iptr);
	aptr = (Appointment_t*)calloc(*size, sizeof(Appointment_t));
	fread(aptr, sizeof(Appointment_t), *size, iptr);

	#ifdef DEBUG
	printf("Debug for array, control of patient id's and names.\n");
	for(i=0;i < *size; i++)
	{
		printf("Patient id of %d. element is %d\n", i, aptr[i].patient_id);
	}
	printf("End of array debug.\n");
	#endif


	fclose(iptr);

	sort(aptr, *size);

	return aptr;
}

/*###########################################################################*/

void write_appointments(Appointment_t appointments[],
	int size, const Files_t* files)
{
	/*Tum taglar initialize edilmis durumda*/
	char *start_size= "<Size>",
			 *end_size= "</Size>",
			 *start_rec = "<Records>",
			 *end_rec = "</Records>",
			 *start_appo = "<Appointment>",
			 *end_appo = "</Appointment>",
			 *start_app_id = "<app_id>",
			 *end_app_id = "</app_id>",
			 *start_patient_id = "<patient_id>",
			 *end_patient_id = "</patient_id>",
			 *start_hour = "<hour>",
			 *end_hour = "</hour>";
	int i;
	FILE *optr;

	optr = fopen(files->readable_records_file_n, "w");
	if(optr == FALSE)
	{
		printf("Can't open to write the readable records file\n");
		exit(ONE);
	}

	fprintf(optr, "%s%d%s\n",start_size, size, end_size );
	fprintf(optr, "%s\n", start_rec);
	for(i=0; i<size; i++)
	{
		fprintf(optr, "\t%s\n", start_appo);
		fprintf(optr, "\t\t%s%d%s\n", start_app_id,
		appointments[i].app_id, end_app_id);
		fprintf(optr, "\t\t%s%d%s\n", start_patient_id,
		appointments[i].patient_id, end_patient_id);
		fprintf(optr, "\t\t%s%d%s\n", start_hour,
		appointments[i].hour, end_hour);
		fprintf(optr, "\t%s\n", end_appo);
	}
	fprintf(optr, "%s\n", end_rec );

	fclose(optr);

}

/*###########################################################################*/

void get_main_arguments(int argc, char *argv[],
Working_hours_t* hours, Files_t* files)
{

	int i,temp, letter;
	/*Default atamalar*/
	files->readable_records_file_n = readable_rec_file;
  files->records_file_n = records_file;
  files->patients_file_n = patient_file;
  files->delete_file_n = delete_file;
  files->accepted_appo_file_n = accepted_appo_file;
  files->parameters_file_n = param_file;

  hours->start = START;
  hours->end = END;

	if(argc % TWO == ZERO)/*Arguman sayisi problemli ise*/
	{
		printf("You entered half argument, there isn't any argument for ");
		printf("\"%s\" descriptor.Program will ignore it. ", argv[argc-ONE]);
		printf("Please consider that and restart the program correctly.\n");
		argc--;
	}

		for(i=ONE; i<argc; i += TWO)
		{
			if(argv[i][ZERO] == '-')
			{
				letter = argv[i][ONE];
				switch (letter)
				{
					case 'r':
						temp = i+ONE;
						files->records_file_n = argv[temp];
						break;
					case 'p':
						temp = i+ONE;
						files->patients_file_n = argv[temp];
						break;
					case 'd':
						temp = i+ONE;
						files->delete_file_n = argv[temp];
						break;
					case 'x':
						temp = i+ONE;
						files->readable_records_file_n = argv[temp];
						break;
					case 'c':
						temp = i+ONE;
						files->accepted_appo_file_n = argv[temp];
						break;
					case 't':
						temp = i+ONE;
						files->parameters_file_n = argv[temp];
						break;
					case 's':
						temp = i+ONE;
						hours->start = atoi(argv[temp]);
						break;
					case 'e':
						temp = i+ONE;
						hours->end = atoi(argv[temp]);
						break;
					default:
						break;

				}
			}
			else
			{
				printf("\"%s\" is wrong. It must be a descriptor.\n", argv[i]);
				exit(ONE);
			}

		}
		#ifdef DEBUG
		printf("\nDebug of file names:\n");
		printf("Record binary file is: %s\n", files->records_file_n);
		printf("Patient file is: %s\n", files->patients_file_n);
		printf("Delete file is: %s\n", files->delete_file_n);
		printf("Readable record file is: %s\n", files->readable_records_file_n);
		printf("Accepted appointment file is: %s\n", files->accepted_appo_file_n);
		printf("Parameter file is: %s\n", files->parameters_file_n);
		printf("Start hour is: %d\n", hours->start);
		printf("End hour is: %d\n", hours->end);
		printf("Debug of file name is finished.\n\n");
		#endif

}

/*###########################################################################*/

void print_parameters(const Files_t* files, const Working_hours_t* hours)
{
	FILE *optr;

	optr = fopen(files->parameters_file_n, "w");
	if(optr == FALSE)
	{
		printf("Can't open to write the parameters file.\n");
		exit(ONE);
	}

	fprintf(optr, "%s\n", files->records_file_n);
	fprintf(optr, "%s\n", files->patients_file_n);
	fprintf(optr, "%s\n", files->delete_file_n);
	fprintf(optr, "%s\n", files->readable_records_file_n);
	fprintf(optr, "%s\n", files->accepted_appo_file_n);
	fprintf(optr, "%s\n", files->parameters_file_n);
	fprintf(optr, "%d\n", hours->start);
	fprintf(optr, "%d\n", hours->end);

	fclose(optr);

}

/*###########################################################################*/
/*Bu fonksiyon daha onceki odevlerde yazilmis ve bu odev icin duzenlenmistir*/

void sort(Appointment_t *array, int size )
{
	/*Randevulari erken saatten gec saate dizer*/
	int temp_patient, temp_appo, temp_hour, i,j, k;

	for(i=ZERO;i<size;i++)
	{
		  for(j=i+ONE;j<size;j++)
			{
		       if(array[i].hour > array[j].hour)
		       {
		          temp_patient = array[i].patient_id;
				  temp_appo = array[i].app_id;
				  temp_hour = array[i].hour;

				  array[i].patient_id = array[j].patient_id;
		   		  array[i].app_id = array[j].app_id;
				  array[i].hour = array[j].hour;

		          array[j].patient_id = temp_patient;
				  array[j].app_id = temp_appo;
				  array[j].hour = temp_hour;
		       }
			}
	}

	#ifdef DEBUG
	printf("Debug for array, control of patient id's and names.\n");
	for(k=ZERO;k < size; k++)
	{
		printf("Patient id of %d. element is %d\n", (k+ONE), array[k].app_id);
	}
	printf("End of array debug.\n");

	#endif

}
/*###########################################################################*/
/*              End of HW10_AliYasin_Eser_141044058_Part1.c                  */
/*###########################################################################*/
