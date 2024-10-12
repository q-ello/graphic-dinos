#include "FightFinalScreen.h"

FightFinalScreen::FightFinalScreen(sf::RenderWindow* window, const std::string& verdict, sf::Texture* texture)
	: _texture {texture}
	, ScreenEmptyBase(window)
{
	_welcomeText = Utils::setText(40, C_DARK_GREEN, verdict);
	const sf::Vector2f textSize = _welcomeText.getGlobalBounds().getSize();
	const sf::Vector2f textPos = Utils::alignToCenter(&_welcomeText);
	_welcomeText.setPosition(textPos);
}

void FightFinalScreen::createBG()
{
	_bg = Utils::setBG(_texture);
}

void FightFinalScreen::goToNextScreen()
{
	_show = false;
	return;
}
