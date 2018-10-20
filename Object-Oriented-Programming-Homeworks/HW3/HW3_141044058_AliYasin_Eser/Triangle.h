/* 
 * File:   Triangle.h
 * Author: aliyasineser
 * Triangle class'inin prototip ve tanimlamasini barindiran header dosyasidir
 *
 * Created on 21 Ekim 2015 Çarşamba, 00:50
 */

#ifndef TRIANGLE_H
#define	TRIANGLE_H

/*Ucgen'in sahip olabilecegi onemli bilgileri ve fonksiyonlari barindiran class
 * Fonksiyon ile ilgili bilgiler implementation dosyasindadir*/
class Triangle {
public:
    /*Hic bir deger verilmediginde her kenara 1.00 atar ve hesaplamalari yapar, checking gerekmez*/
    Triangle();

    /*Verilen bir degeri tum kenarlara atar, checking ve hesaplamalari yapar*/
    Triangle(double sides);

    /*İki arguman alir, birini A digerini B kenarina atar ve cheking yapar. Valid ise hesaplamalari yapar*/
    Triangle(double side_of_A, double side_of_B);

    /*Uc kenari da alir, atama, checking ve valid durumda hesaplamalari yapar*/
    Triangle(double side_of_A, double side_of_B, double side_of_C);

    /*Ucgenin memberlarini kullanicidan alip doldurur*/
    void input();

    /*Ucgenin sahip oldugu member'lari uygun bir formatta ekrana basar*/
    void output() const;

    /*Ucgenin A kenarina aldigi degeri atar, validate check yapar*/
    void setSideA(double side_A_param);

    /*Ucgenin B kenarina aldigi degeri atar, validate check yapar*/
    void setSideB(double side_B_param);

    /*Ucgenin C kenarina aldigi degeri atar, validate check yapar*/
    void setSideC(double side_C_param);

    /*Ucgenin A kenarini return eder*/
    double getSideA() const;

    /*Ucgenin B kenarini return eder*/
    double getSideB() const;

    /*Ucgenin C kenarini return eder*/
    double getSideC() const;

    /*Ucgenin B ve C kenarinlari arasindaki aciyi return eder*/
    double getAngleA() const;

    /*Ucgenin A ve C kenarinlari arasindaki aciyi return eder*/
    double getAngleB() const;

    /*Ucgenin A ve B kenarinlari arasindaki aciyi return eder*/
    double getAngleC() const;

    /*Ucgenin alanini return eder*/
    double getArea() const;

    /*Ucgenin cevresini return eder*/
    double getPerimeter() const;

    /*Ucgenin dik olup olmadigini return eder*/
    bool getIsRightAngleTriangle() const;


private:
    /*Ucgenin B ve C kenarinlari arasindaki aciyi hesaplar*/
    void calculateAngleA();

    /*Ucgenin A ve C kenarinlari arasindaki aciyi hesaplar*/
    void calculateAngleB();

    /*Ucgenin A ve B kenarinlari arasindaki aciyi hesaplar*/
    void calculateAngleC();

    /*Ucgenin alanini kenarlari kullanarak hesaplar*/
    void calculateArea();

    /*Ucgenin cevresini kenarlari kullanarak hesaplar*/
    void calculatePerimeter();

    /*Ucgenin dik olup olmadigini kenarlari kullanarak hesaplar*/
    void rightAngleTriangle();


    double side_A; // A kenari
    double side_B; // B kenari
    double side_C; // C kenari
    double angleA; // A acisi
    double angleB; // B acisi
    double angleC; // C acisi
    double area; // Alan
    double perimeter; // Cevre
    bool isRightAngleTriangle; // Ucgenin dik olup olmamasi

};

#endif	/* TRIANGLE_H */




