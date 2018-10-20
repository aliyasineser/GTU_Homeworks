/* 
 * File:   DayOfYear.h
 * Author: aliyasineser
 * Karsilastirma testi icin yazilmis bir class olan DayOfYear'in header dosyasidir
 * 
 * Created on 23 Ekim 2015 Cuma, 00:44
 */

#ifndef DAYOFYEAR_H
#define	DAYOFYEAR_H

class DayOfYear {
public:
    DayOfYear(int monthValue = 1, int dayValue = 1);

    void setMonthAndDay(int _month, int _day);

    int getMonth() const;
    int getDay() const;

    void input();
    void output() const;

private:
    int month;
    int day;
};

#endif	/* DAYOFYEAR_H */

