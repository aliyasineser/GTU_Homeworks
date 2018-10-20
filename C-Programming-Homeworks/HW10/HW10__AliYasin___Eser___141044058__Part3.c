/*****************************************************************
 *                                                               *
 * HW10 Part3 Implementation File                                *
 * Student Name: Ali Yasin Eser                                  *
 * Student ID  : 141044058										 *
 * Date        : 20.05.2015                                      *
 *                                                               *
 ****************************************************************/
#include "HW10_<AliYasin>_<Eser>_<141044058>_Part1.h"
#include "HW10_<AliYasin>_<Eser>_<141044058>_Part2.h"
#include "HW10_<AliYasin>_<Eser>_<141044058>_Part3.h"
#define TRUE 1
#define FALSE 0
#define ZERO 0
#define ONE 1
#define TWO 2

node_t* make_independent_copy_ll(node_t* head)
{

  node_t *temp_first, /*Ilk head pointer icin gecici pointer*/
         *temp_sec, /*Ikinci head pointer icin gecici pointer*/
         *head_sec, /*Kopya olan liste icin head pointer*/
         *previous, /*Onceki liste node'unu saklamak icin pointer*/
         *for_debug;


  #ifdef DEBUG
  for_debug = head;
  printf("Debug of first linked list.\n");
  while(for_debug != NULL)
  {
    printf("Patient ID:%d\n", for_debug->patient_id);
    printf("Patient name:%s\n" ,for_debug->name);
    printf("Patient history:%s\n\n" ,for_debug->history);
    for_debug = for_debug->next;
  }
  #endif

  head_sec = NULL;  /*Liste ters olusacagi icin null simdiden atanir*/

  if(head == NULL)  /* Eleman yoksa */
  {
    head_sec = NULL;
    return head_sec;
  }
  else /* Eleman varsa */
  {

    temp_first = head;

    while(temp_first != NULL) /*Elaman kalmayincaya kadar kopyalanir*/
    {
      temp_sec = (node_t*)calloc(ONE, sizeof(node_t));

      temp_sec->app_id = temp_first->app_id;
      temp_sec->patient_id = temp_first->patient_id;
      strcpy(temp_sec->name, temp_first->name);
      temp_sec->history = (char*)malloc(strlen(temp_first->history)+1);
      strcpy(temp_sec->history, temp_first->history);
      temp_sec->hour = temp_first->hour;


      temp_sec->next = head_sec;
      temp_first = temp_first->next;
      head_sec = temp_sec;

    }

    temp_sec = NULL; /*Son elemanin sonlandirilmasi*/

  }

  recursiveReverse(&head_sec); /*Listenin duzeltilmesi*/

  temp_sec = head_sec;

  #ifdef DEBUG
  for_debug = head_sec;
  printf("Debug of independent copy linked list.\n" );
  while(for_debug != NULL)
  {
    printf("Patient ID:%d\n", for_debug->patient_id);
    printf("Patient name:%s\n" ,for_debug->name);
    printf("Patient history:%s\n\n" ,for_debug->history);
    for_debug = for_debug->next;
  }
  #endif



  return head_sec;
}
/*###########################################################################*/
/*              End of HW10_AliYasin_Eser_141044058_Part3.c                  */
/*###########################################################################*/
