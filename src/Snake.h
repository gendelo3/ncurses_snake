//
// Created by robin on 08.05.20.
//

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include <vector>
#include <utility>

class Snake {
public:
    const int _size = 20;

    void initTerminal();

    void drawBorderLine();

    void showCell(int x, int y, int attr);

    void draw();

    void update(int key_code);

    void spawn_food();

    bool check_collision(int x, int y);

    void play();

    void reset_snake();

    const int initial_direction = 3;

    std::pair<int, int> food_position;
    int direction;
    std::vector<std::pair<int, int>> current_snake;

};


#endif //SNAKE_SNAKE_H
