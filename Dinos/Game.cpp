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


void Game::start()
{
	Player::load();
	_window.create(sf::VideoMode(1000, 800), "Dino's Battle!");

	WelcomeScreen* welcomeScreen = new WelcomeScreen(&_window);
	welcomeScreen->show();
	delete welcomeScreen;	
}