#pragma once

#include "stdafx.h"
#include "Utils.h"

class Button
{
public:
	Button(int textSize, const std::string& text, sf::Color color, sf::Vector2f position, 
		E_Choice meaning, bool focused = false);
	~Button() {};

	void draw(sf::RenderWindow* window);
	bool handleMouseMovement(int mouseX, int mouseY);
	void toggleFocus(bool focus);
	bool handleMousePressed(int mouseX, int mouseY);
	void toggleAlmostExecuted(bool focus);
	bool handleMouseReleased(int mouseX, int mouseY);

	E_Choice meaning()
	{
		return _meaning;
	}
private:
	sf::Text _text;
	sf::Color _textColor;
	bool _focused;
	bool _almostExecuted{ false };
	E_Choice _meaning;
};