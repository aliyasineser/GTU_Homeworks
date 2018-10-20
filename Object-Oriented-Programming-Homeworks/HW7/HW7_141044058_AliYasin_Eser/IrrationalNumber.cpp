/* 
 * File:   IrrationalNumber.cpp
 * Author: aliyasineser
 * 
 * Created on December 17, 2015, 1:16 AM
 */

#include "IrrationalNumber.h"
#include <stdlib.h>
#include <cmath>
const double ZERO = 0.0;
const double TEN = 10.0;
const double FOUR = 4.0;
const double ONE = 1.0;
const double TWO = 2.0;
const double NINE = 9.0;

using namespace std;

namespace GTU_YASIN_NUMBERS {

    IrrationalNumber::IrrationalNumber() : RealNumber(ZERO, ZERO) {
    }

    IrrationalNumber::IrrationalNumber(double _real) : RealNumber(_real, ZERO) {
    }

    IrrationalNumber::IrrationalNumber(double _real, double _junk) : RealNumber(_real, ZERO) {
    }

    IrrationalNumber::IrrationalNumber(const IrrationalNumber& orig) {

        setBoth(orig.getFirst(), orig.getSec());
    }

    const IrrationalNumber IrrationalNumber::operator+(const IrrationalNumber& other) const {
        return IrrationalNumber((getFirstNom() * other.getFirstDenom() + getFirstDenom() * other.getFirstNom()) / (double) (getFirstDenom() * other.getFirstDenom()),
                (getSecNom() * other.getSecDenom() + getSecDenom() * other.getSecNom()) / (double) (getSecDenom() * other.getSecDenom()));
    }

    const IrrationalNumber IrrationalNumber::operator-(const IrrationalNumber& other) const {
        return IrrationalNumber((getFirstNom() * other.getFirstDenom() - getFirstDenom() * other.getFirstNom()) / (double) (getFirstDenom() * other.getFirstDenom()),
                (getSecNom() * other.getSecDenom() - getSecDenom() * other.getSecNom()) / (double) (getSecDenom() * other.getSecDenom()));
    }

    bool IrrationalNumber::operator<(const IrrationalNumber& other) const {
        if (getFirst() < other.getFirst())
            return true;
        else
            return false;
    }

    std::ostream & operator<<(std::ostream & outputStream, const IrrationalNumber& our_irrat_num) {
        outputStream << our_irrat_num.getFirst();
        return outputStream;
    }

    double IrrationalNumber::getFirst() const {
        return ((double) first_nom / first_denom);

    }

    double IrrationalNumber::getSec() const {
        return ((double) sec_nom / sec_denom);

    }

    void IrrationalNumber::setBoth(double _first, double _sec) {


        if (_first != ZERO) {
            first_denom = pow(TEN, NINE);
            first_nom = _first * pow(TEN, NINE);
            
        } else {

            first_denom = ONE;
            first_nom = ZERO;

        }


        if (_sec != ZERO) {
            sec_denom = pow(TEN, NINE);
            sec_nom = _sec * pow(TEN, NINE);
        } else {

            sec_denom = ONE;
            sec_nom = ZERO;

        }
    }


}