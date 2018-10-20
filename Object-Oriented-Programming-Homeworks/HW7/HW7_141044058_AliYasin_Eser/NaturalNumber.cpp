/* 
 * File:   NaturalNumber.cpp
 * Author: aliyasineser
 * 
 * Created on December 16, 2015, 3:59 PM
 */

#include "NaturalNumber.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
const int ZERO = 0;
const double TEN = 10.0;
const double FOUR = 4.0;
const double ONE = 1.0;
using namespace std;


namespace GTU_YASIN_NUMBERS {

    NaturalNumber::NaturalNumber() {
        setFirst(ZERO);
        setSec(ZERO);
    }

    NaturalNumber::NaturalNumber(int _num) {
        setFirst(_num);
        setSec(ZERO);
    }
    
    NaturalNumber::NaturalNumber(int _num, int _junk) {
        setFirst(_num);
        setSec(ZERO);
    }
    

    NaturalNumber::NaturalNumber(const NaturalNumber& orig) {
        setFirst(orig.getFirst());
    }

    const NaturalNumber NaturalNumber::operator+(const NaturalNumber& other) const {
        return NaturalNumber((getFirstNom() * other.getFirstDenom() + getFirstDenom() * other.getFirstNom()) / (double) (getFirstDenom() * other.getFirstDenom()),
                (getSecNom() * other.getSecDenom() + getSecDenom() * other.getSecNom()) / (double) (getSecDenom() * other.getSecDenom()));
    }

    const Integer NaturalNumber::operator-(const NaturalNumber& other) const {
        return Integer((getFirstNom() * other.getFirstDenom() - getFirstDenom() * other.getFirstNom()) / (double) (getFirstDenom() * other.getFirstDenom()),
                (getSecNom() * other.getSecDenom() - getSecDenom() * other.getSecNom()) / (double) (getSecDenom() * other.getSecDenom()));
    }

    bool NaturalNumber::operator<(const NaturalNumber& other) const {
        if (getFirst() < other.getFirst())
            return true;
        else
            return false;
    }

    std::ostream & operator<<(std::ostream & outputStream, const NaturalNumber& our_nat_num) {
        outputStream << our_nat_num.getFirst();
        return outputStream;
    }

    void NaturalNumber::setFirst(int _first) {
        if (_first > ZERO)
            if (_first != ZERO) {
                first_denom = pow(TEN, FOUR);
                first_nom = _first * pow(TEN, FOUR);
            } else {

                first_denom = ONE;
                first_nom = ZERO;

            } else {
            cerr << "Natural numbers must be greater than zero or must be zero." << endl;
            exit(1);
        }
    }

    int NaturalNumber::getFirst() const {
        return first_nom / first_denom;

    }



} 