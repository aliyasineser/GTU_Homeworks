/*****************************************************************
 *                                                               *
 * HW10 Part1 Header File  	 	                                 *
 * Student Name: Ali Yasin Eser                                  *
 * Student ID  : 141044058										 *
 * Date        : 20.05.2015                                      *
 *                                                               *
 ****************************************************************/
#ifndef PART1
#define PART1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FOR_NAME 50

#define START 9
#define END 17

extern const char *records_file;
extern const char *param_file;
extern const char *delete_file;
extern const char *patient_file;
extern const char *readable_rec_file;
extern const char *accepted_appo_file;

typedef struct{
	int app_id,
			patient_id,
			hour;
}Appointment_t;

typedef struct{
	int start,
			end;
}Working_hours_t;


typedef struct{
	const char *records_file_n,
		*patients_file_n,
		*delete_file_n,
		*readable_records_file_n,
		*accepted_appo_file_n,
		*parameters_file_n;
}Files_t;


typedef struct node_s{
	int app_id,
		patient_id,
		hour;
	char *history,
		name[FOR_NAME];
	struct node_s *next;
}node_t;



extern Appointment_t* getRequests(const Files_t* files, int* size);
extern void write_appointments(Appointment_t appointments[],
	int size, const Files_t* files);
extern void get_main_arguments(int argc, char *argv[],
	Working_hours_t* hours, Files_t* files);
extern void print_parameters(const Files_t* files,
	const Working_hours_t* hours);
extern void sort(Appointment_t *array, int size );

#endif
/*###########################################################################*/
/*              End of HW10_AliYasin_Eser_141044058_Part1.h                  */
/*###########################################################################*/
