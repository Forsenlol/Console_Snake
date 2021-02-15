#pragma once

#include <vector>
#include <list>


class Snake {
public:
    explicit Snake();
    ~Snake() = default;
    void start();
private:
    static const size_t width = 31;
    static const size_t height = 21;
    bool game_over;
    int score;

    std::pair<size_t, size_t> pos_snake;
    std::pair<size_t, size_t> pos_fruit;
    std::pair<size_t, size_t> pos_bad_fruit;
    std::list<std::pair<size_t, size_t>> pos_snake_body;

    enum class eOptions { START, PAUSE, FINISH, GAME, BAG };
    eOptions status;
    std::vector<std::string> game_state{ 4 };

    enum class eSnakeStatus { NONE, UP, DOWN, LEFT, RIGHT };
    eSnakeStatus direction;

    enum class eElemets {SNAKE_HEAD = 'O', SNAKE_BODY = 'o', FRUIT = 'f', BAD_FRUIT = 'b', WALL = '#', SPACE = ' ' };

    void event_loop();
    void setup_default_settings();
    void draw_field();
    void _draw_start();
    void _draw_pause();
    void _draw_finish();
    void _draw_game();
    void _draw_error();
    void clear_screen();
    void key_event();
    void move_snake();
    void update_snake_status();
    void setup_fruit(bool bad_fruit);
    void restart();
    std::pair<size_t, size_t> get_random_pos(bool bad_fruit);
};

