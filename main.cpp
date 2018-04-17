//#include <Windows.h>            // Windows only
#include <FL/Fl.H>
#include <ctime>
#include "GameWindow.h"
using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    GameWindow* game = new GameWindow(800, 600);
    return Fl::run();
}
