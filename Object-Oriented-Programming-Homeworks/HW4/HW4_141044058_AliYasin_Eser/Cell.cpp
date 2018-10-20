/* 
 * File:   Cell.cpp
 * Author: aliyasineser
 * Cell classi icin implementation dosyasi
 * Created on November 8, 2015, 12:08 PM
 */

#include "Cell.h"
#include <cstring>
#include <cctype>
#include <cmath>

using namespace std;

const int ZERO = 0;
const char* INITIAL_STR_POS = "a";
const char EMPTY_MARK = '.';
const char USER_MARK = 'O';
const char COMP_MARK = 'X';
const int DIFF_BETWEEN_Z_AND_A = 26;

int Cell::livingCells = ZERO;

Cell::Cell() {
    set_x(ZERO);
    set_y(INITIAL_STR_POS);
    set_owner(EMPTY_MARK);
    ++livingCells;
}

Cell::Cell(int _x, std::string _y) {
    set_x(_x);
    set_y(_y);
    set_owner(EMPTY_MARK);
    ++livingCells;
}

Cell::Cell(int _x, std::string _y, char _owner) {
    set_x(_x);
    set_y(_y);
    set_owner(_owner);
    ++livingCells;
}

void Cell::set_x(const int _x) {
    if (_x > ZERO)
        x = _x;



}

void Cell::set_y(std::string _y) {
    int size = _y.size();
    bool flag = true;

    for (int i = 0; i < size; ++i) {
        if (!isalpha(_y[i]))
            flag = false;
    }

    if (flag)
        y = _y;


}

void Cell::set_owner(const char _owner) {
    if (_owner == EMPTY_MARK || _owner == COMP_MARK || _owner == USER_MARK)
        owner = _owner;

}

const int Cell::get_y_as_integer() const {
    int num = 0;

    for (int i = y.size() - 1; i >= 0; --i) {
        num += static_cast<int>(y[i] - 'A')+(DIFF_BETWEEN_Z_AND_A * i);

    }

    

    return num;
}

const std::string Cell::get_y_as_string(const int _y) {
    string str = "";
    int loop_limit = static_cast<int> (_y / DIFF_BETWEEN_Z_AND_A);
    int last_char_mode = _y % DIFF_BETWEEN_Z_AND_A;

    for (int i = 0; i < loop_limit; ++i) {
        str += "A";
    }

    str += static_cast<char> (static_cast<int> ('A') + last_char_mode);

    return str;
}

