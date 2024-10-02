#include "Button.h"

Button::Button(int textSize, const std::string& text, sf::Color color, sf::Vector2f position, 
	int meaning, bool focused)
	: _textColor{ color }
	, _focused{ focused }
	, _meaning {meaning}
{
	_text = Utils::setText(textSize, focused ? C_FOCUSED : color, text, position);
}

Button::Button()
	: _focused {false}
	, _meaning {C_NOTHING}
{
}

void Button::draw(sf::RenderWindow* window)
{
	if (!checkCondition())
	{
		return;
	}
	window->draw(_text);
}

void Button::toggleFocus(bool focus)
{
	_text.setFillColor(focus ? C_FOCUSED : _textColor);
	_focused = focus;
	if (!_focused)
	{
		_almostExecuted = false;
	}
}

bool Button::handleMouseMovement(int mouseX, int mouseY)
{
	if (!checkCondition())
	{
		return false;
	}

	if (_focused != getBounds().contains(sf::Vector2f(static_cast<float>(mouseX),
		static_cast<float>(mouseY))))
	{
		if (!_focused)
		{
			toggleFocus(true);
			return true;
		}
		
		if (_almostExecuted)
		{
			toggleAlmostExecuted(false);
		}
	}
	return false;
}

bool Button::handleMousePressed(int mouseX, int mouseY)
{
	if (!checkCondition())
	{
		return false;
	}
	if (_almostExecuted != getBounds().contains(sf::Vector2f(static_cast<float>(mouseX),
		static_cast<float>(mouseY))))
	{
		if (!_almostExecuted)
		{
			toggleAlmostExecuted(true);
			return true;
		}
	}
	return false;
}

void Button::toggleAlmostExecuted(bool focus)
{
	_text.setFillColor(focus ? C_EXECUTABLE : _focused ? C_FOCUSED : _textColor);
	_almostExecuted = focus;
}

bool Button::handleMouseReleased(int mouseX, int mouseY)
{
	if (_almostExecuted && getBounds().contains(sf::Vector2f(static_cast<float>(mouseX),
		static_cast<float>(mouseY))))
	{
		return true;
	}
	return false;
}

bool Button::checkCondition()
{
	return true;
}

sf::FloatRect Button::getBounds()
{
	return _text.getGlobalBounds();
}
