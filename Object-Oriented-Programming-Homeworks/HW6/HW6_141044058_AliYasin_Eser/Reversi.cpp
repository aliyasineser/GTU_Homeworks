/* 
 * File:   Reversi.cpp
 * Author: aliyasineser
 *  Reversi classi icin implementation dosyasi
 * Created on December 10, 2015, 3:41 PM
 */

#include "Reversi.h"
#include <cmath>
#include <cstring>
#include <iostream>
#include <cctype>
#include <vector>
#include <cstdlib>
#include <fstream>

using namespace std;
namespace GTU_YASIN_REVERSI {

    const int MIN_SIZE = 4; // Table min size
    const int MAX_SIZE = 20; // Table max size
    const int NOT_LEGAL_MOVE = 0; // Legal olmayan hamle icin flag const
    const int LEGAL_MOVE = 1; // Legal hamle icin flag const
    const int IS_DOUBLE_CHECK = 2; // 2 ile mod almak icin const
    const int START_POINT = 0; // Array'lerin baslangic indisi icin const
    const int IS_MIDDLE_CHECK = 2; // Array'in initialize olmasi icin
    const int DELTA_ONE = 1; // Array'de birer birer ilerlemek icin const
    const int FIX_TABLE_SHIFT = 10; // Cift haneli sayilarda tablonun kaymamasi icin eklenmis kod icin
    const int ERROR = 1; // Error flag
    const int NO_ERROR = 0; // Error flag
    const int ARRAY_FIX = 1; // Kullanicinin girdigi degeri duzenlemek icin
    const int BOTH_CANNOT_MOVE = 2; // Hem user hem computer hamle yapamazsa oyun biter
    const int ZERO = 0; // Sifir degeri
    const int STR_LENGTH = 80; // ongorulmus line uzunlugu
    const char EMPTY_MARK = '.';
    const char USER_MARK = 'O';
    const char COMP_MARK = 'X';
    const int INITIAL_TABLE_SIZE = 10;
    const int ONE = 1;
    const int DIFF_BETWEEN_Z_AND_A = 26;
    const int FIVE = 5;
    const int DECIMAL_CALC = 10;
    const int HALF = 2;
    const int ADD_TWO_FOR_INITIAL = 2;
    const int ADD_FOUR_FOR_INITIAL = 4;
    const int ADD_THREE_FOR_INITIAL = 3;

    Reversi::Reversi() : arr_size(ZERO) {
        set_Both(INITIAL_TABLE_SIZE, INITIAL_TABLE_SIZE);
        gameCells = new Cell[size_x * size_y];
        arr_cap = size_x * size_y;
    }

    Reversi::Reversi(int _size_x) : arr_size(ZERO) {

        set_Both(_size_x, INITIAL_TABLE_SIZE);
        gameCells = new Cell[size_x * size_y];
        arr_cap = size_x * size_y;
    }

    Reversi::Reversi(int _size_x, int _size_y) : arr_size(ZERO) {


        set_Both(_size_x, _size_y);
        gameCells = new Cell[size_x * size_y];
        arr_cap = size_x * size_y;
    }

    void Reversi::set_Height(int _size_x) {

        size_x = _size_x;

    }

    void Reversi::set_Width(int _size_y) {

        size_y = _size_y;



    }

    void Reversi::set_Both(int _size_x, int _size_y) {

        size_x = _size_x;
        size_y = _size_y;
    }

    int Reversi::rec_decimal_count(int num) {
        int counter = ZERO;

        if (num / DECIMAL_CALC < ONE)
            counter = ONE;
        else
            counter = ONE + rec_decimal_count(num / DECIMAL_CALC);

        return counter;
    }





    //oyun tahtasini basar

    void Reversi::print_game_board() const {
        //satirlar icin bosluk hesabi
        int space_limit = Reversi::rec_decimal_count(getHeight());

        for (int i = ZERO; i < space_limit + ONE; i++) {
            cout << " ";

        }
        //sutunlarin basilmasi
        for (int letter_count = START_POINT; letter_count < getWidth(); letter_count++) {
            cout << Cell::get_y_as_string(letter_count) << " ";

        }
        cout << endl;
        //elemanlarin basilmasi
        for (int i = START_POINT; i < getHeight(); ++i) {
            // satir numaralari
            cout << i + DELTA_ONE;
            for (int m = START_POINT; m < space_limit - rec_decimal_count(i + DELTA_ONE) + ONE; m++) {
                cout << " ";
            }
            //elemanlarin basilmasi, eleman yoksa nokta basilir
            for (int j = START_POINT; j < getWidth(); ++j) {
                cout << return_the_ch(i, j);

                for (int i = ZERO; i < static_cast<int> (j / DIFF_BETWEEN_Z_AND_A) + ONE; i++) {
                    cout << " ";

                }

            }
            cout << endl;
        }

    }
    //bool table olusturur, eger eleman eklenebilirse 1 degilse 0 dondurur

    bool Reversi::createLegalTable(char my_turn, char look_for) {

        // bool table olusturulmasi
        bool_game_board.resize(getHeight());

        for (int i = ZERO; i < getHeight(); ++i) {
            bool_game_board[i].resize(getWidth());

        }

        //eleman konabilecek yerler (bos yerler) 1, gerisi 0
        for (int i = START_POINT; i < getHeight(); i++) {
            for (int j = START_POINT; j < getWidth(); j++) {
                if (return_the_ch(i, j) == EMPTY_MARK) {
                    bool_game_board[i][j] = true;
                } else {
                    bool_game_board[i][j] = false;
                }
            }
        }
        int dif_one = 1, is_the_one = NOT_LEGAL_MOVE;
        // bool table duzenlenmesi legal hamleler 1 olmayanlar 0
        for (int i = START_POINT; i < getHeight(); i++) {
            for (int j = START_POINT; j < getWidth(); j++) {
                is_the_one = vertical_check(i, j, is_the_one, my_turn, look_for);
                is_the_one = horizontal_check(i, j, is_the_one, my_turn, look_for);
                is_the_one = diagonal_check(i, j, is_the_one, my_turn, look_for);

                if (bool_game_board[i][j] == true) {
                    if (is_the_one == NOT_LEGAL_MOVE) {
                        bool_game_board[i][j] = false;
                    }
                }
                is_the_one = NOT_LEGAL_MOVE;
            }
        }


        // oynanacak hamle varsa count 1 olur ve dondurulur, diger durumda oynanacak tas yoktur
        int at_least_one_legal = NOT_LEGAL_MOVE;
        for (int i = START_POINT; i < getHeight(); i++) {
            for (int j = START_POINT; j < getWidth(); j++) {
                if (at_least_one_legal == NOT_LEGAL_MOVE)
                    if (bool_game_board[i][j] == true)
                        at_least_one_legal++;
            }
        }

        return at_least_one_legal;

    }


    // Dikey duzlemde hamle yapilacak yerleri kontrol eder

    bool Reversi::vertical_check(int x_axis, int y_axis, int is_the_one, char my_turn, char look_for) const {
        int row_temp, col_temp, count_last, dif_one = 1;

        /*From bottom to top*/
        if (is_the_one == NOT_LEGAL_MOVE) {
            if (x_axis - dif_one >= START_POINT && x_axis - dif_one < getHeight()) {
                row_temp = x_axis - dif_one;

                if (return_the_ch(row_temp, y_axis) == look_for) {
                    for (count_last = ONE; row_temp - count_last >= START_POINT;
                            count_last++) {
                        if (return_the_ch(row_temp - count_last, y_axis) == EMPTY_MARK)
                            break;
                        if (return_the_ch(row_temp - count_last, y_axis) == my_turn) {
                            is_the_one = LEGAL_MOVE;
                        }
                    }
                }
            }
        }


        /*From top to bottom*/
        if (is_the_one == NOT_LEGAL_MOVE) {
            row_temp = x_axis + dif_one;
            if (row_temp >= START_POINT && row_temp < getHeight()) {
                if (return_the_ch(row_temp, y_axis) == look_for) {
                    for (row_temp += dif_one; row_temp < getHeight();
                            row_temp += dif_one) {
                        if (return_the_ch(row_temp, y_axis) == EMPTY_MARK)
                            break;
                        if (return_the_ch(row_temp, y_axis) == my_turn) {
                            is_the_one = LEGAL_MOVE;
                        }
                    }
                }
            }
        }




        return is_the_one;

    }


    // Yatay duzlemde hamle yapilacak yerleri kontrol eder

    bool Reversi::horizontal_check(int x_axis, int y_axis, int is_the_one, char my_turn, char look_for) const {
        int row_temp, col_temp, count_last, dif_one = 1, i;



        /*From left to right*/
        if (is_the_one == NOT_LEGAL_MOVE) {
            if (y_axis + dif_one >= START_POINT && y_axis + dif_one < getWidth()) {
                col_temp = y_axis + dif_one;
                if (return_the_ch(x_axis, col_temp) == look_for) {
                    for (count_last = ONE; col_temp + count_last < getWidth();
                            count_last++) {
                        if (return_the_ch(x_axis, col_temp + count_last) == EMPTY_MARK)
                            break;
                        if (return_the_ch(x_axis, col_temp + count_last) == my_turn) {
                            is_the_one = LEGAL_MOVE;
                        }
                    }
                }
            }
        }


        /*From right to left*/
        if (is_the_one == NOT_LEGAL_MOVE) {
            if (y_axis - dif_one >= START_POINT && y_axis - dif_one < getWidth()) {
                col_temp = y_axis - dif_one;
                if (return_the_ch(x_axis, col_temp) == look_for) {
                    for (count_last = ONE; col_temp - count_last >= START_POINT;
                            count_last++) {
                        if (return_the_ch(x_axis, col_temp - count_last) == EMPTY_MARK)
                            break;
                        if (return_the_ch(x_axis, col_temp - count_last) == my_turn) {
                            is_the_one = LEGAL_MOVE;
                        }
                    }
                }
            }
        }



        return is_the_one;
    }



    // Diagonal duzlemde hamle yapilacak yerleri kontrol eder

    bool Reversi::diagonal_check(int x_axis, int y_axis, int is_the_one, char my_turn, char look_for) const {
        int row_temp, col_temp, count_last, dif_one = ONE;

        /*From right-down to left-up*/
        if (is_the_one == NOT_LEGAL_MOVE) {
            if (x_axis - dif_one >= START_POINT && x_axis - dif_one < getHeight() &&
                    y_axis - dif_one >= START_POINT && y_axis - dif_one < getWidth()) {
                row_temp = x_axis - dif_one;
                col_temp = y_axis - dif_one;
                if (return_the_ch(row_temp, col_temp) == look_for) {
                    for (count_last = ONE; row_temp - count_last >= START_POINT &&
                            col_temp - count_last >= START_POINT;
                            count_last++) {
                        if (return_the_ch(row_temp - count_last, col_temp - count_last) == EMPTY_MARK)
                            break;
                        if (return_the_ch(row_temp - count_last, col_temp - count_last) == my_turn) {
                            is_the_one = LEGAL_MOVE;
                        }
                    }
                }
            }
        }


        /*From left-down to right-up*/
        if (is_the_one == NOT_LEGAL_MOVE) {
            if (x_axis - dif_one >= START_POINT && x_axis - dif_one < getHeight() &&
                    y_axis + dif_one >= START_POINT && y_axis + dif_one < getWidth()) {
                row_temp = x_axis - dif_one;
                col_temp = y_axis + dif_one;
                if (return_the_ch(row_temp, col_temp) == look_for) {
                    for (count_last = ONE; row_temp - count_last >= START_POINT &&
                            col_temp + count_last < getWidth();
                            count_last++) {
                        if (return_the_ch(row_temp - count_last, col_temp + count_last) == EMPTY_MARK)
                            break;
                        if (return_the_ch(row_temp - count_last, col_temp + count_last) == my_turn) {
                            is_the_one = LEGAL_MOVE;
                        }
                    }
                }
            }
        }

        /*From right-up to left-down*/
        if (is_the_one == NOT_LEGAL_MOVE) {
            if (x_axis + dif_one >= START_POINT && x_axis + dif_one < getHeight() &&
                    y_axis - dif_one >= START_POINT && y_axis - dif_one < getWidth()) {
                row_temp = x_axis + dif_one;
                col_temp = y_axis - dif_one;
                if (return_the_ch(row_temp, col_temp) == look_for) {
                    for (count_last = ONE; row_temp + count_last < getHeight() && col_temp - count_last >= START_POINT;
                            count_last++) {
                        if (return_the_ch(row_temp + count_last, col_temp - count_last) == EMPTY_MARK)
                            break;
                        if (return_the_ch(row_temp + count_last, col_temp - count_last) == my_turn) {
                            is_the_one = LEGAL_MOVE;
                        }
                    }
                }
            }
        }


        /*From left-up to right-down*/
        if (is_the_one == NOT_LEGAL_MOVE) {
            if (x_axis + dif_one >= START_POINT && x_axis + dif_one < getHeight() &&
                    y_axis + dif_one >= START_POINT && y_axis + dif_one < getWidth()) {
                row_temp = x_axis + dif_one;
                col_temp = y_axis + dif_one;
                if (return_the_ch(row_temp, col_temp) == look_for) {
                    for (count_last = ONE; row_temp + count_last < getHeight() &&
                            col_temp + count_last < getWidth();
                            count_last++) {
                        if (return_the_ch(row_temp + count_last, col_temp + count_last) == EMPTY_MARK)
                            break;
                        if (return_the_ch(row_temp + count_last, col_temp + count_last) == my_turn) {
                            is_the_one = LEGAL_MOVE;
                        }
                    }
                }
            }
        }






        return is_the_one;
    }


    // Bilgisayarin maksimum degistirebilecegi tas sayisina gore hamlesini belirler

    move_t Reversi::max_move_of_computer(char player_ch, char target_ch) const {
        int i, j;
        move_t best_move = {.change_count = START_POINT, .coor_x = START_POINT, .coor_y = START_POINT}, temp_move;


        for (i = START_POINT; i < getHeight(); i++) {
            for (j = START_POINT; j < getWidth(); j++) {
                if (bool_game_board[i][j] == true) {
                    temp_move.change_count = START_POINT;
                    temp_move.coor_x = i;
                    temp_move.coor_y = j;

                    temp_move.change_count += horizontal_count(player_ch, target_ch, i, j, temp_move.change_count);
                    temp_move.change_count += vertical_count(player_ch, target_ch, i, j, temp_move.change_count);
                    temp_move.change_count += diagonal_count(player_ch, target_ch, i, j, temp_move.change_count);

                    if (temp_move.change_count > best_move.change_count)
                        best_move = temp_move;
                }
            }
        }
        return best_move;
    }




    // Yatay duzlemde hamleyi gerceklestirir

    void Reversi::horizontal_update(char player_ch, char target_ch, int coor_x, int coor_y) {
        int delta_one = ONE;
        int i = ZERO;
        for (i = coor_x - delta_one; i >= START_POINT && return_the_ch(i, coor_y) == target_ch; i -= (delta_one));

        if (i >= START_POINT && return_the_ch(i, coor_y) == player_ch)
            for (i = coor_x - delta_one; i >= START_POINT && return_the_ch(i, coor_y) == target_ch; i -= (delta_one))
                setTheOwnerOfCell(i, coor_y, player_ch);

        for (i = coor_x + delta_one; i < getHeight() && return_the_ch(i, coor_y) == target_ch; i += (delta_one));

        if (i < getHeight() && return_the_ch(i, coor_y) == player_ch)
            for (i = coor_x + delta_one; i < getHeight() && return_the_ch(i, coor_y) == target_ch; i += (delta_one))
                setTheOwnerOfCell(i, coor_y, player_ch);

    }

    // Dikey duzlemde hamleyi gerceklestirir

    void Reversi::vertical_update(char player_ch, char target_ch, int coor_x, int coor_y) {
        int delta_one = ONE, j;

        for (j = coor_y - delta_one; j >= START_POINT && return_the_ch(coor_x, j) == target_ch; j -= (delta_one));

        if (j >= START_POINT && return_the_ch(coor_x, j) == player_ch)
            for (j = coor_y - delta_one; j >= START_POINT && return_the_ch(coor_x, j) == target_ch; j -= (delta_one))
                setTheOwnerOfCell(coor_x, j, player_ch);

        for (j = coor_y + delta_one; j < getWidth() && return_the_ch(coor_x, j) == target_ch; j += (delta_one));

        if (j < getWidth() && return_the_ch(coor_x, j) == player_ch)
            for (j = coor_y + delta_one; j < getWidth() && return_the_ch(coor_x, j) == target_ch; j += (delta_one))
                setTheOwnerOfCell(coor_x, j, player_ch);

    }




    // Diagonal duzlemde hamleyi gerceklestirir

    void Reversi::diagonal_update(char player_ch, char target_ch, int coor_x, int coor_y) {
        int delta_one = ONE, i, j;


        /* Left and Up */
        for (i = coor_x - delta_one, j = coor_y - delta_one; i >= START_POINT && j >= START_POINT && return_the_ch(i, j) == target_ch; i -= (delta_one), j -= (delta_one));

        if (i >= START_POINT && j >= START_POINT && return_the_ch(i, j) == player_ch)
            for (i = coor_x - delta_one, j = coor_y - delta_one; i >= START_POINT && j >= START_POINT && return_the_ch(i, j) == target_ch; i -= (delta_one), j -= (delta_one))
                setTheOwnerOfCell(i, j, player_ch);

        /*Right and Up*/
        for (i = coor_x - delta_one, j = coor_y + delta_one; i >= START_POINT && j < getWidth() && return_the_ch(i, j) == target_ch; i -= (delta_one), j += (delta_one));

        if (i >= START_POINT && j < getWidth() && return_the_ch(i, j) == player_ch)
            for (i = coor_x - delta_one, j = coor_y + delta_one; i >= START_POINT && j < getWidth() && return_the_ch(i, j) == target_ch; i -= (delta_one), j += (delta_one))
                setTheOwnerOfCell(i, j, player_ch);

        /* Right and Down */
        for (i = coor_x + delta_one, j = coor_y + delta_one; i < getHeight() && j < getWidth() && return_the_ch(i, j) == target_ch; i += (delta_one), j += (delta_one));

        if (i < getHeight() && j < getWidth() && return_the_ch(i, j) == player_ch)
            for (i = coor_x + delta_one, j = coor_y + delta_one; i < getHeight() && j < getWidth() && return_the_ch(i, j) == target_ch; i += (delta_one), j += (delta_one))
                setTheOwnerOfCell(i, j, player_ch);

        /* Left and Down */
        for (i = coor_x + delta_one, j = coor_y - delta_one; i < getHeight() && j >= START_POINT && return_the_ch(i, j) == target_ch; i += (delta_one), j -= (delta_one));

        if (i < getHeight() && j >= START_POINT && return_the_ch(i, j) == player_ch)
            for (i = coor_x + delta_one, j = coor_y - delta_one; i < getHeight() && j >= START_POINT && return_the_ch(i, j) == target_ch; i += (delta_one), j -= (delta_one))
                setTheOwnerOfCell(i, j, player_ch);

    }







    //Yatay duzlemde degistirilecek taslari sayar

    int Reversi::horizontal_count(char player_ch, char target_ch, int coor_x, int coor_y, int stone_count) const {
        int i, j, delta_one = ONE;


        for (i = coor_x - delta_one; i >= START_POINT && return_the_ch(i, coor_y) == target_ch; i -= (delta_one));

        if (i >= START_POINT && return_the_ch(i, coor_y) == player_ch)
            for (i = coor_x - delta_one; i >= START_POINT && return_the_ch(i, coor_y) == target_ch; i -= (delta_one))
                stone_count++;

        for (i = coor_x + delta_one; i < getHeight() && return_the_ch(i, coor_y) == target_ch; i += (delta_one));

        if (i < getHeight() && return_the_ch(i, coor_y) == player_ch)
            for (i = coor_x + delta_one; i < getHeight() && return_the_ch(i, coor_y) == target_ch; i += (delta_one))
                stone_count++;

        return stone_count;
    }





    //Dikey duzlemde degistirilecek taslari sayar

    int Reversi::vertical_count(char player_ch, char target_ch, int coor_x, int coor_y, int stone_count) const {
        int i, j, delta_one = ONE;


        for (j = coor_y - delta_one; j >= START_POINT && return_the_ch(coor_x, j) == target_ch; j -= (delta_one));

        if (j >= START_POINT && return_the_ch(coor_x, j) == player_ch)
            for (j = coor_y - delta_one; j >= START_POINT && return_the_ch(coor_x, j) == target_ch; j -= (delta_one))
                stone_count++;

        for (j = coor_y + delta_one; j < getWidth() && return_the_ch(coor_x, j) == target_ch; j += (delta_one));

        if (j < getWidth() && return_the_ch(coor_x, j) == player_ch)
            for (j = coor_y + delta_one; j < getWidth() && return_the_ch(coor_x, j) == target_ch; j += (delta_one))
                stone_count++;

        return stone_count;
    }


    //Diagonal duzlemde degistirilecek taslari sayar

    int Reversi::diagonal_count(char player_ch, char target_ch, int coor_x, int coor_y, int stone_count) const {
        int i, j, delta_one = ONE;


        /* Left and Up */
        for (i = coor_x - delta_one, j = coor_y - delta_one; i >= START_POINT && j >= START_POINT && return_the_ch(i, j) == target_ch; i -= (delta_one), j -= (delta_one));

        if (i >= START_POINT && j >= START_POINT && return_the_ch(i, j) == player_ch)
            for (i = coor_x - delta_one, j = coor_y - delta_one; i >= START_POINT && j >= START_POINT && return_the_ch(i, j) == target_ch; i -= (delta_one), j -= (delta_one))
                stone_count++;

        /*Right and Up*/
        for (i = coor_x - delta_one, j = coor_y + delta_one; i >= START_POINT && j < getWidth() && return_the_ch(i, j) == target_ch; i -= (delta_one), j += (delta_one));

        if (i >= START_POINT && j < getWidth() && return_the_ch(i, j) == player_ch)
            for (i = coor_x - delta_one, j = coor_y + delta_one; i >= START_POINT && j < getWidth() && return_the_ch(i, j) == target_ch; i -= (delta_one), j += (delta_one))
                stone_count++;

        /* Right and Down */
        for (i = coor_x + delta_one, j = coor_y + delta_one; i < getHeight() && j < getWidth() && return_the_ch(i, j) == target_ch; i += (delta_one), j += (delta_one));

        if (i < getHeight() && j < getWidth() && return_the_ch(i, j) == player_ch)
            for (i = coor_x + delta_one, j = coor_y + delta_one; i < getHeight() && j < getWidth() && return_the_ch(i, j) == target_ch; i += (delta_one), j += (delta_one))
                stone_count++;

        /* Left and Down */
        for (i = coor_x + delta_one, j = coor_y - delta_one; i < getHeight() && j >= START_POINT && return_the_ch(i, j) == target_ch; i += (delta_one), j -= (delta_one));

        if (i < getHeight() && j >= START_POINT && return_the_ch(i, j) == player_ch)
            for (i = coor_x + delta_one, j = coor_y - delta_one; i < getHeight() && j >= START_POINT && return_the_ch(i, j) == target_ch; i += (delta_one), j -= (delta_one))
                stone_count++;
    }
    // bilgisayar icin oyun oynayan fonksiyon

    bool Reversi::play() {

        // legal tablo olusturulur ve en iyi hamle belirlenir
        bool res = createLegalTable(COMP_MARK, USER_MARK);
        move_t best_move = max_move_of_computer(COMP_MARK, USER_MARK);
        // en iyi hamle eger bulunduysa oynanir
        if (best_move.change_count != START_POINT) {
            update_table(COMP_MARK, USER_MARK, best_move.coor_x, best_move.coor_y);
            cout << "The board after computer's move" << endl;
            print_game_board();
            cout << endl << endl;
            return true;
        } else {
            cout << "No legal move for computer" << endl;
            return false;
        }

        return res;
    }

    bool Reversi::play(int _x, int _y) {

        bool res = createLegalTable(USER_MARK, COMP_MARK);
        if (bool_game_board[_x][_y])
            update_table(USER_MARK, COMP_MARK, _x, _y);

        cout << "The board after user's move" << endl;
        print_game_board();
        cout << endl << endl;

        return res;
    }

    void Reversi::take_input(int &row_coor, string &col_coor) {
        int error_flag, alpha_flag, range_flag;
        string thrash, i;

        // input temizleme
        cin.clear();
        cin.ignore(STR_LENGTH, '\n');

        do {
            error_flag = NO_ERROR;
            cout << "Please enter row number that you want to move: ";
            cin >> row_coor;
            if (row_coor > getHeight() || cin.fail()) {
                cout << "Wrong row number or format, check again!" << endl;
                //sonraki alim icin input etmizleme
                cin.clear();
                cin.ignore(STR_LENGTH, '\n');
                error_flag = ERROR;
            }
        } while (error_flag == ERROR);
        row_coor -= ARRAY_FIX; // Array'ler sifirdan baslar, kullaniciya zorluk cikarmamak adina eklendi





        string temp_letter;

        // string oncesi inpıut temizleme
        cin.clear();
        cin.ignore(STR_LENGTH, '\n');

        if (row_coor >= ZERO) { // menuye donmek icin , negatif deger girildiginde string almamasi icin
            do {

                range_flag = NO_ERROR;
                error_flag = NO_ERROR;
                alpha_flag = NO_ERROR;
                cout << "Please enter column string that you want to move: ";
                cin >> temp_letter;


                //alfabe kontrol
                for (int i = ZERO; i < temp_letter.size() && alpha_flag != ERROR; ++i) {
                    if (isalpha(temp_letter[i]) == ZERO)
                        alpha_flag = ERROR;
                }
                //harf buyutme
                if (alpha_flag == NO_ERROR)
                    for (int i = ZERO; i < temp_letter.size(); ++i) {
                        temp_letter[i] = toupper(temp_letter[i]);
                    }
                //ikincil kontrol
                for (int i = ZERO; i < temp_letter.size() && range_flag != ERROR; ++i) {
                    if (temp_letter[i] < 'A' && temp_letter[i] > 'Z')
                        range_flag = ERROR;
                }



                if (alpha_flag != NO_ERROR && range_flag != NO_ERROR) {
                    cout << "Out of range or letter format, check again!" << endl;
                    cin.clear();
                    cin.ignore(STR_LENGTH, '\n');
                    error_flag = ERROR;
                }

                col_coor = temp_letter;

            } while (error_flag == ERROR);

        }

    }







    // Belirtilen koordinatlar uzerinde hamleyi yapar

    void Reversi::update_table(char player_ch, char target_ch, int coor_x, int coor_y) {
        // hamle yapilacak yere isaret koyar
        setTheOwnerOfCell(coor_x, coor_y, player_ch);

        ++arr_size;

        gameCells[arr_size - ONE] = (Cell(coor_x, Cell::get_y_as_string(coor_y), player_ch));

        horizontal_update(player_ch, target_ch, coor_x, coor_y);
        vertical_update(player_ch, target_ch, coor_x, coor_y);
        diagonal_update(player_ch, target_ch, coor_x, coor_y);
    }
    //vektorde cell aramasi yapar, eger aranan koordinatlar icin varsa isaretini dondurur

    const char Reversi::return_the_ch(int coor_x, int coor_y) const {


        for (int i = ZERO; i < arr_size; ++i) {
            if (gameCells[i].get_x() == coor_x && gameCells[i].get_y_as_integer() == coor_y)
                return gameCells[i].get_owner();
        }
        return EMPTY_MARK;
    }
    //belirtilen kordinatlara sahip olan cell icin isaret degisimini yapar

    void Reversi::setTheOwnerOfCell(int coor_x, int coor_y, char _owner) {
        for (int i = ZERO; i < arr_size; ++i) {
            if (gameCells[i].get_x() == coor_x && gameCells[i].get_y_as_integer() == coor_y)
                gameCells[i].set_owner(_owner);
        }
    }

    void Reversi::clearTheTable() {
        delete [] gameCells;
        arr_size = ZERO;
        arr_cap = size_x * size_y;
        gameCells = new Cell[ arr_cap ];

    }

    //belirtilen durumlara gore ilk tahtanin elemeanlarini ayarlar

    void Reversi::initialize_board() {

        clearTheTable();


        if (getHeight() == ONE || getWidth() == ONE) {
            cerr << "Unplayable table" << endl;
            exit(ERROR);
        } else if (getHeight() % HALF == ZERO && getWidth() % HALF == ONE && arr_cap >= arr_size - ADD_FOUR_FOR_INITIAL) {
            arr_size += ADD_FOUR_FOR_INITIAL;
            gameCells[arr_size - ADD_FOUR_FOR_INITIAL] = (Cell(((getHeight() / HALF) - ONE), Cell::get_y_as_string((getWidth() + ONE) / HALF - ONE), COMP_MARK));
            gameCells[arr_size - ADD_TWO_FOR_INITIAL] = (Cell((getHeight() / HALF), Cell::get_y_as_string((getWidth() + ONE) / HALF), COMP_MARK));

            gameCells[arr_size - ADD_THREE_FOR_INITIAL] = (Cell(((getHeight() / HALF) - ONE), Cell::get_y_as_string((getWidth() + ONE) / HALF), USER_MARK));
            gameCells[arr_size - ONE] = (Cell(((getHeight() / HALF)), Cell::get_y_as_string((getWidth() + ONE) / HALF - ONE), USER_MARK));
        } else if (getHeight() % HALF == ONE && getWidth() % HALF == ZERO && arr_cap >= arr_size - ADD_FOUR_FOR_INITIAL) {
            arr_size += ADD_FOUR_FOR_INITIAL;
            gameCells[arr_size - ADD_FOUR_FOR_INITIAL] = (Cell(((getHeight() + ONE) / HALF - ONE), Cell::get_y_as_string(getWidth() / HALF - ONE), USER_MARK));
            gameCells[arr_size - ADD_TWO_FOR_INITIAL] = (Cell(((getHeight() + ONE) / HALF), Cell::get_y_as_string(getWidth() / HALF), USER_MARK));

            gameCells[arr_size - ADD_THREE_FOR_INITIAL] = (Cell(((getHeight() + ONE) / HALF - ONE), Cell::get_y_as_string(getWidth() / HALF), COMP_MARK));
            gameCells[arr_size - ONE] = (Cell(((getHeight() + ONE) / HALF), Cell::get_y_as_string(getWidth() / HALF - ONE), COMP_MARK));
        } else if (getHeight() % HALF == ONE && getWidth() % HALF == ONE && arr_cap >= arr_size - ADD_FOUR_FOR_INITIAL) {
            arr_size += ADD_FOUR_FOR_INITIAL;
            gameCells[arr_size - ADD_FOUR_FOR_INITIAL] = (Cell(((getHeight() + ONE) / HALF - ONE), Cell::get_y_as_string((getWidth() + ONE) / HALF - ONE), COMP_MARK));
            gameCells[arr_size - ADD_TWO_FOR_INITIAL] = (Cell(((getHeight() + ONE) / HALF), Cell::get_y_as_string((getWidth() + ONE) / HALF), COMP_MARK));

            gameCells[arr_size - ADD_THREE_FOR_INITIAL] = (Cell(((getHeight() + ONE) / HALF - ONE), Cell::get_y_as_string((getWidth() + ONE) / HALF), USER_MARK));
            gameCells[arr_size - ONE] = (Cell(((getHeight() + ONE) / HALF), Cell::get_y_as_string((getWidth() + ONE) / HALF - ONE), USER_MARK));
        } else if (getHeight() % HALF == ZERO && getWidth() % HALF == ZERO && arr_cap >= arr_size - ADD_FOUR_FOR_INITIAL) {
            arr_size += ADD_FOUR_FOR_INITIAL;
            gameCells[arr_size - ADD_FOUR_FOR_INITIAL] = (Cell((getHeight() / HALF - ONE), Cell::get_y_as_string(getWidth() / HALF - ONE), COMP_MARK));
            gameCells[arr_size - ADD_TWO_FOR_INITIAL] = (Cell((getHeight() / HALF), Cell::get_y_as_string(getWidth() / HALF), COMP_MARK));

            gameCells[arr_size - ADD_THREE_FOR_INITIAL] = (Cell((getHeight() / HALF - ONE), Cell::get_y_as_string(getWidth() / HALF), USER_MARK));
            gameCells[arr_size - ONE] = (Cell((getHeight() / HALF), Cell::get_y_as_string(getWidth() / HALF - ONE), USER_MARK));
        }



    }
    //iki reversi oyununu karsilastirir, birincisi daha iyiyse bool true dondurur

    bool Reversi::isFirstBetter(const Reversi &other) const {
        double first_rate = ZERO, sec_rate = ZERO;
        int first_counter = ZERO, sec_counter = ZERO;
        // ilk tablodaki kullanici tas sayisi
        for (int i = ZERO; i < getHeight(); ++i) {
            for (int j = ZERO; j < getWidth(); ++j) {
                if (return_the_ch(i, j) == USER_MARK)
                    ++first_counter;
            }
        }

        // ikinci tablodaki kullanici tas sayisi
        for (int i = ZERO; i < other.getHeight(); ++i) {
            for (int j = ZERO; j < other.getWidth(); ++j) {
                if (other.return_the_ch(i, j) == USER_MARK)
                    ++sec_counter;
            }
        }
        // kullanici tasi sayisinin tablo buyuklugune orani sonucu verir
        first_rate = static_cast<double> (first_counter) / (getHeight() * getWidth());
        sec_rate = static_cast<double> (sec_counter) / (other.getHeight() * other.getWidth());



        if (first_rate > sec_rate)
            return true;
        else
            return false;
    }
    //oyunun bitip bitmedigini kontrol eder

    bool Reversi::is_end() {

        bool flag_user = false, flag = false, flag_comp = false;

        flag_user = createLegalTable(USER_MARK, COMP_MARK);
        flag_comp = createLegalTable(COMP_MARK, USER_MARK);

        if (flag_comp == false && flag_user == false) {
            flag = true;
            cout << "The game has ended. Last score:" << endl;
            cout << "User: " << player_score(USER_MARK) << endl;
            cout << "Computer: " << player_score(COMP_MARK) << endl;
            cout << "Thanks for playing!" << endl;

        } else
            flag = false;

        return flag;
    }
    // kullanicinin (ya da parametre gonderilirse bilgisayarin) tas sayisini doner

    int Reversi::player_score(char mark) {
        int counter = ZERO;
        for (int i = ZERO; i < getHeight(); i++) {

            for (int j = ZERO; j < getWidth(); j++) {
                if (return_the_ch(i, j) == mark)
                    ++counter;
            }
        }
        return counter;
    }




    //verilen string degerini integer'a  cevirip kullanilmasini saglar

    const int Reversi::get_y_as_integer(std::string str_coor) {
        int num = ZERO;

        for (int i = str_coor.size() - ONE; i >= ZERO; --i) {
            num += static_cast<int> (str_coor[i] - 'A')+(DIFF_BETWEEN_Z_AND_A * i);
        }


        return num;

    }

    //oyundaki canli hucreleri dondurur

    int Reversi::return_livings_of_this_obj() const {


        return arr_size;
    }

    // oyunun oynandigi, neredeyse tum fonksiyonlarin toplandigi genel fonksiyon

    void Reversi::playGame() {

        int size_Height, size_Width;


        cout << "Welcome to game of reversi, a.k.a. \"Othello\" " << endl;

        char whatWeWillDo = '0'; // menudeki karar icin
        while (whatWeWillDo != 'e' && whatWeWillDo != 'E') {// sonsuz dongu, cikis sartina kadar

            bool isGameContinues = true; // oyunun devamini degistirmek icin

            //Menu
            cout << "What will you do?" << endl;
            cout << "1- Play[Or Continue, if you started already](p)" << endl << "2- Play from beginning(r)" << endl << "3- Exit(e)" << endl;
            cin >> whatWeWillDo;

            if (whatWeWillDo == 'e' || whatWeWillDo == 'E') {
                break;



            } else if (whatWeWillDo == 'r' || whatWeWillDo == 'R') {
                // Table size alinmasi ve kontrolu, ilk oyun tahtasinin olusturulmasi
                cout << "What are the sizes you want for the game?" << "\n"
                        << "Both sizes must be greater than 2, please keep that in mind." << endl;
                do {
                    cout << "Height: ";
                    cin >> size_Height;

                    if (size_Height > ZERO)
                        set_Height(size_Height);
                    else {
                        cout << "Must be greater than zero, try again!" << endl;
                        cin.clear();
                        cin.ignore(STR_LENGTH, '\n');
                    }
                } while (size_Height < ZERO);


                do {
                    cout << endl << "Width: ";
                    cin >> size_Width;
                    if (size_Width > ZERO)
                        set_Width(size_Width);
                    else {
                        cout << "Must be greater than zero, try again!" << endl;
                        cin.clear();
                        cin.ignore(STR_LENGTH, '\n');
                    }
                } while (size_Width < ZERO);


                cout << endl;
                initialize_board();

                //print_game_board();
                cout << (*this);

                whatWeWillDo = 'p';

            }
            if (whatWeWillDo == 'p' || whatWeWillDo == 'P') {


                cout << "In this game, if you enter negative values the game enters to the main menu" << endl;

                // No move count 0 ise oyun oynanabilir, ilk artis bilgisayar ya da kullanicinin oyun oynayamamasindan kaynaklidir
                // No move count 2 olursa oyun biter, iki taraf da hareket edemez
                int no_move_count = START_POINT;
                int legal_counter = ZERO;
                while (!is_end()) {
                    isGameContinues = true;
                    /* User's turn */
                    if (no_move_count < BOTH_CANNOT_MOVE) {

                        legal_counter = createLegalTable(USER_MARK, COMP_MARK);

                        int x_coor;
                        string y_coor;
                        if (legal_counter != NOT_LEGAL_MOVE) {
                            no_move_count = START_POINT;
                            do {
                                take_input(x_coor, y_coor);
                                if (x_coor < ZERO)
                                    isGameContinues = false;
                                if (isGameContinues == false)
                                    break;
                                if (bool_game_board[x_coor][get_y_as_integer(y_coor)] != true)
                                    cout << "Your move is not legal, enter a legal move please" << endl;
                            } while (bool_game_board[x_coor][get_y_as_integer(y_coor)] != true);
                            if (isGameContinues == true) {
                                play(x_coor, get_y_as_integer(y_coor));
                            }
                        }
                    }
                    if (isGameContinues == false)
                        break;
                    /* Computer's Turn */
                    if (!is_end()) {
                        legal_counter = createLegalTable(USER_MARK, COMP_MARK);
                        (*this)++;
                    }
                }



            }
        }
    }

    std::ostream & operator<<(std::ostream & output_stream, const Reversi & obj) {

        //satirlar icin bosluk hesabi
        int space_limit = Reversi::rec_decimal_count(obj.getHeight());

        for (int i = ZERO; i < space_limit + ONE; i++) {
            cout << " ";

        }
        //sutunlarin basilmasi
        for (int letter_count = START_POINT; letter_count < obj.getWidth(); letter_count++) {
            cout << Cell::get_y_as_string(letter_count) << " ";

        }
        cout << endl;
        //elemanlarin basilmasi
        for (int i = START_POINT; i < obj.getHeight(); i++) {
            // satir numaralari
            cout << i + DELTA_ONE;
            for (int m = ZERO; m < space_limit - Reversi::rec_decimal_count(i + DELTA_ONE) + ONE; m++) {
                cout << " ";
            }
            //elemanlarin basilmasi, eleman yoksa nokta basilir
            for (int j = START_POINT; j < obj.getWidth(); j++) {
                cout << obj.return_the_ch(i, j);

                for (int i = ZERO; i < static_cast<int> (j / DIFF_BETWEEN_Z_AND_A) + ONE; i++) {
                    cout << " ";

                }

            }
            cout << endl;
        }


        cout << " ";
    }

    void Reversi::operator++(int) {
        // legal tablo olusturulur ve en iyi hamle belirlenir
        bool res = createLegalTable(COMP_MARK, USER_MARK);
        move_t best_move = max_move_of_computer(COMP_MARK, USER_MARK);
        // en iyi hamle eger bulunduysa oynanir
        if (best_move.change_count != START_POINT) {
            update_table(COMP_MARK, USER_MARK, best_move.coor_x, best_move.coor_y);
            cout << "The board after computer's move" << endl;
            print_game_board();
            cout << endl << endl;

        } else {
            cout << "No legal move for computer" << endl;

        }




    }

    void Reversi::operator++() {

        // legal tablo olusturulur ve en iyi hamle belirlenir
        bool res = createLegalTable(COMP_MARK, USER_MARK);
        move_t best_move = max_move_of_computer(COMP_MARK, USER_MARK);
        // en iyi hamle eger bulunduysa oynanir
        if (best_move.change_count != START_POINT) {
            update_table(COMP_MARK, USER_MARK, best_move.coor_x, best_move.coor_y);
            cout << "The board after computer's move" << endl;
            print_game_board();
            cout << endl << endl;
        } else {
            cout << "No legal move for computer" << endl;
        }
    }

    Reversi::Reversi(const Reversi & other) {


        arr_size = other.arr_size;
        arr_cap = other.arr_cap;
        set_Both(other.size_x, other.size_y);
        gameCells = new Cell[arr_cap];

        for (int i = 0; i < arr_size; i++) {
            gameCells[i] = other.gameCells[i];
        }
    }

    Reversi & Reversi::operator=(const Reversi & other) {


        if (arr_cap != other.arr_cap || arr_size != other.arr_size) {
            delete [] gameCells;
            gameCells = new Cell[other.arr_cap];
        }

        arr_cap = other.arr_cap;
        arr_size = other.arr_size;
        set_Both(other.size_x, other.size_y);

        for (int i = 0; i < arr_cap; i++) {
            gameCells[i] = other.gameCells[i];
        }


    }

    Reversi::~Reversi() {
        delete [] gameCells;

    }
}