#pragma once
#include "ScreenEmptyBase.h"
#include "MainScreen.h"

class WelcomeScreen : public ScreenEmptyBase
{
public:
	using ScreenEmptyBase::ScreenEmptyBase;
private:
	void setScreenData() override;

	void handleKeyReleasedEvent(sf::Keyboard::Scancode code) override;
	void handleCloseWindowEvent() override;
	void goToNextScreen() override;
};