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
		bonusStr = "STRENGTH";
		break;
	case T_Mountain:
		_texture.loadFromFile("images/mountain.png");
		terrainStr = "MOUNTAIN";
		bonusStr = "INTELLECT";
		break;
	default:
		_texture.loadFromFile("images/river.png");
		terrainStr = "RIVER";
		bonusStr = "DEXTERITY";
		break;
	}

	_welcomeText = Utils::setText(50, C_DARK_GREEN, "You are fighting in " + terrainStr + ".\n" + bonusStr + " is doubled.",
		sf::Vector2f(150, 300));
	_welcomeText.setOutlineThickness(4);
	_clueText = Utils::setClueText(C_DARK_GREEN);
	_clueText.setOutlineThickness(1);
}

void FightWelcomeScreen::createBG()
{
	_bg = Utils::setBG(&_texture);
}

void FightWelcomeScreen::drawData()
{
	_window->draw(_welcomeText);
	_window->draw(_clueText);
}

void FightWelcomeScreen::handleKeyReleasedEvent(sf::Keyboard::Scancode code)
{
	startFight();
}

void FightWelcomeScreen::handleMouseButtonReleasedEvent(sf::Event::MouseButtonEvent button)
{
	startFight();
}

void FightWelcomeScreen::startFight()
{

	_show = false;
	return;
}
