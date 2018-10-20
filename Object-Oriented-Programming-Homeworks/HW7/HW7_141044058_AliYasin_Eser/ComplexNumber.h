/* 
 * File:   ComplexNumber.h
 * Author: aliyasineser
 *
 * Created on December 16, 2015, 6:42 PM
 */

#ifndef COMPLEXNUMBER_H
#define	COMPLEXNUMBER_H

#include <iostream>
namespace GTU_YASIN_NUMBERS {

    class ComplexNumber {
    public:
        //Constructors
        ComplexNumber();
        ComplexNumber(double numForBoth);
        ComplexNumber(const ComplexNumber& orig);// copy constructor
        ComplexNumber(double _real, double _image);

        //Necessary getter and setters
        int getFirstNom() const;
        int getSecNom() const;
        int getFirstDenom() const;
        int getSecDenom() const;
        double getFirst() const;
        double getSec() const;
        void setFirst(double _first);
        void setSec(double _sec);
        void setBoth(double _first, double _sec);


        //Operator overloads
        const ComplexNumber operator-(const ComplexNumber& other) const;
        const ComplexNumber operator+(const ComplexNumber& other) const;
        bool operator<(const ComplexNumber& other) const;
        friend std::ostream & operator<<(std::ostream & outputStream, const ComplexNumber& our_comp_num);
    protected: // Member data's
        int first_nom;
        int first_denom;
        int sec_nom;
        int sec_denom;

    };
}
#endif	/* COMPLEXNUMBER_H */

