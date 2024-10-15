#pragma once
#include "./stdafx.h"

enum GroupType { Party, Resting };

class Game
{
public:
    Game();
    ~Game();

private:

    void start();

    sf::RenderWindow _window;
};
