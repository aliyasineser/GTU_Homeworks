/* 
 * File:   HW3_141044058_AliYasin_Eser.cpp
 * Author: aliyasineser
 * Triangle class'i icin iki ozel fonksiyon ve bir adet test iceren test dosyasidir
 *
 * Created on 19 Ekim 2015 Pazartesi, 23:39
 */

#include <cstdlib>
#include <cmath>
#include <iostream>
#include "Triangle.h"

using namespace std;

/* Call by reference ile alinmis iki Triangle objeyi swaplar */
void swap_triangles(Triangle &tri_obj1, Triangle &tri_obj2);

/*Call by value ile alinmis Triangle objenin eskenar ucgen olup olmadigini kontrol eder
 *Sonucu ekrana yazar ve return degeri yoktur
 */
void is_equilateral_triangle(Triangle the_triangle);

int main(int argc, char** argv) {
    Triangle tri_obj(8), tri_obje(9, 40, 41);

    cout << "Triangle No:1 " << endl;
    tri_obj.output();
    cout << "Triangle No:2 " << endl;
    tri_obje.output();

    swap_triangles(tri_obj, tri_obje);

    cout << "After swap:" << endl << endl;

    cout << "Triangle No:1 " << endl;
    tri_obj.output();
    cout << "Triangle No:2 " << endl;
    tri_obje.output();

    cout << "Is No:1 Triangle equilateral triangle? " << endl;
    is_equilateral_triangle(tri_obj);
    cout << "Is No:2 Triangle equilateral triangle? " << endl;
    is_equilateral_triangle(tri_obje);

    return 0;
}

/* Call by reference ile alinmis iki Triangle objeyi swaplar */
void swap_triangles(Triangle &tri_obj1, Triangle &tri_obj2) {
    Triangle temp_triangle;

    temp_triangle = tri_obj1;
    tri_obj1 = tri_obj2;
    tri_obj2 = temp_triangle;

}

/*Call by value ile alinmis Triangle objenin eskenar ucgen olup olmadigini kontrol eder
 *Sonucu ekrana yazar ve return degeri yoktur
 */
void is_equilateral_triangle(Triangle the_triangle) {
    if (the_triangle.getSideA() == the_triangle.getSideB() &&
            the_triangle.getSideB() == the_triangle.getSideC() &&
            the_triangle.getSideA() == the_triangle.getSideC())
        cout << "Triangle is equilateral triangle" << endl;
    else
        cout << "Triangle is not eqilateral triangle" << endl;


}