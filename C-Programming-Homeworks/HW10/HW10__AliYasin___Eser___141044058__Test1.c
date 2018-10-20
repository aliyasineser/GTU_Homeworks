/*****************************************************************
 *                                                               *
 * HW10 Part1 Test Driver File	                                 *
 * Student Name: Ali Yasin Eser                                  *
 * Student ID  : 141044058										 *
 * Date        : 20.05.2015                                      *
 *                                                               *
 ****************************************************************/
#include "HW10_<AliYasin>_<Eser>_<141044058>_Part1.h"
#define ZERO 0


int
main(int argc, char *argv[])
{
  int size=ZERO;
  Files_t our_files;
  Working_hours_t our_hours;
  Appointment_t *app_aptr;

  get_main_arguments( argc, argv, &our_hours, &our_files );

  app_aptr = getRequests(&our_files, &size);

  sort(app_aptr, size);

  write_appointments(app_aptr, size, &our_files);

  print_parameters( &our_files, &our_hours);

  return 0;

}
/*###########################################################################*/
/*              End of HW10_AliYasin_Eser_141044058_Test1.c                  */
/*###########################################################################*/
