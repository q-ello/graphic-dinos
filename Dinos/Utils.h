#pragma once

#include "stdafx.h"

class Utils
{
public:
	static sf::Text setText(int size, sf::Color color,
		const std::string& string, sf::Vector2f position);

	static sf::Text setText(int size, sf::Color color,
		const std::string& string);

	static sf::Text setClueText(sf::Color color);

	static sf::RectangleShape setBG(sf::Color color);
	static sf::RectangleShape setBG(sf::Texture* texture);

	static sf::RectangleShape setRect(sf::Vector2f size, sf::Color color, sf::Color outlineColor,
		float thickness, sf::Vector2f position);

	static void loadFont()
	{
		_font.loadFromFile("./font/lunchds.ttf");
	}

	static UINT frame();

	static boolean keyIsArrow(sf::Keyboard::Scancode code);

	static std::pair<int, int> handleArrows(sf::Keyboard::Scancode code);

private:
	static sf::Font _font;
	static sf::Clock _clock;
	static UINT _frame;
};