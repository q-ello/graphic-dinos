#include "Utils.h"

sf::Text Utils::setText(int size, sf::Color color, 
	const std::string& string, sf::Vector2f position)
{
	sf::Text text = Utils::setText(size, color, string);
	text.setPosition(position);
	return text;
}

sf::Text Utils::setText(int size, sf::Color color, const std::string& string)
{
	sf::Text text;
	text.setCharacterSize(size);
	text.setFillColor(color);
	text.setString(string);
	text.setFont(_font);
	text.setOutlineThickness(1);
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

sf::RectangleShape Utils::setBG(sf::Texture* texture)
{
	sf::RectangleShape bg;
	bg.setSize(SCREEN_SIZE);
	bg.setTexture(texture);
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

UINT Utils::frame()
{
	if (_clock.getElapsedTime().asMilliseconds() > 300)
	{
		_clock.restart();
		_frame++;
	}
	return _frame;
}

boolean Utils::keyIsArrow(sf::Keyboard::Scancode code)
{
	return code == sf::Keyboard::Scan::Left || code == sf::Keyboard::Scan::A
		|| code == sf::Keyboard::Scan::Up || code == sf::Keyboard::Scan::W
		|| code == sf::Keyboard::Scan::Right || code == sf::Keyboard::Scan::D
		|| code == sf::Keyboard::Scan::Down || code == sf::Keyboard::Scan::S;
}

std::pair<int, int> Utils::handleArrows(sf::Keyboard::Scancode code)
{
	std::pair direction{ 0, 0 };
	if (code == sf::Keyboard::Scan::Left || code == sf::Keyboard::Scan::A)
	{
		direction.first = -1;
	}
	else if (code == sf::Keyboard::Scan::Up || code == sf::Keyboard::Scan::W)
	{
		direction.second = -1;
	}
	else if (code == sf::Keyboard::Scan::Right || code == sf::Keyboard::Scan::D)
	{
		direction.first = 1;
	}
	else if (code == sf::Keyboard::Scan::Down || code == sf::Keyboard::Scan::S)
	{
		direction.second = 1;
	}
	return direction;
}

sf::Vector2f Utils::alignToCenter(sf::Text* text, sf::Vector2f space)
{
	const sf::Vector2f textSize = text->getLocalBounds().getSize();
	return alignToCenter(textSize, space);
}

sf::Vector2f Utils::alignToCenter(sf::Vector2f object, sf::Vector2f space)
{
	return { (space.x - object.x) / 2, (space.y - object.y) / 2 };
}

sf::Font Utils::_font;
sf::Clock Utils::_clock;
UINT Utils::_frame = 0;