/* 
 * File:   RealNumber.cpp
 * Author: aliyasineser
 * 
 * Created on December 15, 2015, 2:32 PM
 */

#include "RealNumber.h"
const double ZERO = 0.0;

namespace GTU_YASIN_NUMBERS {

    RealNumber::RealNumber() : ComplexNumber(ZERO, ZERO) {
    }

    RealNumber::RealNumber(double _real) : ComplexNumber(_real, ZERO) {
    }

    RealNumber::RealNumber(double _real, double _junk) : ComplexNumber(_real, ZERO) {
    }

    RealNumber::RealNumber(const RealNumber& orig) {

        setBoth(orig.getFirst(), orig.getSec());
    }

    const RealNumber RealNumber::operator+(const RealNumber& other) const {
        return RealNumber((getFirstNom() * other.getFirstDenom() + getFirstDenom() * other.getFirstNom()) / (double) (getFirstDenom() * other.getFirstDenom()),
                (getSecNom() * other.getSecDenom() + getSecDenom() * other.getSecNom()) / (double) (getSecDenom() * other.getSecDenom()));
    }

    const RealNumber RealNumber::operator-(const RealNumber& other) const {
        return RealNumber((getFirstNom() * other.getFirstDenom() - getFirstDenom() * other.getFirstNom()) / (double) (getFirstDenom() * other.getFirstDenom()),
                (getSecNom() * other.getSecDenom() - getSecDenom() * other.getSecNom()) / (double) (getSecDenom() * other.getSecDenom()));
    }

    bool RealNumber::operator<(const RealNumber& other) const {
        if (getFirst() < other.getFirst())
            return true;
        else
            return false;
    }

    std::ostream & operator<<(std::ostream & outputStream, const RealNumber& our_real_num) {
        outputStream << our_real_num.getFirst();
        return outputStream;
    }



}