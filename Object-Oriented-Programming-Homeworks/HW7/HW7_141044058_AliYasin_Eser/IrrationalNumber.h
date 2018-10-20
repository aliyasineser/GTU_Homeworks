/* 
 * File:   IrrationalNumber.h
 * Author: aliyasineser
 *
 * Created on December 17, 2015, 1:16 AM
 */

#ifndef IRRATIONALNUMBER_H
#define	IRRATIONALNUMBER_H

#include "RealNumber.h"

/*Irrasyonel class'i hiyerarsi itibariyle dogru fakat yapi itibariyle yanlistir.
 * Bilgisayar ortaminda sonsuz sayi tutma olanagi yok denebilir.
 * Eger bu gercegi gozardi etseydim, virgulden sonra 20 haneyi kontrol edip durumuna gore sonsuza gidip gitmeyecegini ele alirdim.
 * Bu duruma gore de real numbers class'ina benzer bir yapiya modifikasyon yapardim.
 */


namespace GTU_YASIN_NUMBERS {

    class IrrationalNumber : public RealNumber {
    public:
        //Constructors
        IrrationalNumber();
        IrrationalNumber(double _real);
        IrrationalNumber(const IrrationalNumber& orig);
        IrrationalNumber(double _real, double _junk); // copy constructor

        //Operator overloads
        const IrrationalNumber operator+(const IrrationalNumber& other) const;
        const IrrationalNumber operator-(const IrrationalNumber& other) const;
        bool operator<(const IrrationalNumber& other) const;
        friend std::ostream & operator<<(std::ostream & outputStream, const IrrationalNumber& our_irrat_num);

        
        //Helper Functions and get/set redefine
        double getFirst() const;
        double getSec() const;
        void setBoth(double _first, double _sec);
    };
}

#endif	/* IRRATIONALNUMBER_H */

