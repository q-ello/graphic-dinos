#pragma once
#include "stdafx.h"
#include "Player.h"
#include "Utils.h"
#include "Popup.h"
#include "DinoCard.h"

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
	ScreenBase();

	void show();

protected:
	sf::RenderWindow* _window;
	sf::Text _moneyText;
	std::unique_ptr<Popup> _popup;
	sf::RectangleShape _bg;
	boolean _show{ true };
	Button _returnBtn;
	bool _waitingInput{ true };

	virtual void setScreenData() = 0;
	virtual void setMoneyData();
	virtual void drawData() = 0;
	virtual void handleKeyPressedEvent(sf::Keyboard::Scancode code);
	virtual void handleKeyReleasedEvent(sf::Keyboard::Scancode code);
	virtual void handleMouseButtonPressedEvent(sf::Event::MouseButtonEvent button);
	virtual void handleMouseButtonReleasedEvent(sf::Event::MouseButtonEvent button);
	virtual void handleMouseMovedEvent(sf::Event::MouseMoveEvent moveEvent);
	virtual void handleCloseWindowEvent();
	virtual void createBG();
	virtual void drawBG();
	virtual void handlePopupChoice(int choice);
	virtual void handleDiffPopupChoice(int choice);
};