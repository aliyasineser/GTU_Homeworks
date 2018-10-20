/* 
 * File:   ImaginaryNumber.cpp
 * Author: aliyasineser
 * 
 * Created on December 15, 2015, 1:38 PM
 */

#include "ImaginaryNumber.h"


const int ZERO = 0.0;


namespace GTU_YASIN_NUMBERS {

    ImaginaryNumber::ImaginaryNumber() : ComplexNumber(ZERO, ZERO) {

    }

    ImaginaryNumber::ImaginaryNumber(double _image) : ComplexNumber(ZERO, _image) {
    }

    ImaginaryNumber::ImaginaryNumber(const ImaginaryNumber& orig) {
        setBoth(orig.getFirst(), orig.getSec());

    }

    const ImaginaryNumber ImaginaryNumber::operator+(const ImaginaryNumber& other) const {
        ImaginaryNumber answer;
        answer.setBoth(ZERO, getSec() + other.getSec());
        return answer;
    }

    const ImaginaryNumber ImaginaryNumber::operator-(const ImaginaryNumber& other) const {
        ImaginaryNumber answer;
        answer.setBoth(ZERO, getSec() - other.getSec());
        return answer;
    }

    bool ImaginaryNumber::operator<(const ImaginaryNumber& other) const {
        if (getSec() < other.getSec())
            return true;
        else
            return false;
    }

    std::ostream & operator<<(std::ostream & outputStream, const ImaginaryNumber& our_img_num) {
        outputStream << our_img_num.getSec() << "i";
        
        return outputStream;
    }



}