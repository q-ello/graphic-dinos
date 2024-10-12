#pragma once
#include "Button.h"
#include "Dino.h"

class DinoCard : public Button
{
public:
	using Button::Button;
	DinoCard(int textSize, const std::string& text, sf::Color color, sf::Vector2f position,
		int meaning, Dino* dino, bool focused = false);

	void draw(sf::RenderWindow* window) override;

	void toggleFocus(bool focus) override;
	void toggleAlmostExecuted(bool focus) override;

	std::string dinoName() const;
	int dinoCost();
	Dino* dino()
	{
		return _dino;
	}

	boolean isSold()
	{
		return _sold;
	}

	void buyDino()
	{
		_sold = true;
		toggleFocus(false);
	}

	void setDino(Dino* newDino);

private:
	Dino* _dino;
	sf::RectangleShape _body;
	boolean _sold{ false };
	sf::Text _soldText;
	sf::RectangleShape _soldBody;

	sf::FloatRect getBounds() override;
};