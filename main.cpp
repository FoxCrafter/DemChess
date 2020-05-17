#include "ui.h"

#include <ctime>
#include <cstdlib>
#include <locale.h>

int main(int argc, char const *const *argv) {
    std::srand(std::time(0));
    setlocale(LC_ALL, "");
    Game game;
    ui::UI screen;
    screen.main_loop();
    return 0;
}
