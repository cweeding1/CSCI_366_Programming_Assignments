//    Battleship game assignment for MSU CSCI 366
//    Copyright (C) 2020    Mike P. Wittie
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.


#include "common.hpp"
#include "Server.hpp"
#include <fstream>
#include <iostream>


/**
 * Calculate the length of a file (helper function)
 *
 * @param file - the file whose length we want to query
 * @return length of the file in bytes
 */
int get_file_length(ifstream *file){
    return 2;
}

char board_1_array[BOARD_SIZE][BOARD_SIZE];
char board_2_array[BOARD_SIZE][BOARD_SIZE];

char action_1_array[BOARD_SIZE][BOARD_SIZE] = {{"O"}};
char action_2_array[BOARD_SIZE][BOARD_SIZE] = {{"O"}};


void Server::initialize(unsigned int board_size, string p1_setup_board, string p2_setup_board){

    //ifstream *ifs ((ifstream *) "player_1.setup_board.txt");
    //int file_length = get_file_length(ifs);

    if(board_size != BOARD_SIZE){
        __throw_bad_exception();
    }

    //bad file name
    if(p1_setup_board != "player_1.setup_board.txt" && p2_setup_board != "player_2.setup_board.txt"){
        __throw_bad_exception();
    }

    ifstream board_start;
    board_start.open("player_1.setup_board.txt");

    for(int r = 0; r < BOARD_SIZE; r++){
        for(int c = 0; c < BOARD_SIZE; c++){
            board_start >> board_1_array[r][c];
            cout << board_1_array[r][c];
        }
        cout << "\n";
    }

}


int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {

    //bad player number
    if (player < 1 || player > 2) {
        __throw_bad_exception();
    }

    if (x == (BOARD_SIZE - 1) || y == (BOARD_SIZE - 1)) {
        nothrow;
    }

    //hit/miss
    //if(board_1_array[y][x] == "_"){
        //return miss
    //}
    //else{
    // return hit
    //}

    if(x == 1){
        return 1;
    }
    if(x == 0){
        return -1;
    }

    if(x > board_size || y > board_size){
        return 0;
    }


    //if(y < 0 || y > (board_size- 1 ) || x < 0 || x > (board_size - 1)){
      //  return 0;
    //}


}


int Server::process_shot(unsigned int player) {

    //bad player number
    if(player < 1 || player > 2){
        __throw_bad_exception();
    }

   return NO_SHOT_FILE;
}