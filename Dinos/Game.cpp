#include "Game.h"
#include "WelcomeScreen.h"
#include "Player.h"

Game::Game()
{
	Utils::loadFont();

	start();
}
Game::~Game()
{
	Player::clearData();
}
/*
* void Game::drawParty(int x, int y)
{
	for (int i = 0; i < _currentParty.size(); i++)
	{
		_currentParty[i]->draw(_window, Idle, x + 20 * i, y);
	}
}

void Game::drawResting(int x, int y)
{
	for (int i = 0; i < _ownedDinosaurs.size(); i++)
	{
		_ownedDinosaurs[i]->draw(_window, Idle, x + 20 * i, y);
	}
}
*/


void Game::start()
{
	_window.create(sf::VideoMode(1000, 800), "Dino's Battle!");

	WelcomeScreen* welcomeScreen = new WelcomeScreen(&_window);
	welcomeScreen->show();
	delete welcomeScreen;	
}