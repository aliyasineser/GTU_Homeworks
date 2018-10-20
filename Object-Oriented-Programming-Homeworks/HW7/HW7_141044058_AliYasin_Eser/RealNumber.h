/* 
 * File:   RealNumber.h
 * Author: aliyasineser
 *
 * Created on December 15, 2015, 2:32 PM
 */

#ifndef REALNUMBER_H
#define	REALNUMBER_H

#include "ComplexNumber.h"

namespace GTU_YASIN_NUMBERS {

    class RealNumber : public ComplexNumber {
    public:
        //Constructors
        RealNumber();
        RealNumber(double _real);
        RealNumber(const RealNumber& orig);// copy constructor
        RealNumber(double _real, double _junk);
        
        //Operator overloads
        const RealNumber operator+(const RealNumber& other) const;
        const RealNumber operator-(const RealNumber& other) const;
        bool operator<(const RealNumber& other) const;
        friend std::ostream & operator<<(std::ostream & outputStream, const RealNumber& our_real_num);

    };
}

#endif	/* REALNUMBER_H */

