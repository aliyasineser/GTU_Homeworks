/*****************************************************************
 *                                                               *
 * HW10 Part2 Implementation File                                *
 * Student Name: Ali Yasin Eser                                  *
 * Student ID  : 141044058										 *
 * Date        : 20.05.2015                                      *
 *                                                               *
 ****************************************************************/
#include "HW10_<AliYasin>_<Eser>_<141044058>_Part1.h"
#include "HW10_<AliYasin>_<Eser>_<141044058>_Part2.h"
#define SO_MUCH_HISTORY 550
#define TRUE 1
#define FALSE 0
#define ONE 1
#define ZERO 0
#define TWO 2
#define NO_PROB 0
#define PROB 1


/*###########################################################################*/

node_t* build_ll(Appointment_t appointmens[], int size,
  const Working_hours_t* hours)
{
  int i,j,
      flag=NO_PROB; /*Saatler problemliyse listeye yazmaz*/

  node_t *head,
         *temp,
         *for_debug;

  head = NULL;/*Sondan basa dogru olusturulacagi icin once head'e Null atanir*/

  for(i=ZERO; i<size; i++)
  {
    if(i!=ZERO)/*Ilk asamada karsilastiracagi kimse olmayacak*/
    {
      for(j=i-ONE; j>=ZERO; j--)
      {
        if(appointmens[j].hour == appointmens[i].hour)
        {
          flag=PROB;/*sonraki if icinde bu duruma gore listeye eklenir*/
        }
      }
    }
    /*Saatler cakismiyorsa, randevu dogru saat araligindaysa*/
    if((flag != PROB) &&
      (appointmens[i].hour >= hours->start) &&
      (appointmens[i].hour < hours->end))
    {
      /*Yer ayrilir, icerik eklenir ve sonraki liste elemanina gecilir*/
      temp = (node_t*)calloc(ONE, sizeof(node_t));
      temp->app_id = appointmens[i].app_id;
      temp->patient_id = appointmens[i].patient_id;
      temp->hour = appointmens[i].hour;

      temp->next = head;
      head = temp;
    }
    flag = NO_PROB;/*Dongude tekrar kullanilmasi icin flag update*/

  }

  temp = head;
  /*Sondan basa olusturulan linked list'i ters cevirir*/
  recursiveReverse(&temp);

  #ifdef DEBUG
  for_debug = temp;
  printf("\nDebug with using patient id's:\n");
  while(for_debug)
  {
      printf("%d\n", for_debug->patient_id);
      for_debug = for_debug->next;
  }
  printf("Debug of build_ll is finished.\n\n");
  #endif


  return temp;
}

/*###########################################################################*/

void write_accepted_app(node_t* head, const Files_t* files)
{
  node_t *temp;
  int i=ONE;
  FILE *optr;

  optr = fopen(files->accepted_appo_file_n, "w");
  if(optr == FALSE)
  {
    printf("Accepted appointment file is missing.\n");
    exit(ONE);
  }
  /*Ilk node'dan sonuncuya kadar tek tek yazar*/
  for(temp=head;
      temp != NULL;
      temp = temp->next, i++)
  {
    fprintf(optr, "%d;%d;%d;%s;%s;%d\n", i, temp->app_id, temp->patient_id,
            temp->name, temp->history, temp->hour);
  }
}

/*###########################################################################*/

void add_personal_data(node_t* head, const Files_t* files)
{
  char *start_rec = "<Records>",
       *end_rec = "</Records>",
       *start_patient = "<Patient>",
       *end_patient = "</Patient>",
       *start_id = "<ID>",
       *end_id = "</ID>",
       *start_name = "<Name>",
       *end_name = "</Name>",
       *start_history = "<History>",
       *end_history = "</History>",
       temp[SO_MUCH_HISTORY] = "empty",
       *ingredient,
       *for_name,
       *for_history,
       *pos,
       *initialize,
       long_history[SO_MUCH_HISTORY];

  int flag=ONE, which,i,k, j;
  node_t *patient;
  FILE *iptr;

  iptr = fopen(files->patients_file_n, "r");
  if(iptr == FALSE)
  {
    printf("Patient file is missing.\n");
    exit(ONE);
  }
  patient = head;
  while(patient != NULL)/*Tum liste elemanlarinin stringlerini sifirlamak*/
  {
    patient->name[ZERO] = '\0';
    patient->history = (char*)malloc(sizeof(char));
    patient->history[ZERO] = '\0';
    patient = patient->next;
  }
  patient = head;
  #ifdef DEBUG
  printf("Debug of patient linked list:\n\n");
  #endif
  while (strstr(temp, start_rec) == NULL)
  {
    fgets(temp, SO_MUCH_HISTORY, iptr);
  }
  fgets(temp, SO_MUCH_HISTORY, iptr);
  do {
    if(strstr(temp, start_patient) != NULL)
    {
      fgets(temp, SO_MUCH_HISTORY, iptr);
      pos = strstr(temp, start_id);
      ingredient = strtok( &pos[strlen(start_id)-ONE], "><");

      /*Dogru id'ye sahip olan node'un bulunmasi*/
      for(patient = head;
          patient->next != NULL && patient->patient_id != atoi(ingredient);
          patient = patient->next)
      {}

        if(patient->patient_id == atoi(ingredient))/*Ikincil kontrol ve islem*/
        {
          fgets(temp, SO_MUCH_HISTORY, iptr);
          pos = strstr(temp, start_name);
          for_name = strtok( &pos[strlen(start_name)-ONE], "><");
          strcpy(patient->name, for_name);

          fgets(temp, SO_MUCH_HISTORY, iptr);

          /*History tag'inin okundugu kisim*/

          pos = strstr(temp, start_history);
          if( strstr(temp, end_history ) != NULL )/*Tek satirsa*/
          {
            for_history = strtok( &pos[strlen(start_history)-ONE], "><");
            free(patient->history);
            patient->history = (char*)calloc(strlen(for_history)+ONE,
             sizeof(char));
            strcpy(patient->history, for_history);
            if(patient->history[ZERO] == '/')
            {
              patient->history[ZERO] = '\0';
            }
          }
          else/*Cok satirsa*/
          {
            strcpy( long_history, &pos[strlen(start_history)] );
            fgets(temp, SO_MUCH_HISTORY, iptr);
            while( strstr(temp, end_history) == NULL )
            {
              strcat(long_history, temp);
              fgets(temp, SO_MUCH_HISTORY, iptr);
            }
            for_history = strtok( temp, "><");
            strcat(long_history, for_history);
            patient->history = (char*)calloc(strlen(long_history)+ONE,
             sizeof(char));
            strcpy(patient->history, long_history);
          }

          /*Ekstra uzun tab bosluklari icin*/
          for(k=ZERO; k<strlen(patient->history); k++)
          {
            if(patient->history[k] == '\t')
            {
              patient->history[k]  = ' ';
            }


          }

          /*History tag'i okundu*/

          #ifdef DEBUG
          printf("Patient ID:%d\n", patient->patient_id);
          printf("Patient name:%s\n" ,patient->name);
          printf("Patient history:%s\n\n" ,patient->history);
          #endif
        }
      fgets(temp, SO_MUCH_HISTORY, iptr);/*Cop patient kapatma tagi icin*/
    }
    fgets(temp, SO_MUCH_HISTORY, iptr);

  } while(strstr(temp, end_rec) == NULL);/*record tagi kapanmadikca devam*/

  #ifdef DEBUG
  printf("Debug of patient linked list is finished.\n");
  #endif

  fclose(iptr);
}

/*###########################################################################*/

int delete_appointments(node_t** head, const Files_t* files)
{
  int count=ZERO, curr_num, status;
  node_t *prev_ll = NULL,
         *curr_ll = *head,
         *for_debug;
  FILE *delptr;

  delptr = fopen(files->delete_file_n, "r");
  if(delptr == FALSE)
  {
    printf("Delete file is missing.\n");
    exit(ONE);
  }
  /*silinmesi gerekeni alip listede arar, bulunca siler*/
  for(status = fscanf(delptr, "%d", &curr_num);
      status != EOF;
      status = fscanf(delptr, "%d", &curr_num))
  {
    while(curr_ll != NULL)/*listede dolasmak icin dongu*/
    {
        if(curr_ll->app_id == curr_num)/*bulunca siler*/
        {
            if(prev_ll == NULL)/*ilk eleman ise*/
            {
                curr_ll = curr_ll->next;
                free((*head)->history);
                free(*head);
                *head = curr_ll;
                count++;
            }
            else  /*Ilk eleman degilse*/
            {
                prev_ll->next = curr_ll->next;
                free(curr_ll->history);
                free(curr_ll);
                curr_ll = prev_ll->next;
                count++;
            }
        }
        else  /*Bulunan node yanlis node ise*/
        {
            prev_ll = curr_ll;
            curr_ll = curr_ll->next;
        }
    }
    prev_ll = NULL;
    curr_ll = *head;
  }

  #ifdef DEBUG
  for_debug = *head;
  while(for_debug != NULL)
  {
    printf("Patient ID:%d\n", for_debug->patient_id);
    printf("Patient name:%s\n" ,for_debug->name);
    printf("Patient history:%s\n\n" ,for_debug->history);
    for_debug = for_debug->next;
  }
  #endif

  fclose(delptr);
  return count;
}

/*###########################################################################*/
/*Fonksiyon  internetten alinip program icin degistirilmistir*/
/*http://www.geeksforgeeks.org/
  write-a-function-to-reverse-the-nodes-of-a-linked-list/      */
/*Kaynak icin yorum satirindaki iki parcayi birlestirip siteye girin lutfen*/
void recursiveReverse( node_t** head_ref)
{
     node_t* first_ll;
     node_t* rest_ll;

    /* empty list */
    if (*head_ref == NULL)
       return;

    /* suppose first_ll = {1, 2, 3}, rest_ll = {2, 3} */
    first_ll = *head_ref;
    rest_ll  = first_ll->next;

    /* List has only one node */
    if (rest_ll == NULL)
       return;

    /* reverse the rest_ll list and put the first_ll element at the end */
    recursiveReverse(&rest_ll);
    first_ll->next->next  = first_ll;

    /* tricky step */
    first_ll->next  = NULL;

    /* baslangic pointer'ini duzeltme */
    *head_ref = rest_ll;
}

/*###########################################################################*/

void free_list(node_t* head)
{
    if(head == NULL){}/*Liste bos ise veya son elemana gelindiyse*/
    else
    {
      free(head->history);
      free_list(head->next);
    }

    free(head);
}
/*###########################################################################*/
/*              End of HW10_AliYasin_Eser_141044058_Part2.c                  */
/*###########################################################################*/
