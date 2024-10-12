#pragma once
#include "stdafx.h"
#include "Button.h"
#include "Dino.h"

enum PopupType
{
	P_SAVE,
	P_INFORM,
	P_BUY,
	P_CHANGE,
	P_CONCEDE
};

class Popup
{
public:
	Popup(const std::string& mainText, PopupType type = P_INFORM, const std::vector<std::string>& buttons = {}, 
		std::vector<E_Choice> choices = {});
	Popup();
	Popup(const std::string& mainText, Dino* dino);
	~Popup();

	PopupType type()
	{
		return _meaning;
	}

	void draw(sf::RenderWindow* window);

	void handleKeyPressedEvent(sf::Keyboard::Scancode code);
	virtual int handleKeyReleasedEvent(sf::Keyboard::Scancode code);
	void handleMouseButtonPressedEvent(int mouseX, int mouseY);
	virtual int handleMouseButtonReleasedEvent(int mouseX, int mouseY);
	void handleMouseMovedEvent(sf::Event::MouseMoveEvent event);
	
protected:
	sf::Vector2f _size{ sf::Vector2f(200, 100) };
	sf::Text _mainText;
	std::vector<Button*> _buttons;
	sf::Text _clueText;
	sf::RectangleShape _bg;
	sf::RectangleShape _body;
	int _activeIndex{ 0 };
	PopupType _meaning{ P_INFORM };
	Dino* _dino{ nullptr };
	
	void changeFocusedButton(int newIndex);
};