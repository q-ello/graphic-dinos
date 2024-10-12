#include "FightWelcomeScreen.h"

void FightWelcomeScreen::setScreenData()
{
	std::string terrainStr;
	std::string bonusStr;
	_terrain = Player::newTerrain();

	switch (_terrain)
	{
	case T_Plain:
		_texture.loadFromFile("images/plain.png");
		terrainStr = "PLAIN";
		bonusStr = "DINOSTR";
		break;
	case T_Mountain:
		_texture.loadFromFile("images/mountain.png");
		terrainStr = "MOUNTAIN";
		bonusStr = "DINOINT";
		break;
	default:
		_texture.loadFromFile("images/river.png");
		terrainStr = "RIVER";
		bonusStr = "DINODEX";
		break;
	}

	_welcomeText = Utils::setText(50, C_DARK_GREEN, "You are fighting in " + terrainStr + ".\n" + 
		"Damage of " + bonusStr + " is doubled.", sf::Vector2f(100, 300));
	_welcomeText.setOutlineThickness(4);

	ScreenEmptyBase::setScreenData();
}

void FightWelcomeScreen::createBG()
{
	_bg = Utils::setBG(&_texture);
}

void FightWelcomeScreen::goToNextScreen()
{
	FightMainScreen* fight = new FightMainScreen(_window, &_texture, _terrain);
	fight->show();
	delete fight;
	_show = false;
	return;
}