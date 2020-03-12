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

using namespace std;


/**
 * Calculate the length of a file (helper function)
 *
 * @param file - the file whose length we want to query
 * @return length of the file in bytes
 */

//used CSCI_366_Examples for all json related problems
//https://github.com/msu-netlab/CSCI_366_examples/blob/master/serialization/main.cpp
//also used
//https://lastviking.eu/json_serialization.html

//used for setting up vectors
//https://stackoverflow.com/questions/29696168/a-fast-way-to-set-values-of-a-2d-vector-to-0

//declare arrays outside of everything so they can be accessed by every function
char array1[BOARD_SIZE][BOARD_SIZE];
char array2[BOARD_SIZE][BOARD_SIZE];

//never used? Don't know what to use for
int get_file_length(ifstream *file){
    file->seekg(0, ios::beg);
    int start = file->tellg();
    file->seekg(0, ios::end);
    int end = file->tellg();
    return end - start;
}

void Server::initialize(unsigned int board_size, string p1_setup_board, string p2_setup_board){


    Server::board_size = BOARD_SIZE;

    //using current board size instead of board size defined in Server.hpp
    this->board_size = board_size;
    if(this->board_size != BOARD_SIZE){
        throw ServerException("Wrong Board Size");
    }

    //bad file name exception
    if(p1_setup_board != "player_1.setup_board.txt" && p2_setup_board != "player_2.setup_board.txt"){
        throw ServerException("Bad File Name");
    }
    //use ifstreams defined in Server.hpp
    Server::p1_setup_board.open("player_1.setup_board.txt");
    Server::p2_setup_board.open("player_2.setup_board.txt");

    //fill arrays with board contents
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            Server::p1_setup_board >> array1[i][j];
            Server::p2_setup_board >> array2[i][j];
        }
    }
    Server::p1_setup_board.close();
    Server::p2_setup_board.close();
}

int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {

    //bad player number throws exception
    if (player < 1 || player > 2) {
        throw ServerException("Bad Player Number");
    }
    //max in bounds throws nothing
    if (x == (BOARD_SIZE - 1) || y == (BOARD_SIZE - 1)) {
        nothrow;
    }
    //checks shot with board size
    if(x >= Server::board_size || x < 0 || y < 0 || y >= Server::board_size){
        return OUT_OF_BOUNDS;
    }
    //hit or miss returned for each player
    //out of bounds already handled
    if(player == 1) {
        if (array2[y][x] == '_') {
            return MISS;
        } else{
            return HIT;
        }
    } else if (player == 2){
        if (array1[y][x] == '_') {
            return MISS;
        } else{
            return HIT;
        }
    }
}

int Server::process_shot(unsigned int player) {

    //error happens in process shot
    //has a problem with the json files

    //bad player number
    if(player < 1 || player > 2){
        throw ServerException("Bad Player Number");
    }

    //declare x and y shot variables
    int x,y;

    //seperate cases for each player

    if(player == 1) {
        ifstream shot("player_1.shot.json");
        cereal::JSONInputArchive inputShot(shot);
        inputShot(x, y);

        int result = evaluate_shot(player, x, y);

        ofstream file("player_1.result.json");
        //somewhere here
        cereal::JSONOutputArchive outputShot(file);
        outputShot(CEREAL_NVP(result));

        //remove file in between shots
        remove("player_1.shot.json");
        return SHOT_FILE_PROCESSED;
    } else if(player == 2){
        ifstream shot("player_2.shot.json");
        cereal::JSONInputArchive inputShot(shot);
        inputShot(x, y);

        int result = evaluate_shot(player, x, y);

        ofstream file("player_2.result.json");
        //error happens somewhere here
        cereal::JSONOutputArchive outputShot(file);
        outputShot(CEREAL_NVP(result));

        //remove file in between shots
        remove("player_2.shot.json");
        return SHOT_FILE_PROCESSED;
    }

    else {
        return NO_SHOT_FILE;
    }
}