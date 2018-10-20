/* 
 * File:   Integer.h
 * Author: aliyasineser
 *
 * Created on December 16, 2015, 6:50 PM
 */

#ifndef INTEGER_H
#define	INTEGER_H

#include "ComplexNumber.h"
#include "RealNumber.h"



namespace GTU_YASIN_NUMBERS {

    class Integer : public RealNumber {
    public:
        //Constructors
        Integer();
        Integer(int _num);
        Integer(const Integer& orig); // copy constructor
        Integer(int _num, int _junk);


        //Operator overloads
        const Integer operator+(const Integer& other) const;
        const Integer operator-(const Integer& other) const;
        bool operator<(const Integer& other) const;
        friend std::ostream & operator<<(std::ostream & outputStream, const Integer& our_int_num);


        // getters, setters , redefine
        void setFirst(int _first);
        void setSec(int _sec);
        int getFirst() const;
        void setBoth(int _first, int _sec);

    };
}
#endif	/* INTEGER_H */

