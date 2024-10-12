#pragma once
#include "ScreenBase.h"
#include "Button.h"
#include "ShopScreen.h"
#include "LuckyDinoButton.h"
#include "PartyScreen.h"
#include "RestingScreen.h"
#include "FightWelcomeScreen.h"

class MainScreen : public ScreenBase
{
public:
	using ScreenBase::ScreenBase;
	~MainScreen();

private:
	std::vector<std::vector<Button*>> _buttons{ {}, {}, {}, {} };
	std::pair<int, int> _activeIndex{ 0, 0 };

	void setScreenData() override;
	void drawData() override;
	void handleKeyPressedEvent(sf::Keyboard::Scancode code) override;
	void handleKeyReleasedEvent(sf::Keyboard::Scancode code) override;
	void handleMouseButtonPressedEvent(sf::Event::MouseButtonEvent button) override;
	void handleMouseButtonReleasedEvent(sf::Event::MouseButtonEvent button) override;
	void handleMouseMovedEvent(sf::Event::MouseMoveEvent moveEvent) override;
	void setNewActiveIndex(std::pair<int, int> direction);

	void changeFocusedButton(std::pair<int, int> index, bool withArrows = true);
	void changeState();

	void setDinosData();
};

