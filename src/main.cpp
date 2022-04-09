#include "GameEngine.h"

#ifdef NDEBUG
    #include "windows.h"
#endif

int main() {

#ifdef NDEBUG
    // Hide console window in release mode
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);
#endif

    GameEngine engine;
    engine.init();
    engine.run();

    return 0;
}
