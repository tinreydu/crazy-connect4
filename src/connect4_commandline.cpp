//
// Created by tinre on 4/20/2021.
//

#include <string>
#include <iostream>
#include "connect4_commandline.h"

namespace connect4 {
    void CommandLine::Display() const {
        std::string output;
        for (int y = board.GetHeight(); y > 0; y--) {
            output += "|";
            for (int x = 0; x < board.GetLength(); x++) {
                output += board.GetBoard().at(x).at(y - 1);
                output += "|";
            }
            output += "\n";
        }
        std::cout << output << std::endl;
    }

    void CommandLine::Query() {
        if (board.IsPlayerOneTurn()) {
            std::cout << "You are player 1.Type a command or a row to drop a piece: ";
        } else {
            std::cout << "You are player 2.Type a command or a row to drop a piece: ";
        }
        std::string input;
        std::cin >> input;
        int col = std::stoi(input);
        board.DropPiece(col, false);
    }
}