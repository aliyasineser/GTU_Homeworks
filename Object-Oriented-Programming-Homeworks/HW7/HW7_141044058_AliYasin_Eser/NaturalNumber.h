/* File:   NaturalNumber.h
 * Author: aliyasineser
 *
 * Created on December 16, 2015, 3:59 PM
 */

#ifndef NATURALNUMBER_H
#define	NATURALNUMBER_H

#include "Integer.h"




namespace GTU_YASIN_NUMBERS {

    class NaturalNumber : public Integer {
    public:
        //Constructors
        NaturalNumber();
        NaturalNumber(int _num);
        NaturalNumber(const NaturalNumber& orig);// copy constructor
        NaturalNumber(int _num, int _junk);

        //Operator Overloads
        const NaturalNumber operator+(const NaturalNumber& other) const;
        const Integer operator-(const NaturalNumber& other) const;
        bool operator<(const NaturalNumber& other) const;
        friend std::ostream & operator<<(std::ostream & outputStream, const NaturalNumber& our_nat_num);

        //getters, setters, redefine
        void setFirst(int _first);
        int getFirst() const;

    };
}
#endif	/* NATURALNUMBER_H */

