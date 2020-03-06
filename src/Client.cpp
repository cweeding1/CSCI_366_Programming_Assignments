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

//used CSCI_366_Examples for all json related problems
//https://github.com/msu-netlab/CSCI_366_examples/blob/master/serialization/main.cpp
//also used for json problems
//https://lastviking.eu/json_serialization.html

//used for setting up vectors
//https://stackoverflow.com/questions/29696168/a-fast-way-to-set-values-of-a-2d-vector-to-0

Client::~Client() {
}

void Client::initialize(unsigned int player, unsigned int board_size){

    //sets "board_name" defined in hpp file
    Client::board_size = board_size;

    //sets vector and fills with 0's
    std::vector<std::vector<int>> action_board;
    action_board.resize(board_size, std::vector<int>(board_size, 0));

    if(player == 1){
        Client::player = 1;
        board_name = "player_1.action_board.json";
    } else if(player == 2){
        Client::player = 2;
        board_name = "player_2.action_board.json";
    }

    //
    std::ofstream array_ofp(board_name);
    cereal::JSONOutputArchive writeOutput(array_ofp);
    writeOutput(cereal::make_nvp("board", action_board));

    //set initialized to true to advance from player number
    if(player < 1 || player > 2){
        throw ClientException("Wrong Player Number");
    } else{
        initialized = true;
    }
}

void Client::fire(unsigned int x, unsigned int y) {

    if(Client::player == 1) {
        std::ofstream file_write("player_1.shot.json");
        cereal::JSONOutputArchive fire_wr(file_write);
        fire_wr(CEREAL_NVP(x), CEREAL_NVP(y));
    } else if(Client::player == 2){
        std::ofstream file_write("player_2.shot.json");
        cereal::JSONOutputArchive fire_wr(file_write);
        fire_wr(CEREAL_NVP(x), CEREAL_NVP(y));
    }
}

bool Client::result_available() {

    if(Client::player == 1){
        string fileName = "player_1.result.json";
        std::ifstream infile(fileName);
        if(infile.good()){
            return true;
        } else{
            return false;
        }
    } else if(Client::player == 2){
        string fileName = "player_2.result.json";
        std::ifstream infile(fileName);
        if(infile.good()){
            return true;
        } else{
            return false;
        }
    }
}

int Client::get_result() {

    string fileName;

    if (Client::player == 1) {
        fileName = "player_1.result.json";
    } else if (Client::player == 2) {
        fileName = "player_2.result.json";
    }
    //define an int that holds HIT,MISS,OUT_OF_BOUNDS
    int shotResult;
    std::ifstream result_read(fileName);
    cereal::JSONInputArchive result_ready(result_read);
    result_ready(shotResult);
    //remove files so they do not get used twice
    remove("player_1.result.json");
    remove("player_2.result.json");

    if (shotResult == 1) {
        return HIT;
    } else if (shotResult == -1) {
        return MISS;
    } else if (shotResult == 0) {
        return OUT_OF_BOUNDS;
    } else {
        throw ClientException("Bad Result");
    }
}

void Client::update_action_board(int result, unsigned int x, unsigned int y) {

    string fileName;
    //change file name based on player number
    if (Client::player == 1) {
        fileName = "player_1.action_board.json";
    } else if (Client::player == 2) {
        fileName = "player_2.action_board.json";
    }

    //initialize vector for the action board
    std::vector<vector<int>> actionBoard;
    std::ifstream action_file_read(fileName);
    cereal::JSONInputArchive archive_in(action_file_read);
    archive_in(actionBoard);
    actionBoard[x][y] = result;

    if(Client::player ==  1){
        if(result == HIT) {
            std::ofstream outputResult("player_1.action_board.json");
            cereal::JSONOutputArchive writeOutput(outputResult);
            writeOutput(cereal::make_nvp("board", actionBoard));

        }else if (result == MISS) {
            std::ofstream outputResult("player_1.action_board.json");
            cereal::JSONOutputArchive writeOutput(outputResult);
            writeOutput(cereal::make_nvp("board", actionBoard));
        }
    }else if(Client::player == 2){
        if(result == HIT) {
            std::ofstream outputResult("player_2.action_board.json");
            cereal::JSONOutputArchive writeOutput(outputResult);
            writeOutput(cereal::make_nvp("board", actionBoard));

        }else if (result == MISS) {
            std::ofstream outputResult("player_2.action_board.json");
            cereal::JSONOutputArchive writeOutput(outputResult);
            writeOutput(cereal::make_nvp("board", actionBoard));
        }
    }
}

string Client::render_action_board() {

    /*
    if(Client::player == 1){
        return "player_1.action_board.json \n";
    }else if(Client::player == 2){
        return "player_2.action_board.json \n";
    }
     */
}