/*****************************************************************
 *                                                               *
 * HW10 Part2 Test Driver File	                                 *
 * Student Name: Ali Yasin Eser                                  *
 * Student ID  : 141044058										 *
 * Date        : 20.05.2015                                      *
 *                                                               *
 ****************************************************************/
#include "HW10_<AliYasin>_<Eser>_<141044058>_Part1.h"
#include "HW10_<AliYasin>_<Eser>_<141044058>_Part2.h"



int
main(int argc, char *argv[])
{
  int size=0,i, count_deleted;
  Files_t our_files;
  Working_hours_t our_hours;
  Appointment_t *app_aptr;
  node_t *head_ll;


  get_main_arguments( argc, argv, &our_hours, &our_files );

  app_aptr = getRequests(&our_files, &size);

  write_appointments(app_aptr, size, &our_files);

  print_parameters( &our_files, &our_hours);


  head_ll = build_ll( app_aptr, size, &our_hours );


  add_personal_data(head_ll, &our_files);

  count_deleted = delete_appointments(&head_ll, &our_files);

  #ifdef DEBUG
  printf("\nDeleted %d appointmens.\n", count_deleted);
  #endif

  write_accepted_app(head_ll, &our_files);

  free_list(head_ll);



  return 0;

}
/*###########################################################################*/
/*              End of HW10_AliYasin_Eser_141044058_Test2.c                  */
/*###########################################################################*/
