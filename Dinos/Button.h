#pragma once

#include "stdafx.h"
#include "Utils.h"

class Button
{
public:
	Button(int textSize, const std::string& text, sf::Color color, sf::Vector2f position, 
		int meaning = 0, bool focused = false);

	Button();
	~Button() {};

	virtual void draw(sf::RenderWindow* window);
	bool handleMouseMovement(int mouseX, int mouseY);
	virtual void toggleFocus(bool focus);
	bool handleMousePressed(int mouseX, int mouseY);
	virtual void toggleAlmostExecuted(bool focus);
	bool handleMouseReleased(int mouseX, int mouseY);
	virtual bool checkCondition();

	int meaning()
	{
		return _meaning;
	}
protected:
	sf::Text _text;
	sf::Color _textColor;
	bool _focused;
	bool _almostExecuted{ false };
	int _meaning;
	virtual sf::FloatRect getBounds();
};