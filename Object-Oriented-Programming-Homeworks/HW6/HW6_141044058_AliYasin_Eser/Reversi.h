/* 
 * File:   Reversi.h
 * Author: aliyasineser
 *Reversi classi icin header dosyasi
 * Created on December 10 2015, 3:41 PM
 */

#ifndef REVERSI_H
#define	REVERSI_H

#include "Cell.h"
#include <vector>

namespace GTU_YASIN_REVERSI {

    struct move_t {
        int change_count, // Degistirebilinecek tas sayisi
        coor_x,
        coor_y;

    };

    class Reversi {
    public:

        Reversi();
        Reversi(int _size_x);
        Reversi(int _size_x, int _size_y);
        Reversi(const Reversi & other);

        
        void set_Height(int _size_x);
        void set_Width(int _size_y);
        void set_Both(int _size_x, int _size_y);
        void print_game_board() const;

        inline const int getHeight() const {
            return size_x;
        }

        
        inline const int getSize() const {
            return arr_size;
        }
        
        
        inline const int getCap() const {
            return arr_cap;
        }
        
        inline const int getWidth() const {
            return size_y;
        }
        int player_score(char mark);
        friend std::ostream & operator<<(std::ostream & output_stream, const Reversi & obj);

        Reversi & operator=(const Reversi & other);
        void operator++(int);
        void operator++();

        bool play(); // non const
        bool play(int _x, int _y); // non const
        bool is_end(); // non const
        void playGame(); // non const
        bool isFirstBetter(const Reversi &other) const;
        const char return_the_ch(int coor_x, int coor_y) const;
        static int rec_decimal_count(int num); // static
        ~Reversi();

    private:
        void clearTheTable();
        bool createLegalTable(char my_turn, char look_for); // non const
        bool vertical_check(int x_axis, int y_axis, int is_the_one, char my_turn, char look_for) const;
        bool horizontal_check(int x_axis, int y_axis, int is_the_one, char my_turn, char look_for) const;
        bool diagonal_check(int x_axis, int y_axis, int is_the_one, char my_turn, char look_for) const;
        void initialize_board(); // non const
        void horizontal_update(char player_ch, char target_ch, int coor_x, int coor_y); // non const
        int diagonal_count(char player_ch, char target_ch, int coor_x, int coor_y, int stone_count) const;
        int vertical_count(char player_ch, char target_ch, int coor_x, int coor_y, int stone_count) const;
        int horizontal_count(char player_ch, char target_ch, int coor_x, int coor_y, int stone_count) const;
        void diagonal_update(char player_ch, char target_ch, int coor_x, int coor_y); // non const
        void vertical_update(char player_ch, char target_ch, int coor_x, int coor_y); // non const
        move_t max_move_of_computer(char player_ch, char target_ch) const; // non const
        void update_table(char player_ch, char target_ch, int coor_x, int coor_y); // non const
        Cell return_the_cell(int x_coor, std::string y_coor) const;
        void setTheOwnerOfCell(int coor_x, int coor_y, char _owner); // non const
        void take_input(int &row_coor, std::string &col_coor); // non const
        static const int get_y_as_integer(std::string str_coor); // static

        int return_livings_of_this_obj() const;


        int size_x; // Height
        int size_y; // Width
        int arr_size; // Number of living cells on the board
        int arr_cap; // Max number that board can fill in

        Cell * gameCells; // game table
        std::vector< std::vector<bool> > bool_game_board; // legal bool game table

    };
}
#endif	/* REVERSI_H */

