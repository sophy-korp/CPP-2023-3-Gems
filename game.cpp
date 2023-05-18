#include "game.h"


Game* CurrentInstance;

extern "C"
void renderScene() {
    // очистка буфера цвета и глубины
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    CurrentInstance->mechanics();
    CurrentInstance->board.print(CurrentInstance->touch1, CurrentInstance->touch2);
    glutSwapBuffers();
}


void mouseButton(int button, int state, int x, int y) {
    // если нажата левая кнопка

    if (button == GLUT_LEFT_BUTTON) {
        // когда кнопка отпущена
        if (state == GLUT_UP && CurrentInstance->board.to_delete.empty()) {
            if (CurrentInstance->touch1 == std::pair<int, int>({ -1, -1 })) {
                CurrentInstance->touch1.first = x / 80;
                CurrentInstance->touch1.second = y / 80;
            }
            else {
                if (CurrentInstance->touch2 == std::pair<int, int>({ -1, -1 })) {
                    CurrentInstance->touch2.first = x / 80;
                    CurrentInstance->touch2.second = y / 80;
                }
            }
            std::cout << CurrentInstance->touch1.first << ' ' << CurrentInstance->touch1.second<<'\n';
            std::cout << CurrentInstance->touch2.first << ' ' << CurrentInstance->touch2.second << '\n';
            std::cout << '\n';
        }
    }
}

void Game::register_auxiliary_functions() {
    CurrentInstance = this;
    ::glutDisplayFunc(::renderScene);
    ::glutIdleFunc(::renderScene);
    ::glutMouseFunc(::mouseButton);
}

void Game::mechanics() {
    time++;
    std::pair<int, int> empty = { -1, -1 };
    if (touch1 == empty and touch2 == empty and gravity_used and no_black_cells
        and board.to_delete.empty() and board.to_activate.empty()) {
        board.CheckDelete();
        if (!board.to_delete.empty()) {
            time = 0;
        }
    }
    if (time >= time_to_wait) {
        time = 0;
        if (touch1 != empty and touch2 != empty) {
            //поменять местами квадратики
            board.ChangePlaces(touch1, touch2);
            touch1 = empty;
            touch2 = empty;
        }
        if (!board.to_delete.empty()) {
            //удаление
            board.DeleteCells();
            gravity_used = false; //если удалили клетки, то 100% надо применять гравитацию
            no_black_cells = false; //если удалили клетки, то остались чёрные клетки и их надо заполнить
            return;
        }
        if (!board.to_activate.empty()) {
            //активация
            board.Activation();
            return;
        }
        if (!gravity_used) {
            board.Gravity();
            gravity_used = true;
            return;
        }
        if (!no_black_cells) {
            //закрасить чёрные клетки
            board.DrawBlackCells();
            no_black_cells = true;
            return;
        }

    }
}