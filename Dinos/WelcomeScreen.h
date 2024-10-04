#pragma once
#include "ScreenBase.h"
#include "MainScreen.h"

class WelcomeScreen : public ScreenBase
{
public:
	using ScreenBase::ScreenBase;
	WelcomeScreen();
protected:
	sf::Text _welcomeText;
	sf::Text _clueText;

	void setScreenData() override;
	void drawData() override;

	void handleKeyReleasedEvent(sf::Keyboard::Scancode code) override;
	void handleMouseButtonReleasedEvent(sf::Event::MouseButtonEvent button) override;
	void handleCloseWindowEvent() override;

	void goToMainScreen();
};