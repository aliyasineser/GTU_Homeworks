/* 
 * File:   HW4_141044058_AliYasin_Eser.cpp
 * Author: aliyasineser
 *Reversi classi icin test dosyasi
 * Created on November 8, 2015, 11:53 AM
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include "Reversi.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    
    Reversi game, game2;
    
    game.playGame();
    
    
    // Eger ikinci oyunu da oynayarak test etmek isterseniz:
    
    //game2.playGame();
    //cout << game2.isFirstBetter(game);

    
    return 0;
}

