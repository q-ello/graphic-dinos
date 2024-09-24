#include "Utils.h"

sf::Text Utils::setText(int size, sf::Color color, 
	const std::string& string, sf::Vector2f position)
{
	sf::Text text;
	text.setCharacterSize(size);
	text.setFillColor(color);
	text.setString(string);
	text.setPosition(position);
	text.setFont(_font);
	return text;
}

sf::Text Utils::setText(int size, sf::Color color, const std::string& string)
{
	sf::Text text;
	text.setCharacterSize(size);
	text.setFillColor(color);
	text.setString(string);
	text.setFont(_font);
	return text;
}

sf::Text Utils::setClueText(sf::Color color)
{
	return Utils::setText(30, color, "Click or press any key to proceed.",
		sf::Vector2f(300, 700));
}

sf::RectangleShape Utils::setBG(sf::Color color)
{
	sf::RectangleShape bg;
	bg.setSize(SCREEN_SIZE);
	bg.setFillColor(color);
	bg.setPosition(sf::Vector2f(0, 0));
	return bg;
}

sf::RectangleShape Utils::setRect(sf::Vector2f size, sf::Color color, sf::Color outlineColor, 
	float thickness, sf::Vector2f position)
{
	sf::RectangleShape rect;
	rect.setSize(size);
	rect.setFillColor(color);
	rect.setOutlineColor(outlineColor);
	rect.setOutlineThickness(thickness);
	rect.setPosition(position);
	return rect;
}

sf::Font Utils::_font;