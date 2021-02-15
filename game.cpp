#include <conio.h>
#include <ctime>
#include <iostream>
#include <cstdlib>

#include "game.h"


using namespace std;

/***********************************************************************************
*                                      Snake
*       @description
*       This is a constructor. Initialization menu.
************************************************************************************/
Snake::Snake() {
    game_over = false;
    game_state[0] = "#############\n#############\n### START ###\n## press e ##\n#############\n# QUIT GAME #\n## press t ##\n#############";
    game_state[1] = "#############\n#############\n### PAUSE ###\n## press p ##\n#############\n# QUIT GAME #\n## press t ##\n#############";
    game_state[2] = "# GAME OVER #\n#############\n## RESTART ##\n## press r ##\n#############\n# QUIT GAME #\n## press t ##\n#############";
    game_state[3] = "#############\n#############\n#############\n### ERROR ###\n## restart ##\n#############\n#############\n#############";
}

/***********************************************************************************
*                                      start
*       @description
*       This method starts the game
************************************************************************************/
void Snake::start() {
    status = eOptions::START;
    event_loop();
}

/***********************************************************************************
*                                  event_loop
*       @description
*       This method controls the life state of the game, the user continues to play 
*       until the game is turned off
************************************************************************************/
void Snake::event_loop() {
    setup_default_settings();
    while (!game_over) {
        draw_field();
        key_event();
        move_snake();
        update_snake_status();
    }
}

/***********************************************************************************
*                              setup_default_settings
*       @description
*       This method initializes the starting values of the game states(position 
*       snake, snake direction, position of good and bad friuts, and score)
************************************************************************************/
void Snake::setup_default_settings() {
    pos_snake = make_pair(width / 2, height / 2);
    direction = eSnakeStatus::NONE;
    setup_fruit(false);
    setup_fruit(true);
    score = 0;
}

/***********************************************************************************
*                                   restart
*       @description
*       This method restarts the game from the beginning
************************************************************************************/
void Snake::restart() {
    status = eOptions::FINISH;
    setup_default_settings();
}

/***********************************************************************************
*                                   draw_field
*       @description
*       This method is responsible for controlling the call of display methods
*       depending on the state of the game and user actions
************************************************************************************/
void Snake::draw_field() {
    clear_screen();
    if (status == eOptions::START) {
        _draw_start();
    }
    else if (status == eOptions::PAUSE) {
        _draw_pause();
    }
    else if (status == eOptions::FINISH) {
        _draw_finish();
    }
    else if (status == eOptions::GAME) {
        _draw_game();
    }
    else {
        _draw_error();
    }
}

/***********************************************************************************
*                                   _draw_start
*       @description
*       This method displays the start menu
************************************************************************************/
void Snake::_draw_start() {
    cout << game_state[0] << endl;
}

/***********************************************************************************
*                                   _draw_pause
*       @description
*       This method displays the pause menu
************************************************************************************/
void Snake::_draw_pause() {
    cout << game_state[1] << endl;
}

/***********************************************************************************
*                                   _draw_finish
*       @description
*       This method displays the game over menu
************************************************************************************/
void Snake::_draw_finish() {
    cout << game_state[2] << endl;
}

/***********************************************************************************
*                                   _draw_game
*       @description
*       This method displays the game field
************************************************************************************/
void Snake::_draw_game() {
    for (size_t i = 0; i < width; ++i) {
        cout << static_cast<char>(eElemets::WALL);
    }
    cout << endl;

    for (size_t j = 1; j < height - 1; ++j) {
        for (size_t i = 0; i < width; ++i) {
            if (i == 0 || i == width - 1) {
                cout << static_cast<char>(eElemets::WALL);
            }
            else if (i == pos_snake.first && j == pos_snake.second) {
                cout << static_cast<char>(eElemets::SNAKE_HEAD);
            }
            else if (i == pos_fruit.first && j == pos_fruit.second) {
                cout << static_cast<char>(eElemets::FRUIT);
            }
            else if (i == pos_bad_fruit.first && j == pos_bad_fruit.second) {
                cout << static_cast<char>(eElemets::BAD_FRUIT);
            }
            else {
                bool prnt = false;
                for (auto k : pos_snake_body) {
                    if (i == k.first && j == k.second) {
                        cout << static_cast<char>(eElemets::SNAKE_BODY);
                        prnt = true;
                        break;
                    }
                }
                if (!prnt) {
                    cout << static_cast<char>(eElemets::SPACE);
                }

            }
        }
        cout << endl;
    }

    for (size_t i = 0; i < width; ++i) {
        cout << static_cast<char>(eElemets::WALL);
    }
    cout << endl;
    cout << "Score: " << score << endl;
    cout << "FRIUT: " << pos_fruit.first << " " << pos_fruit.second << endl;
    cout << "BAD_FRIUT: " << pos_bad_fruit.first << " " << pos_bad_fruit.second << endl;
}

/***********************************************************************************
*                                   _draw_error
*       @description
*       This method displays the error menu
************************************************************************************/
void Snake::_draw_error() {
    cout << game_state[3] << endl;
}

/***********************************************************************************
*                                   clear_screen
*       @description
*       This method clears the console
************************************************************************************/
void Snake::clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/***********************************************************************************
*                                   key_event
*       @description
*       This method monitors and handles keypress states
************************************************************************************/
void Snake::key_event() {
    if (_kbhit()) {
        int symbol = _getch();
        if (symbol == 't') {
            game_over = true;
        }
        if (status == eOptions::START) {
            if (symbol == 'e') {
                status = eOptions::GAME;
            }
        }
        else if (status == eOptions::PAUSE) {
            if (symbol == 'p') {
                status = eOptions::GAME;
            }
        }
        else if (status == eOptions::FINISH) {
            if (symbol == 'r') {
                status = eOptions::START;
            }
        }
        else if (status == eOptions::GAME) {
            if (symbol == 'p') {
                status = eOptions::PAUSE;
            }
            if (symbol == 'w' && direction != eSnakeStatus::DOWN) {
                direction = eSnakeStatus::UP;
            }
            if (symbol == 's' && direction != eSnakeStatus::UP) {
                direction = eSnakeStatus::DOWN;
            }
            if (symbol == 'd' && direction != eSnakeStatus::RIGHT) {
                direction = eSnakeStatus::LEFT;
            }
            if (symbol == 'a' && direction != eSnakeStatus::LEFT) {
                direction = eSnakeStatus::RIGHT;
            }
        }
    }
}

/***********************************************************************************
*                                   move_snake
*       @description
*       This method controls the movement of the snake, pressing the corresponding 
*       keys changes the direction of movement
************************************************************************************/
void Snake::move_snake() {
    if (direction == eSnakeStatus::NONE) {
        return;
    }

    pos_snake_body.push_front(pos_snake);
    pos_snake_body.pop_back();

    if (direction == eSnakeStatus::UP) {
        pos_snake.second -= 1;
    }
    else if (direction == eSnakeStatus::DOWN) {
        pos_snake.second += 1;
    }
    else if (direction == eSnakeStatus::RIGHT) {
        pos_snake.first -= 1;
    }
    else if (direction == eSnakeStatus::LEFT) {
        pos_snake.first += 1;
    }
    else {
        status = eOptions::BAG;
    }
}

/***********************************************************************************
*                                   update_snake_status
*       @description
*       This method updates snake location on the game field(position head, 
*       position body)
************************************************************************************/
void Snake::update_snake_status() {

    for (auto k : pos_snake_body) {
        if (k == pos_snake) {
            restart();
        }
    }

    if (pos_snake.first == pos_fruit.first && pos_snake.second == pos_fruit.second) {
        score += 1;
        setup_fruit(false);
        pos_snake_body.push_front(pos_snake);
    }
    if (pos_snake.first == pos_bad_fruit.first && pos_snake.second == pos_bad_fruit.second) {
        score -= 1;
        setup_fruit(true);
        if (pos_snake_body.empty()) {
            restart();
        }
        else {
            pos_snake_body.pop_back();
        }

    }

    if (pos_snake.first == width-1) {
        pos_snake.first = 1;
    }
    else if (pos_snake.first == 0) {
        pos_snake.first = width - 2;
    }
    if (pos_snake.second == height-1) {
        pos_snake.second = 1;
    }
    else if (pos_snake.second == 0) {
        pos_snake.second = height - 2;
    }
}

/***********************************************************************************
*                                   setup_fruit  
*       @description
*       This method initialization bad fruit position on the game field or good fruit
*       position depending on input parameter.
* 
*       @input
*       is_bad_fruit - flag, if is true, bad fruit will be initializated, if it is 
*       false, good fruit position will be initializated.
************************************************************************************/
void Snake::setup_fruit(bool is_bad_fruit) {
    if (is_bad_fruit) {
        pos_bad_fruit = get_random_pos(is_bad_fruit);
    }
    else {
        pos_fruit = get_random_pos(is_bad_fruit);
    }
}

/***********************************************************************************
*                                get_random_pos
*       @description
*       This method returns random coordinates bad fruit or good fruit 
8       depending on input parameter.
*
*       @input
*       is_bad_fruit - flag, if is true, coordinates for the bad fruit are returned.
*       if it is false, coordinates for the good fruit are returned.
* 
*       @output
*       pair<size_t, size_t> - bad fruit or good fruit coordinates
************************************************************************************/
pair<size_t, size_t> Snake::get_random_pos(bool is_bad_fruit) {
    if (is_bad_fruit) {
        srand(static_cast<unsigned>(time(NULL)));
        return make_pair((rand() % (width - 2)) + 1, (rand() % (height - 2)) + 1);
    }
    else{
        srand(static_cast<unsigned>(time(NULL) + time(NULL)));
        return make_pair((rand() % (width - 2)) + 1, (rand() % (height - 2)) + 1);
    }
}
