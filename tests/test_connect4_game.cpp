//
// Created by tinre on 4/19/2021.
//

#include <connect4_board.h>

#include <catch2/catch.hpp>

using connect4::GameBoard;

TEST_CASE("Constructor Tests") {
    SECTION("Normal Construction") {
        GameBoard test_board(7, 6, 4);
        REQUIRE(test_board.GetBoard().size() == 7);
        REQUIRE(test_board.GetBoard().at(5).size() == 6);
        REQUIRE(test_board.GetBoard().at(5).at(5) == ' ');
    }

    SECTION("Win length longer than board size") {
        REQUIRE_THROWS([&](){
            GameBoard test_board(3, 3, 4);
        }());
    }
}

