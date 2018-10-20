/* 
 * File:   Cell.h
 * Author: aliyasineser
 * Cell classi icin implementation dosyasi
 * Created on November 8, 2015, 12:08 PM
 */

#ifndef CELL_H
#define	CELL_H

#include <string>

class Cell {
public:
    Cell();
    Cell(int _x, std::string _y);
    Cell(int _x, std::string _y, char _owner);

    void set_x(const int _x);
    void set_y(std::string _y);
    void set_owner(const char _owner);

    bool operator<(const Cell &sec) const;
    bool operator>(const Cell &sec) const;
    bool operator>=(const Cell &sec) const;
    bool operator<=(const Cell &sec) const;
    bool operator==(const Cell &sec) const;
    bool operator!=(const Cell &sec) const;
    const Cell& operator++();
    const Cell operator++(int);
    const Cell& operator--();
    const Cell operator--(int);
    friend std::ostream& operator<<(std::ostream &output_stream, Cell & obj);
    friend std::istream& operator>>(std::istream &input_stream, Cell & obj);

    inline const int get_x() const {
        return x;
    }

    inline const std::string get_y() const {
        return y;
    }

    const int get_y_as_integer() const;

    inline const char get_owner() const {
        return owner;
    }

    static const std::string get_y_as_string(const int _y);

    inline static int return_the_livings() {
        return livingCells;
    }

    // oyunun dosyadan yuklenmesindeki counter dengesizligi icin

    inline static int initialize_the_livings_for_load_game() {
        livingCells = 0;
        return livingCells;
    }



private:
    int x;
    std::string y;
    char owner;
    static int livingCells;
};

#endif	/* CELL_H */

