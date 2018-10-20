/* 
 * File:   main.cpp
 * Author: aliyasineser
 *
 * Created on December 16, 2015, 6:39 PM
 */

#include <cstdlib>
#include <cmath>
#include <iostream>
#include "ComplexNumber.h"
#include "RealNumber.h"
#include "RationalNumber.h"
#include "Integer.h"
#include "NaturalNumber.h"
#include "IrrationalNumber.h"

using namespace std;
using namespace GTU_YASIN_NUMBERS;

/*
 * 
 */
int main(int argc, char** argv) {

    ComplexNumber comp(0, 9);
    RealNumber real(11.64);
    RationalNumber rat(23, 6);
    Integer integ(4.23);
    NaturalNumber nat(2);
    IrrationalNumber irrat(5.68888);



    cout << "Stream insertion test: " << endl;

    cout << "Complex Num: " << comp << endl;
    cout << "Real Num: " << real << endl;
    cout << "Rational Num: " << rat << endl;
    cout << "Integer Num: " << integ << endl;
    cout << "Natural Num: " << nat << endl;
    cout << "Irrational Num: " << irrat << endl;
    cout << endl << endl << endl;

    cout << "Some sum test: " << endl;

    cout << "Complex + Real: " << comp + real << endl;
    cout << "Complex + Rational: " << comp + rat << endl;
    cout << "Real + Natural: " << comp + nat << endl;
    cout << "Complex + Integer: " << comp + integ << endl;
    cout << "Real + Rational: " << real + rat << endl;

    cout << endl << endl << endl;
    cout << "Some extraction test: " << endl;

    cout << "Complex - Real: " << comp - real << endl;
    cout << "Complex - Rational: " << comp - rat << endl;
    cout << "Real - Natural: " << comp - nat << endl;
    cout << "Complex - Integer: " << comp - integ << endl;
    cout << "Real - Rational: " << real - rat << endl;

    cout << "Some smaller test: 1 for true, 0 for false" << endl;


    cout << endl << endl << endl;
    cout << "Complex < Real: " << (comp < real) << endl;
    cout << "Complex <Rational: " << (comp < rat) << endl;
    cout << "Real < Natural: " << (comp < nat) << endl;
    cout << "Complex < Integer: " << (comp < integ) << endl;
    cout << "Real < Rational: " << (real < rat) << endl;


    return 0;
}

