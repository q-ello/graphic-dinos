#pragma once
#include "ScreenBase.h"

class FightWelcomeScreen : public ScreenBase
{
public:
	using ScreenBase::ScreenBase;
private:
	void setScreenData() override;
	void createBG() override;
	void drawData() override;

	sf::Text _welcomeText;
	sf::Text _clueText;
	Terrain _terrain;
	sf::Texture _texture;

	void handleKeyReleasedEvent(sf::Keyboard::Scancode code) override;
	void handleMouseButtonReleasedEvent(sf::Event::MouseButtonEvent button) override;

	void startFight();
};