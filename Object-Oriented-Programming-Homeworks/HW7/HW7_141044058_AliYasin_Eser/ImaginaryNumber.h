/* 
 * File:   ImaginaryNumber.h
 * Author: aliyasineser
 *
 * Created on December 15, 2015, 1:38 PM  
 */

#include "ComplexNumber.h"

#ifndef IMAGINARYNUMBER_H
#define	IMAGINARYNUMBER_H

namespace GTU_YASIN_NUMBERS {

    class ImaginaryNumber : public ComplexNumber {
    public:
        //Constructors
        ImaginaryNumber();
        ImaginaryNumber(double _image);
        ImaginaryNumber(const ImaginaryNumber& orig);// copy constructor

       //Operator overloads
        const ImaginaryNumber operator+(const ImaginaryNumber& other) const;
        const ImaginaryNumber operator-(const ImaginaryNumber& other) const;
        bool operator<(const ImaginaryNumber& other) const;
        friend std::ostream & operator<<(std::ostream & outputStream, const ImaginaryNumber& our_img_num);

    };
}

#endif	/* IMAGINARYNUMBER_H */



