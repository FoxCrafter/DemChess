#include "config_consts.h"
#include "game.h"

namespace ui {

class UI {
    Game *game = nullptr;
    static unsigned n_rows, n_cols;
    void update_dimensions();
    class Canvas {
        Game const *const *game;
        class CanvasCoors {
            unsigned y, x;
        public:
            CanvasCoors(Board const &board, Coors coors);
            unsigned screen_y(int offset);
            unsigned screen_x(int offset);
        };
        class SquareDrawer {
            Canvas const &canvas;
        public:
            SquareDrawer(Canvas const &canvas) : canvas(canvas) {}
            void operator()(Square &square);
        };
        static unsigned const offset_step = 1;
        int offset_x = 0;
        int offset_y = 0;
    public:
        void init(Game const *const *game) { this->game = game; }
        void offset(int ch);
        void draw() const;
    } canvas;
    class CoorInput {
        Game const *const *game;
        Coors data;
        unsigned curr = 0;
        unsigned curr_sign = 1;
    public:
        CoorInput() { reset(); }
        void init(Game **game) { this->game = game; }
        void switch_to(unsigned i) {
            curr = i;
            curr_sign = data[i] < 0 ? -1 : 1;
        }
        void next() {
            switch_to((curr + 1) % rules::DIMENSIONS);
        }
        void prev() {
            switch_to((curr + rules::DIMENSIONS - 1) % rules::DIMENSIONS);
        }
        void reset() {
            for(unsigned i = 0; i < rules::DIMENSIONS; ++i)
                data[i] = 0;
            switch_to(0);
        }
        void char_in(int ch);
        bool is_valid(unsigned i) {
            Board const &board = (*game)->get_board();
            return data[i] >= board.get_min_coors()[i]
                && data[i] <= board.get_max_coors()[i];
        }
        Coors get_coors() { return data; }
        void print();
    } coor_input;
    class LogDisplay {
        static unsigned const BUFF_SIZE = 256;
        char buff[BUFF_SIZE] = {0};
    public:
        void set(char const *str);
        void print();
    } log_display;
public:
    UI();
    void start_new_game();
    void draw();
    void main_loop();
    virtual ~UI();
};

}
