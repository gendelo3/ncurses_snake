//
// Created by robin on 08.05.20.
//

#include "Snake.h"
#include "ncurses.h"
#include <vector>
#include <utility>
#include <cstdlib>
#include <unistd.h>


int ssx = 4;  // dimensions of a single cell
int ssy = 2;  // get square cells if possible...

void Snake::initTerminal() {
    initscr();
    cbreak();
    noecho();
    curs_set(false);
    nodelay(stdscr, true);
    keypad(stdscr, true);
    start_color();
    use_default_colors();
    init_pair(4, COLOR_RED, COLOR_RED);
    init_pair(7, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_GREEN);
    init_pair(3, COLOR_CYAN, COLOR_CYAN);
    init_pair(5, COLOR_BLUE, COLOR_BLUE);
    init_pair(6, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(8, COLOR_BLACK, COLOR_WHITE);
    // set background to "white", so everyone can see colored tetrominos
    // no matter their own color settings
    bkgd(COLOR_PAIR(8));
}

void Snake::showCell(int x, int y, int attr) {
    attron(attr);
    for (int i = 0; i < ssx; i++) {
        for (int j = 0; j < ssy; j++) {
            if (y < _size + 1) {
                mvprintw((_size + 1 - y) * ssy + j, (5 + x) * ssx + i, " ");
            }
        }
    }
    attroff(attr);
}

void Snake::drawBorderLine() {
    for (int i = 0; i < _size; i++) {
        showCell(i, -1, A_REVERSE);
    }
    for (int i = -1; i < _size; i++) {
        showCell(-1, i, A_REVERSE);
    }
    for (int i = -1; i < _size; i++) {
        showCell(_size, i, A_REVERSE);
    }
    for (int i = -1; i < _size + 1; i++) {
        showCell(i, _size, A_REVERSE);
    }
}

void Snake::draw() {
    clear();
    drawBorderLine();
    for (auto pair : current_snake) {
        showCell(pair.first, pair.second, COLOR_PAIR(2));
    }
    showCell(current_snake.back().first, current_snake.back().second, COLOR_PAIR(3));
    showCell(food_position.first, food_position.second, COLOR_PAIR(4));
    refresh();
}

void Snake::update(int key_code) {
    switch (key_code) {
        case KEY_LEFT:
            direction = (direction - 1) % 4;
            if (direction < 0) {direction += 4;}
            break;
        case KEY_RIGHT:
            direction = (direction + 1) % 4;
            break;
        default:
            break;
    };
    mvprintw(0,0, "%d", direction); // TODO: remove
    std::pair<int, int> current_position = current_snake.back();
    int delta_x = 0;
    int delta_y = 0;
    switch (direction) {
        case 0:
            delta_x = 1;
            break;
        case 2:
            delta_x = -1;
            break;
        case 1:
            delta_y = -1;
            break;
        case 3:
            delta_y = 1;
            break;
        default:
            break;
    }
    std::pair<int, int> next_position = {current_position.first+delta_x,
                                         current_position.second+delta_y};

    if (check_collision(next_position.first, next_position.second)) {
        mvprintw(0,3, "col %d , %d ",next_position.first, next_position.second);
        reset_snake();
        return;
    } else {
        mvprintw(0,3, "good        ");
    }
    current_snake.push_back(next_position);
    if (next_position.first == food_position.first && next_position.second == food_position.second) {
        // found food, dont erase last
        spawn_food();
    } else {
        current_snake.erase(current_snake.begin());

    }
}

void Snake::play() {
    reset_snake();
    initTerminal();
    int key_code;
    while (true) {
        draw();
        key_code = getch();
        update(key_code);

        usleep(250000);
    }
}

void Snake::spawn_food() {
    int x,y;
    while (true) {
        x = lrand48() % _size;
        y = lrand48() % _size;
        if (!check_collision(x,y)) {
            break;
        }
    }
    food_position.first = x;
    food_position.second = y;


}

bool Snake::check_collision(int x, int y) {
    for (auto pair : current_snake) {
        if (pair.first == x && pair.second == y) {
            return true;
        }
    }
    if (x < 0 || y < 0 || x >= _size || y >= _size) {
        return true;
    }
    return false;
}

void Snake::reset_snake() {
    current_snake = { {5, 3}, {5,4}, {5,5}};
    direction = initial_direction;
    spawn_food();
}
