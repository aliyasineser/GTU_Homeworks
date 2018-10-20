/*****************************************************************
 *                                                               *
 * HW10 Part2 Header File		                                 *
 * Student Name: Ali Yasin Eser                                  *
 * Student ID  : 141044058										 *
 * Date        : 20.05.2015                                      *
 *                                                               *
 ****************************************************************/
#ifndef PART2
#define PART2
#include "HW10_<AliYasin>_<Eser>_<141044058>_Part1.h"


extern node_t* build_ll(Appointment_t appointmens[],
int size, const Working_hours_t* hours);

extern void write_accepted_app(node_t* head, const Files_t* files);

extern void add_personal_data(node_t* head, const Files_t* files);

extern int delete_appointments(node_t** head, const Files_t* files);

extern void free_list(node_t* head);

extern void recursiveReverse( node_t** head_ref);

#endif
/*###########################################################################*/
/*              End of HW10_AliYasin_Eser_141044058_Part2.h                  */
/*###########################################################################*/
