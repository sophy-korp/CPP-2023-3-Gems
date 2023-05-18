#include <GL/freeglut.h>
#include <GL/glu.h>
#include "board.h"
#include<set>
/*
 * 1. Засечь прикосновение

2. Если прикосновения два и кубики рыдом, поменять их местами

3. Проверить доску на компоненты связности

4. Если есть что удалять удалить

5. Если есть какие бонусы активировать - активировать

Повторять 4 и 5 пока можем*/

#ifndef INC_3VRYAD_GAME_H
#define INC_3VRYAD_GAME_H

class Game {
public:
    Game() :board(5) {
        touch1 = { -1, -1 };
        touch2 = { -1, -1 };
        time = 0;
        time_to_wait = 2000;
        gravity_used = true;
        no_black_cells = true;
    };
    void init_game(int argc, char** argv) {
        // инициализация
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
        glutInitWindowPosition(100, 100);
        glutInitWindowSize(400, 400);
        glutCreateWindow("Лабораторная 3");

        register_auxiliary_functions(); //позже напишем

        glutMainLoop();
    }
    Board board;
    void mechanics();
    std::pair<int, int> touch1;
    std::pair<int, int> touch2;


private:
    void register_auxiliary_functions();
    int time;
    int time_to_wait;
    bool gravity_used;
    bool no_black_cells;
};


#endif //INC_3VRYAD_GAME_H
