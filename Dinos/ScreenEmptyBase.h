#pragma once
#include "ScreenBase.h"

class ScreenEmptyBase : public ScreenBase
{
public:
	using ScreenBase::ScreenBase;

protected:
	sf::Text _welcomeText;
	sf::Text _clueText;

	void setScreenData() override;
	void drawData() override;

	void handleKeyReleasedEvent(sf::Keyboard::Scancode code) override;
	void handleMouseButtonReleasedEvent(sf::Event::MouseButtonEvent button) override;

	virtual void goToNextScreen() = 0;
};