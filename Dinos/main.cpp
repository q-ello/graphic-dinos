#include <SFML/Graphics.hpp>
#include "./Game.h"
#include <Windows.h>

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    srand(static_cast<unsigned int>(time(0)));

    Game* game = new Game();

    delete game;

    return 0;
}