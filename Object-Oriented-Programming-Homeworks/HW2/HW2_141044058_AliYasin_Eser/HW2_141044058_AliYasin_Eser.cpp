/* 
 * File:   HW2_141044058_AliYasin_Eser.cpp
 * HW2 icin hazirlanmis programdir, esitlik fonksiyonu hazirlanmis 
 * herhangi bir tip veya class icin mod operasyonu yapar
 * Author: aliyasineser
 *
 * Created on 19 Ekim 2015 Pazartesi, 23:38
 */

#include "DayOfYear.h"
#include <cstdlib>
#include <iostream>
#include <cstring>


using namespace std;

const int STRING_SIZE = 80; // Test string size

struct PersonInfo { // Test struct
    char name[STRING_SIZE];
    char sname[STRING_SIZE];
    DayOfYear birth;

};
// Function prototypes
int return_mode(const void * base, size_t num, size_t size, bool (* equals) (const void *, const void *));
bool compare_of_char_variables(const void* el1, const void* el2);
bool compare_of_int_variables(const void* el1, const void* el2);
bool compare_of_double_variables(const void* el1, const void* el2);
bool compare_of_str_variables(const void* el1, const void* el2);
bool compare_of_DayOfYear_variables(const void* el1, const void* el2);
bool compare_of_PersonInfo_variables(const void* el1, const void* el2);


int main(int argc, char** argv) { // Test main


    int array_of_int[] = {26, 24, 45, 4, 4, 26, 41, 35, 4, 34, 34};
    int size_of_int_array = 11;
    cout << "Mode of Int: " << return_mode(array_of_int, size_of_int_array, sizeof (int), compare_of_int_variables) << endl;

    double array_of_double[] = {1.00, 2.00, 11.00, 55.00, 34.00, 54.00, 55.00, 55.00, 54.00, 45.00, 10.00};
    int size_of_double_array = 11;
    cout << "Mode of Double: " << return_mode(array_of_double, size_of_double_array, sizeof (double), compare_of_double_variables) << endl;

    char array_of_char[] = {'b', 'a', 'e', 'a', 'c', 'c', 'e', 'a', 'e', 'f', 'b', 'a', 'e'};
    int size_of_char_array = 13;
    cout << "Mode of Char: " << return_mode(array_of_char, size_of_char_array, sizeof (char), compare_of_char_variables) << endl;

    char str_arr[7][STRING_SIZE];
    strcpy(str_arr[0], "Hello mate");
    strcpy(str_arr[1], "Hello mates!");
    strcpy(str_arr[2], "Hello mate");
    strcpy(str_arr[3], "Hello mates");
    strcpy(str_arr[4], "Hello mates");
    strcpy(str_arr[5], "Hello mate");
    strcpy(str_arr[6], "Hello mates!");
    int size_of_string_array = 7;
    cout << "Mode of String: " << return_mode(str_arr, size_of_string_array, STRING_SIZE, compare_of_str_variables) << endl;

    DayOfYear day_array[6];
    day_array[0].setMonthAndDay(10, 21);
    day_array[1].setMonthAndDay(3, 6);
    day_array[2].setMonthAndDay(3, 23);
    day_array[3].setMonthAndDay(11, 2);
    day_array[4].setMonthAndDay(3, 23);
    day_array[5].setMonthAndDay(4, 22);
    int size_of_dayofyear_array = 6;
    cout << "Mode of DayOfYear: " << return_mode(day_array, size_of_dayofyear_array, sizeof (DayOfYear), compare_of_DayOfYear_variables) << endl;

    PersonInfo people[7];
    strcpy(people[0].name, "Joe"); strcpy(people[0].sname, "Satriani");
    strcpy(people[1].name, "Steve"); strcpy(people[1].sname, "Vai");
    strcpy(people[2].name, "Steve"); strcpy(people[2].sname, "Vai");
    strcpy(people[3].name, "Eric"); strcpy(people[3].sname, "Johnson");
    strcpy(people[4].name, "John"); strcpy(people[4].sname, "Petrucci");
    strcpy(people[5].name, "John"); strcpy(people[5].sname, "Petrucci");
    strcpy(people[6].name, "John"); strcpy(people[6].sname, "Petrucci");
    int size_of_person_array = 7;
    cout << "Mode of PersonInfo: " << return_mode(people, size_of_person_array, sizeof (PersonInfo), compare_of_PersonInfo_variables) << endl;

    return 0;
}
/*Compare function for DayOfYear Class variables*/
bool compare_of_DayOfYear_variables(const void* el1, const void* el2) {


    DayOfYear* p1 = (DayOfYear*) el1;
    DayOfYear* p2 = (DayOfYear*) el2;

    if (p1->getMonth() == p2->getMonth() && p1->getDay() == p2->getDay())
        return true;

    return false;


}
/*Compare function for Double variables*/
bool compare_of_double_variables(const void* el1, const void* el2) {


    double* p1 = (double*) el1;
    double* p2 = (double*) el2;

    if (*p1 == *p2)
        return true;

    return false;


}
/*Compare function for PersonInfo struct variables*/
bool compare_of_PersonInfo_variables(const void* el1, const void* el2) {
    PersonInfo* p1 = (PersonInfo*) el1;
    PersonInfo* p2 = (PersonInfo*) el2;

    if (compare_of_str_variables(&(p1->name), &(p2->name)) && // Same name string
            compare_of_str_variables(&(p1->sname), &(p2->sname)) && // Same surname string
            compare_of_DayOfYear_variables(&(p1->birth), &(p2->birth))) // Same birth day
        return true;



    return false;
}
/*Compare function for string's*/
//Uses cstring
bool compare_of_str_variables(const void* el1, const void* el2) {


    char* p1 = (char*) el1;
    char* p2 = (char*) el2;

    if (strcmp(p1, p2) == 0)
        return true;

    return false;


}
/*Compare function for int variables*/
bool compare_of_int_variables(const void* el1, const void* el2) {


    int* p1 = (int*) el1;
    int* p2 = (int*) el2;

    if (*p1 == *p2)
        return true;

    return false;


}
/*Compare function for char variables*/
bool compare_of_char_variables(const void* el1, const void* el2) {


    char* p1 = (char*) el1;
    char* p2 = (char*) el2;

    if (*p1 == *p2)
        return true;

    return false;


}
/*Return mode function*/
// Modu belirleyen degerin array'de ilk bulunan indisini gonderir
int return_mode(const void * base, size_t num, size_t size, bool (* equals) (const void *, const void *)) {
    unsigned char* elem = (unsigned char*) base; // Ilk elemani gosteren pointer

    unsigned char* most_frequent = (unsigned char*) base; // Modu belirleyen elemani gosteren pointer

    unsigned char* end = (unsigned char*) base + (size * num); // Son elemani gosteren pointer

    int counter_of_most_frequent = 0, temp_counter = 0; // Mod icin counter ve gecici counter


    for (; elem < end; elem += size) {
        temp_counter = 1; // Kendisini de saymasi gerektigi icin birden basliyor
        for (unsigned char* cursor_elem = elem + size; cursor_elem < end; cursor_elem += size)
            if ((*equals)(elem, cursor_elem) == true)
                temp_counter++;

        if (temp_counter > counter_of_most_frequent) {
            counter_of_most_frequent = temp_counter;
            most_frequent = elem;
        }


    }
    // Mod bulundu, index bulunmali
    unsigned char* temp_elem = (unsigned char*) base;
    int index_of_first_elem = 0;
    for (index_of_first_elem; true; index_of_first_elem++, temp_elem = (temp_elem + size)) {
        if ((*equals)(temp_elem, most_frequent))
            return index_of_first_elem;
    }



}