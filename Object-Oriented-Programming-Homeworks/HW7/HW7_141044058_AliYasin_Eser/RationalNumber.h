/* 
 * File:   RationalNumber.h
 * Author: aliyasineser
 *
 * Created on December 15, 2015, 2:51 PM
 */

#ifndef RATIONALNUMBER_H
#define	RATIONALNUMBER_H

#include "RealNumber.h"



namespace GTU_YASIN_NUMBERS {

    class RationalNumber : public RealNumber {
    public:
        //Constructors
        RationalNumber();
        RationalNumber(int nom);
        RationalNumber(int nom, int denom);
        RationalNumber(double nom, double denom);
        RationalNumber(const RationalNumber& orig);// copy constructor

        //Operator Overloads
        const RationalNumber operator+(const RationalNumber& other) const;
        const RationalNumber operator-(const RationalNumber& other) const;
        bool operator<(const RationalNumber& other) const;
        friend std::ostream & operator<<(std::ostream & outputStream, const RationalNumber& our_rat_num);

        //Getters, Setters, redefine
        void setFirst(int _first);
        void setSec(int _sec);
        void setBoth(int _first, int _sec);
        void setBoth(double _first, double _sec);
        int getFirst() const;
        int getSec() const;


    };
}
#endif	/* RATIONALNUMBER_H */

