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

}

char array1[BOARD_SIZE][BOARD_SIZE];
char array2[BOARD_SIZE][BOARD_SIZE];

void Server::initialize(unsigned int board_size, string p1_setup_board, string p2_setup_board){

    //using current board size
    this->board_size = board_size;
    if(this->board_size != BOARD_SIZE){
        throw ServerException("Wrong Board Size");
    }
    //bad file name
    if(p1_setup_board != "player_1.setup_board.txt" && p2_setup_board != "player_2.setup_board.txt"){
        throw ServerException("Bad File Name");
    }
    ifstream board1;
    ifstream board2;
    board1.open("player_1.setup_board.txt");
    board2.open("player_2.setup_board.txt");
    //fill arrays with board contents
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            board1 >> array1[i][j];
            board2 >> array2[i][j];
        }
    }
}

int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {

    //bad player number
    if (player < 1 || player > 2) {
        throw ServerException("Bad Player Number");
    }
    //max in bounds
    if (x == (BOARD_SIZE - 1) || y == (BOARD_SIZE - 1)) {
        nothrow;
    }
    //out of bounds
    if(x >= board_size || x < 0 || y < 0 || y >= board_size){
        return OUT_OF_BOUNDS;
    }
    //hit or miss returned
    //out of bounds already handled
    if(player == 1) {
        if (array2[y][x] == '_') {
            return MISS;
        } else if (array2[y][x] != '_') {
            return HIT;
        }
    } else{
        if (array1[y][x] == '_') {
            return MISS;
        } else if (array1[y][x] != '_') {
            return HIT;
        }
    }
}


int Server::process_shot(unsigned int player) {

    //bad player number
    if(player < 1 || player > 2){
        throw ServerException("Bad Player Number");
    }
    //declare x and y shot variables
    int x, y;
    if(player == 1) {
        std::ifstream shot("player_1.shot.json");
        cereal::JSONInputArchive inputShot(shot);
        inputShot(x, y);

        int result = evaluate_shot(player, x, y);

        std::ofstream file("player_1.result.json");
        cereal::JSONOutputArchive outputShot(file);
        outputShot(CEREAL_NVP(result));

        //remove file in between shots
        remove("player_1.shot.json");
        return SHOT_FILE_PROCESSED;
    } else if(player == 2){
        std::ifstream shot("player_2.shot.json");
        cereal::JSONInputArchive inputShot(shot);
        inputShot(x, y);

        int result = evaluate_shot(player, x, y);

        std::ofstream file("player_2.result.json");
        cereal::JSONOutputArchive outputShot(file);
        outputShot(CEREAL_NVP(result));

        //remove file in between shots
        remove("player_2.shot.json");
        return SHOT_FILE_PROCESSED;
    } else {
        //return if no shot file present
        return NO_SHOT_FILE;
    }
}