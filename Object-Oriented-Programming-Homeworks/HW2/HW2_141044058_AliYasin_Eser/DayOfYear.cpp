/* 
 * File:   DayOfYear.cpp
 * Author: aliyasineser
 * Karsilastirma testi icin yazilmis bir class olan DayOfYear'in implementation dosyasidir
 * 
 * Created on 23 Ekim 2015 Cuma, 00:44
 */

#include "DayOfYear.h"
#include <iostream>
#include <cstdlib>

using namespace std;

// Class constructor, verilen degerler olmadiginda 1 degeri atanir
DayOfYear::DayOfYear(int monthValue, int dayValue): month(monthValue),
                                                    day(dayValue)
{}


// Class doldurmak icin kullanicidan input alir   
void DayOfYear::input()
{
    cout << "Please enter the month as number" << endl;
    cin >> month;
    cout << "Please enter the day as number" << endl;
    cin >> day;
    
    if( month < 0 || month > 12 || day < 0 || day > 31 )
    {
        cerr << "Invalid month or day" << endl;
        exit(1);
    }
}


// Class icin uygun cikti basar
void DayOfYear::output() const
{
    cout << "Month value: " << month << endl;

    cout << "Day value: " << day << endl;


}


// Verilen degerde atamalari yapar
void DayOfYear::setMonthAndDay(int _month, int _day)
{
    month = _month;
    day = _day;    
    
}

 // Ayi dondurur
int DayOfYear::getMonth() const
{
    return month;
 
}
// Gunu dondurur
int DayOfYear::getDay() const

{
    return day;
    
}