#pragma once
#include "stdafx.h"
#include "Button.h"

enum PopupType
{
	P_SAVE,
	P_INFORM,
	P_BUY,
	P_CHANGE
};

class Popup
{
public:
	Popup(const std::string& mainText, PopupType type = P_INFORM, const std::vector<std::string>& buttons = {}, 
		std::vector<E_Choice> choices = {});
	~Popup();

	PopupType type()
	{
		return _meaning;
	}

	void draw(sf::RenderWindow* window);

	void handleKeyPressedEvent(sf::Keyboard::Scancode code);
	E_Choice handleKeyReleasedEvent(sf::Keyboard::Scancode code);
	void handleMouseButtonPressedEvent(int mouseX, int mouseY);
	E_Choice handleMouseButtonReleasedEvent(int mouseX, int mouseY);
	void handleMouseMovedEvent(int mouseX, int mouseY);
	
private:
	sf::Vector2f _size{ sf::Vector2f(200, 100) };
	sf::Text _mainText;
	std::vector<Button*> _buttons;
	sf::Text _clueText;
	sf::RectangleShape _bg;
	sf::RectangleShape _body;
	int _activeIndex{ 0 };
	PopupType _meaning;
	
	void changeFocusedButton(int newIndex);
};