#include <iostream>

#include "Snake.h"
#include <unistd.h>
#include "ncurses.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Snake snake;

    snake.play();




    return 0;
}
