/* 
 * File:   Integer.cpp
 * Author: aliyasineser
 * 
 * Created on December 16, 2015, 1:25 AM
 */

#include "Integer.h"
#include <cstdlib>
#include <cmath>
const int ZERO = 0;

const double TEN = 10.0;
const double FOUR = 4.0;
const double ONE = 1.0;
namespace GTU_YASIN_NUMBERS {

    Integer::Integer() {
        setBoth(ZERO, ZERO);
    }

    Integer::Integer(int _num) {
        setBoth(_num, ZERO);
    }

    Integer::Integer(int _num, int _junk) {
        setBoth(_num, ZERO);
    }

    Integer::Integer(const Integer& orig) {
        setFirst(orig.getFirst());

    }

    const Integer Integer::operator+(const Integer& other) const {

        return Integer((getFirstNom() * other.getFirstDenom() + getFirstDenom() * other.getFirstNom()) / (double) (getFirstDenom() * other.getFirstDenom()),
                (getSecNom() * other.getSecDenom() + getSecDenom() * other.getSecNom()) / (double) (getSecDenom() * other.getSecDenom()));
    }

    const Integer Integer::operator-(const Integer& other) const {
        return Integer((getFirstNom() * other.getFirstDenom() - getFirstDenom() * other.getFirstNom()) / (double) (getFirstDenom() * other.getFirstDenom()),
                (getSecNom() * other.getSecDenom() - getSecDenom() * other.getSecNom()) / (double) (getSecDenom() * other.getSecDenom()));
    }

    bool Integer::operator<(const Integer& other) const {
        if (getFirst() < other.getFirst())
            return true;
        else
            return false;
    }

    std::ostream & operator<<(std::ostream & outputStream, const Integer& our_int_num) {

        outputStream << our_int_num.getFirst();
        return outputStream;
    }

    void Integer::setFirst(int _first) {
        if (_first != ZERO) {
            first_denom = pow(TEN, FOUR);
            first_nom = _first * pow(TEN, FOUR);
        } else {

            first_denom = ONE;
            first_nom = ZERO;

        }
    }

    void Integer::setSec(int _sec) {
        if (_sec != ZERO) {
            sec_denom = pow(TEN, FOUR);
            sec_nom = abs(_sec * pow(TEN, FOUR));
        } else {

            sec_denom = ONE;
            sec_nom = ZERO;

        }
    }

    int Integer::getFirst() const {
        return first_nom / first_denom;

    }

    void Integer::setBoth(int _first, int _sec) {


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



}