//
// Created by tinre on 4/19/2021.
//

#include "../include/connect4_app.h"


namespace connect4 {
    Connect4App::Connect4App() {
        ci::app::setWindowSize(kWindowSizeX, kWindowSizeY);
        current_col_ = board_.GetLength() / 2;
        showing_menu_ = true;
    }

    void Connect4App::draw() {
        ci::Color background_color("white");
        ci::gl::clear(background_color);
        if (!showing_menu_) {
            drawBoard();
            if (player1_using_delete_ || player2_using_delete_) {
                ci::gl::color(ci::Color("black"));
            } else if (player1_using_swap_ || player2_using_swap_) {
                ci::gl::color(ci::Color("green"));
            } else if (player1_using_blocker_ || player2_using_blocker_) {
                ci::gl::color(ci::Color("navy"));
            } else if (board_.IsPlayerOneTurn()) {
                ci::gl::color(ci::Color("red"));
            } else {
                ci::gl::color(ci::Color("yellow"));
            }

            ci::gl::drawSolidTriangle(
                    glm::vec2((kWindowSizeX / 4) + (current_col_ * board_.GetXSpace() + (board_.GetXSpace() / 2)),
                              (kWindowSizeY / 4) - 5),
                    glm::vec2((kWindowSizeX / 4) + (current_col_ * board_.GetXSpace()) - (board_.GetXSpace() / 2) +
                              (board_.GetXSpace() / 2),
                              (kWindowSizeY / 4) - board_.GetYSpace()),
                    glm::vec2((kWindowSizeX / 4) + (current_col_ * board_.GetXSpace()) + (board_.GetXSpace() / 2) +
                              (board_.GetXSpace() / 2),
                              (kWindowSizeY / 4) - board_.GetYSpace()));

            ci::gl::color(ci::Color("red"));
            ci::gl::drawSolidRect(ci::Rectf(glm::vec2(0, 0), glm::vec2(kWindowSizeX / 4, kWindowSizeY)));
            ci::gl::color(ci::Color("yellow"));
            ci::gl::drawSolidRect(
                    ci::Rectf(glm::vec2(3 * (kWindowSizeX / 4), 0), glm::vec2(kWindowSizeX, kWindowSizeY)));
            ci::gl::drawStringCentered("Player One", glm::vec2(kWindowSizeX / 8, kWindowSizeY / 8), ci::Color("black"),
                                       med);
            ci::gl::drawStringCentered("Player Two", glm::vec2(7 * (kWindowSizeX / 8), kWindowSizeY / 8),
                                       ci::Color("black"), med);

            ci::gl::color(ci::Color("black"));
            if (board_.IsPlayerOneTurn()) {
                ci::gl::drawStrokedRect(ci::Rectf(glm::vec2(2, 2), glm::vec2(kWindowSizeX / 4, kWindowSizeY / 4)), 4);
            } else {
                ci::gl::drawStrokedRect(ci::Rectf(glm::vec2(3 * (kWindowSizeX / 4), 2),
                                                  glm::vec2(kWindowSizeX - 2, (kWindowSizeY / 4))), 4);
            }

            if (game_type_ == 2) {
                if (board_.GetPlayer1TurnsUntilPowerup() == 0) {
                    if (player1_next_powerup_ == 0) {
                        ci::gl::drawStringCentered("Column Deleter is ready!",
                                                   glm::vec2(kWindowSizeX / 8, kWindowSizeY / 2), ci::Color("black"),
                                                   med);
                    } else if (player1_next_powerup_ == 1) {
                        ci::gl::drawStringCentered("Column Swapper is ready!",
                                                   glm::vec2(kWindowSizeX / 8, kWindowSizeY / 2), ci::Color("black"),
                                                   med);

                    } else if (player1_next_powerup_ == 2) {
                        ci::gl::drawStringCentered("Blocker is ready!",
                                                   glm::vec2(kWindowSizeX / 8, kWindowSizeY / 2), ci::Color("black"),
                                                   med);
                    }
                    ci::gl::drawStringCentered("Press 's' to use your power up",
                                               glm::vec2(kWindowSizeX / 8, kWindowSizeY / 2 + 40), ci::Color("black"),
                                               small);
                } else {
                    ci::gl::drawStringCentered(
                            std::to_string(board_.GetPlayer1TurnsUntilPowerup()) + " turns until next power up",
                            glm::vec2(kWindowSizeX / 8, kWindowSizeY / 2), ci::Color("black"), med);
                }

                if (board_.GetPlayer2TurnsUntilPowerup() == 0) {
                    if (player2_next_powerup_ == 0) {
                        ci::gl::drawStringCentered("Column Deleter is ready!",
                                                   glm::vec2(7 * (kWindowSizeX / 8), kWindowSizeY / 2),
                                                   ci::Color("black"),
                                                   med);
                    } else if (player2_next_powerup_ == 1) {
                        ci::gl::drawStringCentered("Column Swapper is ready!",
                                                   glm::vec2(7 * (kWindowSizeX / 8), kWindowSizeY / 2),
                                                   ci::Color("black"),
                                                   med);
                    } else if (player2_next_powerup_ == 2) {
                        ci::gl::drawStringCentered("Blocker is ready!",
                                                   glm::vec2(7 * (kWindowSizeX / 8), kWindowSizeY / 2),
                                                   ci::Color("black"),
                                                   med);
                    }
                    ci::gl::drawStringCentered("Press 's' to use your power up",
                                               glm::vec2(7 * (kWindowSizeX / 8), kWindowSizeY / 2 + 40),
                                               ci::Color("black"),
                                               small);
                } else {
                    ci::gl::drawStringCentered(
                            std::to_string(board_.GetPlayer2TurnsUntilPowerup()) + " turns until next power up",
                            glm::vec2(7 * (kWindowSizeX / 8), kWindowSizeY / 2), ci::Color("black"), med);
                }

            }
        } else {
            drawMenu();
        }
    }

    void Connect4App::setup() {
        /*
        ci::audio::SourceFileRef source = ci::audio::load(ci::app::loadAsset("/home/tinre/bruh.mp3"));
        mVoice = ci::audio::Voice::create(source);
         */
    }

    void Connect4App::drawBoard() {
        try {
            board_.DrawBoard();
            if (board_.GetWinner() == kPlayerOneToken) {
                ci::gl::color(ci::Color("royalblue"));
                ci::gl::drawSolidRect(ci::Rectf(glm::vec2(kWindowSizeX / 4, kWindowSizeY / 4),
                                                glm::vec2(3 * (kWindowSizeX / 4), 3 * (kWindowSizeY / 4))));
                ci::gl::drawStringCentered(
                        "RED WINS!",
                        glm::vec2(kWindowSizeX / 2, kWindowSizeY / 2), ci::Color("black"), large);
                ci::gl::drawStringCentered(
                        "Press 'esc' to return to main menu",
                        glm::vec2(kWindowSizeX / 2 + board_.GetXSpace(), kWindowSizeY / 2 + board_.GetYSpace()),
                        ci::Color("black"), small);
            } else if (board_.GetWinner() == kPlayerTwoToken) {
                ci::gl::color(ci::Color("royalblue"));
                ci::gl::drawSolidRect(ci::Rectf(glm::vec2(kWindowSizeX / 4, kWindowSizeY / 4),
                                                glm::vec2(3 * (kWindowSizeX / 4), 3 * (kWindowSizeY / 4))));
                ci::gl::drawStringCentered(
                        "YELLOW WINS!",
                        glm::vec2(kWindowSizeX / 2, kWindowSizeY / 2), ci::Color("black"), large);
                ci::gl::drawStringCentered(
                        "Press 'esc' to return to main menu",
                        glm::vec2(kWindowSizeX / 2 + board_.GetXSpace(), kWindowSizeY / 2 + board_.GetYSpace()),
                        ci::Color("black"), small);
            } else if (board_.GetWinner() == 'd') {
                ci::gl::color(ci::Color("royalblue"));
                ci::gl::drawSolidRect(ci::Rectf(glm::vec2(kWindowSizeX / 4, kWindowSizeY / 4),
                                                glm::vec2(3 * (kWindowSizeX / 4), 3 * (kWindowSizeY / 4))));
                ci::gl::drawStringCentered(
                        "draw :(",
                        glm::vec2(kWindowSizeX / 2, kWindowSizeY / 2), ci::Color("black"), large);
                ci::gl::drawStringCentered(
                        "Press 'esc' to return to main menu",
                        glm::vec2(kWindowSizeX / 2 + board_.GetXSpace(), kWindowSizeY / 2 + board_.GetYSpace()),
                        ci::Color("black"), small);
            }
        } catch (std::exception &e) {
            std::cout << e.what();
        }
    }

    void Connect4App::initializeBoard() {
        board_ = GameBoard(length_, height_, win_length_, true, 0, kWindowSizeX, 0, kWindowSizeY, game_type_);

        // 0 = Delete Column
        // 1 = Swap Column
        // 2 = Blocker
        player1_next_powerup_ = rand() % 3;
        player2_next_powerup_ = rand() % 3;

        player1_using_delete_ = false;
        player2_using_delete_ = false;

        player1_using_blocker_ = false;
        player2_using_blocker_ = false;

        player1_using_swap_ = false;
        player2_using_swap_ = false;

        swap_col_1 = -1;
    }

    void Connect4App::drawMenu() const {
        ci::Color background_color("white");
        ci::gl::clear(background_color);


        ci::gl::drawStringCentered("Press 1 for a Standard Game", glm::vec2(kWindowSizeX / 2, kWindowSizeY / 8),
                                   ci::Color("black"), large);
        ci::gl::drawStringCentered("Press 2 for a Wild Game", glm::vec2(kWindowSizeX / 2, 2 * (kWindowSizeY / 8)),
                                   ci::Color("black"), large);
        ci::gl::drawStringCentered("Use the left and right arrow to change the length of the board",
                                   glm::vec2(kWindowSizeX / 2, 3 * (kWindowSizeY / 8)),
                                   ci::Color("black"), med);
        ci::gl::drawStringCentered("Use the up and down arrows to change the height of the board",
                                   glm::vec2(kWindowSizeX / 2, 4 * (kWindowSizeY / 8)),
                                   ci::Color("black"), med);
        ci::gl::drawStringCentered("Use '<' and '>' to change the win length",
                                   glm::vec2(kWindowSizeX / 2, 5 * (kWindowSizeY / 8)),
                                   ci::Color("black"), med);

        ci::gl::drawStringCentered("Height: " + std::to_string(height_),
                                   glm::vec2(kWindowSizeX / 2, 11 * (kWindowSizeY / 16)),
                                   ci::Color("black"), small);
        ci::gl::drawStringCentered("Length: " + std::to_string(length_),
                                   glm::vec2(kWindowSizeX / 2, 12 * (kWindowSizeY / 16)),
                                   ci::Color("black"), small);
        ci::gl::drawStringCentered("Win Length: " + std::to_string(win_length_),
                                   glm::vec2(kWindowSizeX / 2, 13 * (kWindowSizeY / 16)),
                                   ci::Color("black"), small);
        ci::gl::drawStringCentered("Make sure either length or height is less than or equal to the win length!",
                                   glm::vec2(kWindowSizeX / 2, 14 * (kWindowSizeY / 16)), ci::Color("black"), small);
    }

    void Connect4App::keyDown(ci::app::KeyEvent event) {
        switch (event.getCode()) {

            case ci::app::KeyEvent::KEY_s:
                if (game_type_ == 2) {
                    if (player1_using_swap_ || player2_using_swap_ || player1_using_delete_ || player2_using_delete_ ||
                        player1_using_blocker_ || player2_using_blocker_) {
                        player1_using_delete_ = false;
                        player2_using_delete_ = false;

                        player1_using_blocker_ = false;
                        player2_using_blocker_ = false;

                        player1_using_swap_ = false;
                        player2_using_swap_ = false;

                        swap_col_1 = -1;
                    } else if (board_.IsPlayerOneTurn() && board_.GetPlayer1TurnsUntilPowerup() == 0) {
                        if (player1_next_powerup_ == 0) {
                            player1_using_delete_ = true;
                        } else if (player1_next_powerup_ == 1) {
                            player1_using_swap_ = true;
                        } else if (player1_next_powerup_ == 2) {
                            player1_using_blocker_ = true;
                        }
                    } else if (!(board_.IsPlayerOneTurn()) && board_.GetPlayer2TurnsUntilPowerup() == 0) {
                        if (player2_next_powerup_ == 0) {
                            player2_using_delete_ = true;
                        } else if (player2_next_powerup_ == 1) {
                            player2_using_swap_ = true;
                        } else if (player2_next_powerup_ == 2) {
                            player2_using_blocker_ = true;
                        }
                    }
                }
                break;

            case ci::app::KeyEvent::KEY_RIGHT:
                if (!showing_menu_) {
                    if (current_col_ + 1 < board_.GetLength()) {
                        current_col_++;
                    }
                } else {
                    length_++;
                }
                break;

            case ci::app::KeyEvent::KEY_LEFT:
                if (!showing_menu_) {
                    if (current_col_ - 1 >= 0) {
                        current_col_--;
                    }
                } else {
                    if (length_ - 1 > 0) {
                        length_--;
                    }
                }
                break;

            case ci::app::KeyEvent::KEY_UP:
                if (showing_menu_) {
                    height_++;
                }
                break;

            case ci::app::KeyEvent::KEY_DOWN:
                if (showing_menu_) {
                    if (height_ - 1 > 0) {
                        height_--;
                    }
                }
                break;

            case ci::app::KeyEvent::KEY_COMMA:
                if (showing_menu_) {
                    if (win_length_ - 1 > 0) {
                        win_length_--;
                    }
                }
                break;

            case ci::app::KeyEvent::KEY_PERIOD:
                if (showing_menu_) {
                    win_length_++;
                }
                break;


            case ci::app::KeyEvent::KEY_RETURN:
                if (player1_using_delete_ || player2_using_delete_) {
                    board_.DeleteColumn(current_col_);
                    if (player1_using_delete_) {
                        player1_using_delete_ = false;
                        player1_next_powerup_ = rand() % 3;
                    } else {
                        player2_using_delete_ = false;
                        player2_next_powerup_ = rand() % 3;
                    }
                } else if (player1_using_swap_ || player2_using_swap_) {
                    if (swap_col_1 == -1) {
                        swap_col_1 = current_col_;
                    } else if (current_col_ != swap_col_1) {
                        board_.SwapColumns(swap_col_1, current_col_);
                        swap_col_1 = -1;
                        if (player1_using_swap_) {
                            player1_using_swap_ = false;
                            player1_next_powerup_ = rand() % 3;
                        } else {
                            player2_using_swap_ = false;
                            player2_next_powerup_ = rand() % 3;
                        }
                    }
                } else if (player1_using_blocker_ || player2_using_blocker_) {
                    try {
                        board_.DropBlocker(current_col_);
                        if (player1_using_blocker_) {
                            player1_using_blocker_ = false;
                            player1_next_powerup_ = rand() % 3;
                        } else {
                            player2_using_blocker_ = false;
                            player2_next_powerup_ = rand() % 3;
                        }
                    } catch (const std::out_of_range &e) {
                        std::cout << "Out of Range!" << std::endl;
                    }
                } else {
                    try {
                        board_.DropPiece(current_col_, false);
                    } catch (const std::exception &e) {
                        std::cout << "Error!" << std::endl;
                    }
                }
                break;

            case ci::app::KeyEvent::KEY_ESCAPE:
                if (!showing_menu_) {
                    showing_menu_ = true;
                    board_.Clear();
                    current_col_ = board_.GetLength() / 2;
                }
                break;

            case ci::app::KeyEvent::KEY_1:
                if (showing_menu_) {
                    if (win_length_ <= length_ || win_length_ <= height_) {
                        showing_menu_ = false;
                        game_type_ = 1;
                        initializeBoard();
                    }
                }
                break;

            case ci::app::KeyEvent::KEY_2:
                if (showing_menu_) {
                    if (win_length_ <= length_ || win_length_ <= height_) {
                        showing_menu_ = false;
                        game_type_ = 2;
                        initializeBoard();
                    }
                }
                break;
        }
    }
}
