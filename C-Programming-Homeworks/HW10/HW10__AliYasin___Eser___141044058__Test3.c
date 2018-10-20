/*****************************************************************
 *                                                               *
 * HW10 Part3 Test Driver File	                                 *
 * Student Name: Ali Yasin Eser                                  *
 * Student ID  : 141044058										 *
 * Date        : 20.05.2015                                      *
 *                                                               *
 ****************************************************************/
#include "HW10_<AliYasin>_<Eser>_<141044058>_Part1.h"
#include "HW10_<AliYasin>_<Eser>_<141044058>_Part2.h"
#include "HW10_<AliYasin>_<Eser>_<141044058>_Part3.h"
#define FOR_HISTORY_STR 100


int
main(int argc, char *argv[])
{
  int size=0,i, count_deleted;
  Files_t our_files;
  Working_hours_t our_hours;
  Appointment_t *app_aptr;
  node_t *head_ll,
         *head_sec_ll,
         *temp1_ll,
         *temp2_ll;


  get_main_arguments( argc, argv, &our_hours, &our_files );

  app_aptr = getRequests(&our_files, &size);

  head_ll = build_ll( app_aptr, size, &our_hours );

  add_personal_data(head_ll, &our_files);

  write_accepted_app(head_ll, &our_files);

  head_sec_ll = make_independent_copy_ll(head_ll);

  /*Kopyanin sorunsuz oldugunun kaniti*/
  temp1_ll = head_ll;
  printf("########################################\n");
  printf("Original linked list with members:\n\n");
  while(temp1_ll != NULL)
  {
    printf("Patient ID:%d\n", temp1_ll->patient_id);
    printf("Patient name:%s\n" ,temp1_ll->name);
    printf("Patient history:%s\n\n" ,temp1_ll->history);
    temp1_ll = temp1_ll->next;
  }
  printf("########################################\n");

  temp2_ll = head_sec_ll;
  printf("########################################\n");
  printf("Independent copy linked list with members:\n\n");
  while(temp2_ll != NULL)
  {
    printf("Patient ID:%d\n", temp2_ll->patient_id);
    printf("Patient name:%s\n" ,temp2_ll->name);
    printf("Patient history:%s\n\n" ,temp2_ll->history);
    temp2_ll = temp2_ll->next;
  }
  printf("########################################\n");

  /*Sonraki kisimda kopya liste degistiriliyor*/

  temp2_ll = head_sec_ll;
  i=1;
  while(temp2_ll != NULL)
  {
    free(temp2_ll->history);
    temp2_ll->history = (char*)calloc( FOR_HISTORY_STR , sizeof(char) );
    sprintf(temp2_ll->history, "This is %d. node of copy list.", i);
    i++;
    temp2_ll = temp2_ll->next;
  }

  /*Listelerin farkli oldugunun kaniti*/

  printf("If we edit the independent copy and don't edit the original, ");
  printf("results will be change.\nOriginal list doesn't change but " );
  printf("independent copy will change.\nSo, results:\n\n");

  temp1_ll = head_ll;
  printf("########################################\n");
  printf("After editing, original linked list with members:\n\n");
  while(temp1_ll != NULL)
  {
    printf("Patient ID:%d\n", temp1_ll->patient_id);
    printf("Patient name:%s\n" ,temp1_ll->name);
    printf("Patient history:%s\n\n" ,temp1_ll->history);
    temp1_ll = temp1_ll->next;
  }
  printf("########################################\n");

  temp2_ll = head_sec_ll;
  printf("########################################\n");
  printf("After editing, independent copy linked list with members:\n\n");
  while(temp2_ll != NULL)
  {
    printf("Patient ID:%d\n", temp2_ll->patient_id);
    printf("Patient name:%s\n" ,temp2_ll->name);
    printf("Patient history:%s\n\n" ,temp2_ll->history);
    temp2_ll = temp2_ll->next;
  }
  printf("########################################\n");

  /*Kanitlandi, simdi listeler free edilmeli */

  free_list(head_ll);
  free_list(head_sec_ll);

  return 0;

}
/*###########################################################################*/
/*              End of HW10_AliYasin_Eser_141044058_Test3.c                  */
/*###########################################################################*/
