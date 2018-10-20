/* 
 * File:   ComplexNumber.cpp
 * Author: aliyasineser
 * 
 * Created on December 15, 2015, 12:32 PM
 */



#include <stdlib.h>
#include <cmath>
#include "ComplexNumber.h"
const double ZERO = 0.0;
const double TEN = 10.0;
const double FOUR = 4.0;
const double ONE = 1.0;

namespace GTU_YASIN_NUMBERS {

    ComplexNumber::ComplexNumber() {
        setBoth(ZERO, ZERO);
    }

    ComplexNumber::ComplexNumber(double numForBoth) {
        setBoth(numForBoth, numForBoth);
    }

    ComplexNumber::ComplexNumber(const ComplexNumber& orig) {
        setBoth(orig.getFirst(), orig.getSec());
    }

    ComplexNumber::ComplexNumber(double _real, double _image) {
        setBoth(_real, _image);
    }

    double ComplexNumber::getFirst() const {
        return ((double) first_nom / first_denom);

    }

    double ComplexNumber::getSec() const {
        return ((double) sec_nom / sec_denom);

    }

    

    
    
    
    const ComplexNumber ComplexNumber::operator+(const ComplexNumber& other) const {
        return ComplexNumber((getFirstNom() * other.getFirstDenom() + getFirstDenom() * other.getFirstNom()) / (double) (getFirstDenom() * other.getFirstDenom()),
                (getSecNom() * other.getSecDenom() + getSecDenom() * other.getSecNom()) / (double) (getSecDenom() * other.getSecDenom()));

    }

    const ComplexNumber ComplexNumber::operator-(const ComplexNumber& other) const {
        return ComplexNumber((getFirstNom() * other.getFirstDenom() - getFirstDenom() * other.getFirstNom()) / (double) (getFirstDenom() * other.getFirstDenom()),
                (getSecNom() * other.getSecDenom() - getSecDenom() * other.getSecNom()) / (double) (getSecDenom() * other.getSecDenom()));
    }

    bool ComplexNumber::operator<(const ComplexNumber& other) const {
        
        if (getFirst() * getFirst() + getSec() * getSec() < other.getFirst() * other.getFirst() + other.getSec() * other.getSec())
            return true;
        else
            return false;
    }

    std::ostream & operator<<(std::ostream & outputStream, const ComplexNumber& our_comp_num) {
        outputStream << our_comp_num.getFirst() << " + (" << our_comp_num.getSec() << ")i";
        return outputStream;
    }

    void ComplexNumber::setFirst(double _first) {

        if (_first != ZERO) {
            first_denom = pow(TEN, FOUR);
            first_nom = _first * pow(TEN, FOUR);
        } else {

            first_denom = ONE;
            first_nom = ZERO;

        }
    }

    void ComplexNumber::setSec(double _sec) {
        if (_sec != ZERO) {
            sec_denom = pow(TEN, FOUR);
            sec_nom = _sec * pow(TEN, FOUR);
        } else {

            sec_denom = ONE;
            sec_nom = ZERO;

        }
    }

    void ComplexNumber::setBoth(double _first, double _sec) {


        if (_first != ZERO) {
            first_denom = pow(TEN, FOUR);
            first_nom = _first * pow(TEN, FOUR);
        } else {

            first_denom = ONE;
            first_nom = ZERO;

        }


        if (_sec != ZERO) {
            sec_denom = pow(TEN, FOUR);
            sec_nom = _sec * pow(TEN, FOUR);
        } else {

            sec_denom = ONE;
            sec_nom = ZERO;

        }
    }

    int ComplexNumber::getFirstNom() const {
        return first_nom;
    }

    int ComplexNumber::getSecNom() const {
        return sec_nom;
    }

    int ComplexNumber::getFirstDenom() const {

        return first_denom;
    }

    int ComplexNumber::getSecDenom() const {
        return sec_denom;
    }

}