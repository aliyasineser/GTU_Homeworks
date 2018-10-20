/* 
 * File:   RationalNumber.cpp
 * Author: aliyasineser
 * 
 * Created on December 15, 2015, 2:51 PM
 */

#include "RationalNumber.h"
#include <cmath>


const double ONE = 1.0;
const double ZERO = 0.0;
const double TEN = 10.0;
const double FOUR = 4.0;

using namespace std;

namespace GTU_YASIN_NUMBERS {

    RationalNumber::RationalNumber() {
        setBoth(ZERO, ONE);
    }

    RationalNumber::RationalNumber(int nom) {
        setBoth((nom), static_cast<int>(ONE));
    }

    RationalNumber::RationalNumber(int nom, int denom) {
        setBoth((nom), (denom));
    }

    RationalNumber::RationalNumber(double nom, double denom) {
        setBoth((nom), (denom));
    }

    RationalNumber::RationalNumber(const RationalNumber& orig) {
        setBoth(orig.getFirst(), orig.getSec());
    }

    
  
    
    
    const RationalNumber RationalNumber::operator+(const RationalNumber& other) const {
        return RationalNumber((getFirstNom() * other.getFirstDenom() + getFirstDenom() * other.getFirstNom()) / (double) (getFirstDenom() * other.getFirstDenom()),
                (getSecNom() * other.getSecDenom() + getSecDenom() * other.getSecNom()) / (double) (getSecDenom() * other.getSecDenom()));

    }

    const RationalNumber RationalNumber::operator-(const RationalNumber& other) const {
        return RationalNumber((getFirstNom() * other.getFirstDenom() - getFirstDenom() * other.getFirstNom()) / (double) (getFirstDenom() * other.getFirstDenom()),
                (getSecNom() * other.getSecDenom() - getSecDenom() * other.getSecNom()) / (double) (getSecDenom() * other.getSecDenom()));
    }

    bool RationalNumber::operator<(const RationalNumber& other) const {
        if (getFirst() * other.getSec() < getSec() * other.getFirst())
            return true;
        else
            return false;
    }

    std::ostream & operator<<(std::ostream & outputStream, const RationalNumber& our_rat_num) {
        outputStream << our_rat_num.getFirst() << "/" << our_rat_num.getSec();
        return outputStream;
    }

    void RationalNumber::setFirst(int _first) {
        if (_first != ZERO) {
            first_denom = pow(TEN, FOUR);
            first_nom = _first * pow(TEN, FOUR);
        } else {

            first_denom = ONE;
            first_nom = ZERO;

        }
    }

    void RationalNumber::setSec(int _sec) {
        if (_sec != ZERO) {
            sec_denom = pow(TEN, FOUR);
            sec_nom = abs(_sec * pow(TEN, FOUR));
        } else {

            sec_denom = ONE;
            sec_nom = ZERO;

        }
    }
    // Eksi isareti kesinlikle ilk sayida olmali

    void RationalNumber::setBoth(int _first, int _sec) {
        if (_first != ZERO) {
            first_denom = pow(TEN, FOUR);
            first_nom = _first * pow(TEN, FOUR);
        } else {

            first_denom = ONE;
            first_nom = ZERO;

        }
        if (_sec != ZERO) {
            sec_denom = pow(TEN, FOUR);
            sec_nom = abs(_sec * pow(TEN, FOUR));
        } else {

            sec_denom = ONE;
            sec_nom = ZERO;

        }
    }

    void RationalNumber::setBoth(double _first, double _sec) {
        if (_first != ZERO && _sec > ZERO) {
            first_denom = _sec;
            first_nom = _first;
            sec_denom = ONE;
            sec_nom = ZERO;
        } else {

            first_denom = ONE;
            first_nom = ZERO;
            sec_denom = ONE;
            sec_nom = ZERO;

        }
        
    }

    int RationalNumber::getFirst() const {
        return first_nom / first_denom;
    }

    int RationalNumber::getSec() const {
        return sec_nom / sec_denom;


    }


}