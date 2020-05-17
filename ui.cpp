#include "ui.h"

#include <stdexcept>
#include <cstring>

#include <ncurses.h>

namespace ui {

UI::Canvas::CanvasCoors::CanvasCoors(Board &board, Coors coors) {
    Coors min_coors = board.get_min_coors();
    Coors max_coors = board.get_max_coors();
    // Y
    y = 0;
    unsigned coeff = 1;
    for(int i = rules::DIMENSIONS - 1; i >= 0; i -= 2) {
        y += coeff * (coors[i] = min_coors[i]);
        coeff = coeff * (max_coors[i] - min_coors[i] + 1) + 3;
    }
    y += rules::DIMENSIONS / 2 * 2 - 1;
    // X
    x = 0;
    coeff = 1;
    for(int i = rules::DIMENSIONS - 2; i >= 0; i -= 2) {
        x += coeff * (coors[i] - min_coors[i]);
        coeff = coeff * (max_coors[i] - min_coors[i] + 1) + 3;
    }
    x += rules::DIMENSIONS / 2 * 2 - 1;
}

unsigned UI::Canvas::CanvasCoors::screen_y(int offset) {
    int res = n_rows - 3 - y - offset;
    if(res < 0 || res >= n_rows - 2)
        throw std::out_of_range("Outside screen.");
    return res;
}

unsigned UI::Canvas::CanvasCoors::screen_x(int offset) {
    int res = 2 * (x - offset);
    if(res < 0 || res >= n_cols / 2 * 2)
        throw std::out_of_range("Outside screen.");
    return res;
}

void UI::Canvas::SquareDrawer::operator(Square &square) {
    CanvasCoors cc(square.get_coors());

}

void UI::Canvas::offset(int ch) {
    switch(ch) {
    case KEY_UP   : offset_y -= offset_step; break;
    case KEY_DOWN : offset_y += offset_step; break;
    case KEY_LEFT : offset_x -= offset_step; break;
    case KEY_RIGHT: offset_x += offset_step; break;
    }
}

void UI::Canvas::draw() const {
    Board const &board = (*game)->get_board();

}

unsigned UI::n_rows, UI::n_cols;

static short const COLOR_PAIR_INVALID = 1;
#define INVALID COLOR_PAIR(COLOR_PAIR_INVALID)

void UI::update_dimensions() {
    getmaxyx(stdscr, n_rows, n_cols);
}

void UI::CoorInput::char_in(int ch) {
    if(ch >= L'0' && ch <= L'9')
        data[curr] = data[curr] * 10 + (ch - L'0') * curr_sign;
    else if(ch == KEY_BACKSPACE || ch == 127) {
        if(data[curr] != 0)
            data[curr] /= 10;
        else if(curr_sign == -1)
            curr_sign = 1;
        else
            prev();
    }
    else if(ch == KEY_DC) {
        data[curr] = 0;
        curr_sign = 1;
    }
    else if(ch == L'-') {
        data[curr] *= -1;
        curr_sign *= -1;
    }
    else if(ch == L' ' || ch == L',') {
        next();
    }
}

void UI::CoorInput::print() {
    mvaddch(n_rows - 1, 0, '(');
    for(unsigned i = 0;; ++i) {
        if(!is_valid(i)) attron(INVALID);
        if(i == curr) {
            attron(A_UNDERLINE);
            if(data[i] == 0 && curr_sign == -1)
                addch('-');
        }
        printw("%d", data[i]);
        attroff(A_UNDERLINE);
        attroff(INVALID);
        if(i >= rules::DIMENSIONS - 1) break;
        addstr(", ");
    }
    addch(')');
}

void UI::LogDisplay::set(char const *str) {
    strncpy(buff, str, BUFF_SIZE - 1);
}

void UI::LogDisplay::print() {
    mvaddstr(n_rows - 2, 0, buff);
}

UI::UI() {
    initscr();
    if (has_colors() == FALSE) {
        endwin();
        throw std::runtime_error("terminal does not support color");
    }
    noecho();
    keypad(stdscr, TRUE);
    //raw();
    start_color();
    init_pair(COLOR_PAIR_INVALID, COLOR_WHITE, COLOR_RED);
    update_dimensions();
    start_new_game();
    coor_input.init(&game);
    canvas.init(&game);
}

void UI::start_new_game() {
    delete game;
    game = new Game();
}

void UI::draw() {
    clear();
    log_display.print();
    coor_input.print();
    refresh();
}

void UI::main_loop() {
    while(true) {
        draw();
        int input = wgetch(stdscr);
        if(input == KEY_RESIZE)
            update_dimensions();
        else if(input == KEY_ENTER || input == 10) {
            try {
                game->execute_move_order(coor_input.get_coors());
                coor_input.reset();
            }
            catch(MoveException ex) {
                log_display.set(ex.what());
            }
        }
        else if(input == KEY_UP || input == KEY_DOWN
             || input == KEY_LEFT || input == KEY_RIGHT)
            canvas.offset(input);
        else
            coor_input.char_in(input);
    }
}

UI::~UI() {
    delete game;
    endwin();
}

}
