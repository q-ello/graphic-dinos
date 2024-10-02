#pragma once

#include "ScreenBase.h"
#include "DinoCard.h"
#include "DinoPopup.h"

class PartyScreen : public ScreenBase
{
public:
	using ScreenBase::ScreenBase;
	~PartyScreen();
protected:
	std::vector<DinoCard*> _dinos;
	int _activeIndex{ 0 };

	void setScreenData() override;
	void drawData() override;
	void handleKeyPressedEvent(sf::Keyboard::Scancode code) override;
	void handleKeyReleasedEvent(sf::Keyboard::Scancode code) override;
	void handleMouseButtonPressedEvent(sf::Event::MouseButtonEvent button) override;
	void handleMouseButtonReleasedEvent(sf::Event::MouseButtonEvent button) override;
	void handleMouseMovedEvent(sf::Event::MouseMoveEvent moveEvent) override;
	virtual void setNewActiveIndex(std::pair<int, int> direction);
	void handleDiffPopupChoice(int choice) override;

	void changeFocusedButton(std::pair<int, int> index, bool withArrows = true);
	virtual void changeDino();
	virtual void updateDinoCards();
};