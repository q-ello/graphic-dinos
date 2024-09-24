#pragma once
#include "stdafx.h"
#include "Player.h"
#include "Utils.h"
#include "Popup.h"

enum saveChoice
{
	S_SAVE,
	S_NOT,
	S_CANCEL
};

class ScreenBase
{
public:
	ScreenBase(sf::RenderWindow* window);

	void show();

protected:
	sf::RenderWindow* _window;
	int _money;
	sf::Text _moneyText;
	Popup* _popup;
	sf::RectangleShape _bg;

	virtual void setScreenData() = 0;
	void setMoneyData();
	virtual void drawData() = 0;
	virtual void handleKeyPressedEvent(sf::Keyboard::Scancode code);
	virtual void handleKeyReleasedEvent(sf::Keyboard::Scancode code);
	virtual void handleMouseButtonPressedEvent(sf::Event::MouseButtonEvent button);
	virtual void handleMouseButtonReleasedEvent(sf::Event::MouseButtonEvent button);
	virtual void handleMouseMovedEvent(sf::Event::MouseMoveEvent moveEvent);
	virtual void handleCloseWindowEvent();
	virtual void createBG();
	void drawBG();
	void handlePopupChoice(E_Choice choice);
	void virtual handleDiffPopupChoice(E_Choice choice);
};