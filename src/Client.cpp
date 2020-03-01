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
#include "Client.hpp"

Client::~Client() {
}


void Client::initialize(unsigned int player, unsigned int board_size){
    //10x10 board
    //take the player number entered and assign it, look at board and determine size

    //make matrix board_size x board_size dimensions
        //get into json file and use for loop to fill array with it?

    //make the action board and fill with "O"
    string Action_Board[BOARD_SIZE][BOARD_SIZE] = {{"O"}};
}


void Client::fire(unsigned int x, unsigned int y) {
    //figure out where to ask for coordinates
    //row and column of matrix
}


bool Client::result_available() {
    //no result file

    //good result file
}


int Client::get_result() {
}



void Client::update_action_board(int result, unsigned int x, unsigned int y) {
}


string Client::render_action_board(){
}