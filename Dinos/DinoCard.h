#pragma once
#include "Button.h"
#include "Dino.h"

class DinoCard : public Button
{
public:
	using Button::Button;
	DinoCard(int textSize, const std::string& text, sf::Color color, sf::Vector2f position,
		int meaning, std::shared_ptr<Dino> dino, bool focused = false);

	~DinoCard()
	{
	}

	void draw(sf::RenderWindow* window) override;

	void toggleFocus(bool focus) override;
	void toggleAlmostExecuted(bool focus) override;

	std::string dinoName() const;
	int dinoCost();
	std::shared_ptr<Dino> dino()
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

	void setDino(std::shared_ptr<Dino> newDino);

private:
	std::shared_ptr<Dino> _dino;
	sf::RectangleShape _body;
	boolean _sold{ false };
	sf::Text _soldText;
	sf::RectangleShape _soldBody;

	sf::FloatRect getBounds() override;
};