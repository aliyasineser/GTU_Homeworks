/* 
 * File:   HW6_141044058_AliYasin_Eser.cpp
 * Author: aliyasineser
 *Reversi classi icin test dosyasi
 * Created on December 10, 2015, 11:53 AM
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include "Reversi.h"
const int FIVE_GAME = 5;
const int FIVE_CELLS = 5;

using namespace GTU_YASIN_REVERSI;
using namespace std;

/*
 * 
 */


void see_the_initial_game(Reversi rev_obj);

int main(int argc, char** argv) {


    Reversi games[FIVE_GAME];

    cout << "***********************REVERSI CONTROL***********************" << endl;
    cout << "Welcome to Reversi test program." << endl;
    cout << "Now let's play a little of first game!" << endl;

    games[0].playGame();
    cout << "And now, for comparing reversi games, please play another game " << endl;

    games[1].playGame();

    cout << "Is second game better than first? Answer is: " << endl;
    if (games[1].isFirstBetter(games[0]))
        cout << "Yes!" << endl;
    else
        cout << "Nope!" << endl;

    cout << "We tested sending reference class obejects to functions." << endl;

    cout << "Now it is the time for testing call by value. "
            << "We will send to fucntion a reversi object that you played before, "
            << "and function gonna initialize and print the game board. "
            << "After that, we will print the original object, and we'll see de difference"
            << endl;


    cout << " The board that we will send the function looks like: " << endl << endl
            << games[0] << endl << endl << "We sending the object to funciton! " << endl;



    cout << "Now let's check the object we sent. Looks like: " <<  endl 
            << games[0] << endl << endl;

    see_the_initial_game(games[0]);
    
    
    cout << "Call by value test is over. Let's test copy constructor!" << endl;

    cout << "We know how our first board looks like, so let's create another one." << endl;

    Reversi test_copy_const = games[0];

    cout << "We created the other board with using copy constructor. "
            << "The board must looks the same. Like that: " << endl << test_copy_const
            << endl << "Copy constructor test has finished." << endl;


    cout << "Now it's time to test assignment operator. We have two first games. "
            << "We created one with using copy constructor. So let's assign our second "
            << "game to first, and after that, assign our test game to first game!" << endl;

    games[0] = games[1];

    cout << "After assignment, first game changed as second: " << endl << games[0] << endl;

    games[0] = test_copy_const;

    cout << "After second assignment, first game changed as real first game: "
            << endl << games[0] << endl << "Assignment test has finished." << endl;

    cout << "***********************CELL CONTROL***********************" << endl;


    Cell test_cells[FIVE_CELLS];

    cout << "Operator ++ Test: " << endl << "First Cell: " << test_cells[0] << endl;
    test_cells[0]++;
    cout << "After the ++ operator: " << test_cells[0] << endl << endl;

    cout << "Operator -- Test: " << endl << "First Cell: " << test_cells[0] << endl;
    test_cells[0]--;
    cout << "After the -- operator: " << test_cells[0] << endl << endl;

    test_cells[4]++;
    test_cells[4]++;
    test_cells[4]++;
    test_cells[3]++;
    test_cells[3]++;
    cout << "First Cell: " << test_cells[4] << endl << "Second Cell: "
            << test_cells[3] << endl;

    cout << "We are gonna test: Greater than and it's equalty of that, "
            << "Smaller than and it's equalty of that, " << "Equal and not equal to symbol. "
            << "If you see zero(0), it means false and otherwise is true." << endl;


    cout << "Is first cell greater than sec? " << (test_cells[4] > test_cells[3]) << endl;

    cout << "Is first cell greater or equal to sec? " << (test_cells[4] >= test_cells[3]) << endl;

    cout << "Is first cell smaller than sec? " << (test_cells[4] < test_cells[3]) << endl;

    cout << "Is first cell smaller or equal to sec? " << (test_cells[4] <= test_cells[3]) << endl;

    cout << "Is first cell equal to sec? " << (test_cells[4] == test_cells[3]) << endl;

    cout << "Is first cell not equal to sec? " << (test_cells[4] == test_cells[3]) << endl;

    cout << "All tests are over now. " << endl;



    return 0;
}

void see_the_initial_game(Reversi rev_obj) {

    rev_obj = Reversi();
    cout << "The object has been initialized. The board looks like: " << endl << endl;
    cout << rev_obj;

    cout << "Function has finished" << endl << endl;

}