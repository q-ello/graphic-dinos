#include "WelcomeScreen.h"
void WelcomeScreen::setScreenData()
{
	_welcomeText = Utils::setText(100, C_BRIGHT_GREEN, "Welcome to\nDino's Battle!",
		sf::Vector2f(130, 250));

	ScreenEmptyBase::setScreenData();
}

void WelcomeScreen::handleKeyReleasedEvent(sf::Keyboard::Scancode code)
{
	if (code == sf::Keyboard::Scan::Escape)
	{
		_window->close();
		return;
	}

	ScreenEmptyBase::handleKeyReleasedEvent(code);
}

void WelcomeScreen::goToNextScreen()
{
	MainScreen* mainScreen = new MainScreen(std::move(_window));
	mainScreen->show();
	delete mainScreen;
}

void WelcomeScreen::handleCloseWindowEvent()
{
	_window->close();
	return;
}