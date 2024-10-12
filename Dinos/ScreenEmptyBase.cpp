#include "ScreenEmptyBase.h"

void ScreenEmptyBase::setScreenData()
{
	_clueText = Utils::setClueText(C_BRIGHT_GREEN);
}

void ScreenEmptyBase::drawData()
{
	_window->draw(_welcomeText);
	_window->draw(_clueText);
}

void ScreenEmptyBase::handleKeyReleasedEvent(sf::Keyboard::Scancode code)
{
	goToNextScreen();
}

void ScreenEmptyBase::handleMouseButtonReleasedEvent(sf::Event::MouseButtonEvent button)
{
	goToNextScreen();
}