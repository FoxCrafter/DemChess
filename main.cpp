#include "ui.h"

#include <ctime>
#include <cstdlib>

int main(int argc, char const *const *argv) {
    std::srand(std::time(0));
    Game game;
    ui::UI screen;
    screen.main_loop();
    return 0;
}
