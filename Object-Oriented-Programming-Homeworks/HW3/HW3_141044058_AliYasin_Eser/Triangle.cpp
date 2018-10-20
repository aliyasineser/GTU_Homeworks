/* 
 * File:   Triangle.cpp
 * Author: aliyasineser
 * Triangle class'inin fonksiyon implementasyonlarini barindan dosyadir
 * 
 * Created on 21 Ekim 2015 Çarşamba, 00:50
 */

#include "Triangle.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

const double PI = 3.14159265; // Approximate value of Pi
const double sideInitialValue = 1.00; // Constructer default value of sides
const int ZERO = 0; // Zero that we know
const int TAKE_SQUARE = 2; // 2 that we use for taking square, in pow func
const int TAKE_DOUBLE = 2; // 2 that we use for doubling a number
const int TAKE_HALF = 2; // 2 that we use for halfing a number
const int DEGREE_OF_HALF_CIRCLE = 180; // Degree of a half circle

/*Hic bir deger verilmediginde her kenara 1.00 atar ve hesaplamalari yapar, checking gerekmez*/
Triangle::Triangle() {
    setSideA(sideInitialValue);
    setSideB(sideInitialValue);
    setSideC(sideInitialValue);

    calculateAngleA();
    calculateAngleB();
    calculateAngleC();

    calculateArea();
    calculatePerimeter();
    rightAngleTriangle();
}

/*Verilen bir degeri tum kenarlara atar, checking ve hesaplamalari yapar*/
Triangle::Triangle(double sides) {
    setSideA(sides);
    setSideB(sides);
    setSideC(sides);

    if ((fabs(side_A - side_B) > side_C) || (side_C > side_A + side_B) ||
            (fabs(side_A - side_C) > side_B) || (side_B > side_A + side_C) ||
            (fabs(side_C - side_B) > side_A) || (side_A > side_C + side_B)) {
        cerr << "Choose your lengths wisely, |a-b| < c < a+b " << endl;
        exit(1);
    }

    calculateAngleA();
    calculateAngleB();
    calculateAngleC();

    calculateArea();
    calculatePerimeter();
    rightAngleTriangle();

}

/*İki arguman alir, birini A digerini B kenarina atar ve cheking yapar. Valid ise hesaplamalari yapar*/
Triangle::Triangle(double side_of_A, double side_of_B) {
    setSideA(side_of_A);
    setSideB(side_of_B);
    setSideC(sideInitialValue);

    if ((fabs(side_A - side_B) > side_C) || (side_C > side_A + side_B) ||
            (fabs(side_A - side_C) > side_B) || (side_B > side_A + side_C) ||
            (fabs(side_C - side_B) > side_A) || (side_A > side_C + side_B)) {
        cerr << "Choose your lengths wisely, |a-b| < c < a+b " << endl;
        exit(1);
    }

    calculateAngleA();
    calculateAngleB();
    calculateAngleC();

    calculateArea();
    calculatePerimeter();
    rightAngleTriangle();


}

/*Uc kenari da alir, atama, checking ve valid durumda hesaplamalari yapar*/
Triangle::Triangle(double side_of_A, double side_of_B, double side_of_C) {
    setSideA(side_of_A);
    setSideB(side_of_B);
    setSideC(side_of_C);

    if ((fabs(side_A - side_B) > side_C) || (side_C > side_A + side_B) ||
            (fabs(side_A - side_C) > side_B) || (side_B > side_A + side_C) ||
            (fabs(side_C - side_B) > side_A) || (side_A > side_C + side_B)) {
        cerr << "Choose your lengths wisely, |a-b| < c < a+b " << endl;
        exit(1);
    }

    calculateAngleA();
    calculateAngleB();
    calculateAngleC();

    calculateArea();
    calculatePerimeter();
    rightAngleTriangle();

}

/*Ucgenin A kenarini return eder*/
double Triangle::getSideA() const {
    return side_A;
}

/*Ucgenin B kenarini return eder*/
double Triangle::getSideB() const {
    return side_B;
}

/*Ucgenin C kenarini return eder*/
double Triangle::getSideC() const {
    return side_C;
}

/*Ucgenin A kenarina aldigi degeri atar, validate check yapar*/
void Triangle::setSideA(double side_A_param) {
    if (side_A_param < ZERO) {
        cerr << "Any side of a triangle cannot be smaller than zero" << endl;
        exit(1);
    }
    side_A = side_A_param;
}

/*Ucgenin B kenarina aldigi degeri atar, validate check yapar*/
void Triangle::setSideB(double side_B_param) {
    if (side_B_param < ZERO) {
        cerr << "Any side of a triangle cannot be smaller than zero" << endl;
        exit(1);
    }
    side_B = side_B_param;
}

/*Ucgenin C kenarina aldigi degeri atar, validate check yapar*/
void Triangle::setSideC(double side_C_param) {
    if (side_C_param < ZERO) {
        cerr << "Any side of a triangle cannot be smaller than zero" << endl;
        exit(1);
    }
    side_C = side_C_param;
}

/*Ucgenin B ve C kenarinlari arasindaki aciyi return eder*/
double Triangle::getAngleA() const {
    return angleA;
}

/*Ucgenin A ve C kenarinlari arasindaki aciyi return eder*/
double Triangle::getAngleB() const {
    return angleB;
}

/*Ucgenin A ve B kenarinlari arasindaki aciyi return eder*/
double Triangle::getAngleC() const {
    return angleC;
}

/*Ucgenin B ve C kenarinlari arasindaki aciyi hesaplar*/
void Triangle::calculateAngleA() {
    angleA = acos(-((pow(side_A, TAKE_SQUARE) - pow(side_B, TAKE_SQUARE) - pow(side_C, TAKE_SQUARE)) / (TAKE_DOUBLE * side_B * side_C))) * DEGREE_OF_HALF_CIRCLE / PI;

}

/*Ucgenin A ve C kenarinlari arasindaki aciyi hesaplar*/
void Triangle::calculateAngleB() {
    angleB = acos(-((pow(side_B, TAKE_SQUARE) - pow(side_A, TAKE_SQUARE) - pow(side_C, TAKE_SQUARE)) / (TAKE_DOUBLE * side_A * side_C))) * DEGREE_OF_HALF_CIRCLE / PI;

}

/*Ucgenin A ve B kenarinlari arasindaki aciyi hesaplar*/
void Triangle::calculateAngleC() {
    angleC = acos(-((pow(side_C, TAKE_SQUARE) - pow(side_A, TAKE_SQUARE) - pow(side_B, TAKE_SQUARE)) / (TAKE_DOUBLE * side_B * side_A))) * DEGREE_OF_HALF_CIRCLE / PI;

}

/*Ucgenin alanini kenarlari kullanarak hesaplar*/
void Triangle::calculateArea() {
    int u = ((side_A + side_B + side_C) / TAKE_HALF);
    area = sqrt(u * (u - side_A)*(u - side_B)*(u - side_C));
}

/*Ucgenin cevresini kenarlari kullanarak hesaplar*/
void Triangle::calculatePerimeter() {
    perimeter = side_A + side_B + side_C;
}

/*Ucgenin dik olup olmadigini kenarlari kullanarak hesaplar*/
void Triangle::rightAngleTriangle() {
    isRightAngleTriangle = ((pow(side_A, TAKE_SQUARE) + pow(side_B, TAKE_SQUARE) == pow(side_C, TAKE_SQUARE)) ||
            (pow(side_A, TAKE_SQUARE) + pow(side_C, TAKE_SQUARE) == pow(side_B, TAKE_SQUARE)) ||
            (pow(side_C, TAKE_SQUARE) + pow(side_B, TAKE_SQUARE) == pow(side_A, TAKE_SQUARE)));
}

/*Ucgenin alanini return eder*/
double Triangle::getArea() const {
    return area;
}

/*Ucgenin cevresini return eder*/
double Triangle::getPerimeter() const {
    return perimeter;
}

/*Ucgenin dik olup olmadigini return eder*/
bool Triangle::getIsRightAngleTriangle() const {
    return isRightAngleTriangle;
}

/*Ucgenin sahip oldugu member'lari uygun bir formatta ekrana basar*/
void Triangle::output() const {
    cout << "Sides of Triangle: " << endl;
    cout << "First side(A): " << getSideA() << endl;
    cout << "Second side(B): " << getSideB() << endl;
    cout << "Third side(C): " << getSideC() << endl << endl;

    cout << "Angles of Triangle: " << endl;
    cout << "First angle(Between B and C): " << getAngleA() << endl;
    cout << "Second angle(Between A and C): " << getAngleB() << endl;
    cout << "Third angle(Between A and B): " << getAngleC() << endl << endl;

    cout << "Area of the triangle is: " << getArea() << endl;
    cout << "Perimeter of the triangle is: " << getPerimeter() << endl;
    if (getIsRightAngleTriangle())
        cout << "It's a right angle triangle" << endl;
    else
        cout << "It's not a right angle triangle" << endl;
    cout << endl << endl;

}

/*Ucgenin memberlarini kullanicidan alip doldurur*/
void Triangle::input() {
    cout << "Please Enter the first side of Triangle(A)" << endl;
    cin >> side_A;
    cout << "Please Enter the second side of Triangle(B)" << endl;
    cin >> side_B;
    cout << "Please Enter the third side of Triangle(C)" << endl;
    cin >> side_C;

    if ((fabs(side_A - side_B) > side_C) || (side_C > side_A + side_B) ||
            (fabs(side_A - side_C) > side_B) || (side_B > side_A + side_C) ||
            (fabs(side_C - side_B) > side_A) || (side_A > side_C + side_B)) {
        cerr << "Choose your lengths wisely, |a-b| < c < a+b " << endl;
        exit(1);
    }

    calculateAngleA();
    calculateAngleB();
    calculateAngleC();

    calculateArea();
    calculatePerimeter();
    rightAngleTriangle();
}