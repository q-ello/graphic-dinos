#include "WelcomeScreen.h"

void WelcomeScreen::setScreenData()
{
	_welcomeText = Utils::setText(100, C_BRIGHT_GREEN, "Welcome to\nDino's Battle!",
		sf::Vector2f(130, 250));

	_clueText = Utils::setClueText(C_BRIGHT_GREEN);
}

void WelcomeScreen::drawData()
{
	_window->draw(_welcomeText);
	_window->draw(_clueText);
}

void WelcomeScreen::handleKeyReleasedEvent(sf::Keyboard::Scancode code)
{
	if (code == sf::Keyboard::Scan::Escape)
	{
		_window->close();
		return;
	}
	goToMainScreen();
}

void WelcomeScreen::handleMouseButtonReleasedEvent(sf::Event::MouseButtonEvent button)
{
	goToMainScreen();
}

void WelcomeScreen::handleCloseWindowEvent()
{
	_window->close();
	return;
}

void WelcomeScreen::goToMainScreen()
{
	MainScreen* mainScreen = new MainScreen(std::move(_window));
	mainScreen->show();
	delete mainScreen;
}
