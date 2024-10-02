#include "DinoCard.h"

DinoCard::DinoCard(int textSize, const std::string& text, sf::Color color, sf::Vector2f position, 
	int meaning, Dino* dino, bool focused)
	: Button(textSize, text, color, position, meaning, focused)
	, _dino {dino}
{
	_body.setSize(DINOCARD_SIZE);
	_body.setPosition(position);
	_body.setFillColor(focused ? C_ALMOST_TRANSPARENT : C_TRANSPARENT);
	const sf::Vector2f textBodySize = _text.getLocalBounds().getSize();
	sf::Vector2f textPosition = sf::Vector2f(position.x + (DINOCARD_SIZE.x - textBodySize.x) / 2, 
		position.y + 210);
	_text.setPosition(textPosition);

	sf::Vector2f dinoPosition = sf::Vector2f(position.x + 5, position.y + 50);
	if (_dino != nullptr) {
		_dino->setDataForDrawing(dinoPosition);
	}

	_soldBody.setSize(DINOCARD_SIZE);
	_soldBody.setPosition(position);
	_soldBody.setFillColor(C_ALMOST_TRANSPARENT);
	_soldText = Utils::setText(60, C_DULL_GREEN, "SOLD", 
		sf::Vector2f(position.x + 70, position.y + 50));
	_soldText.rotate(45);
}

void DinoCard::draw(sf::RenderWindow* window)
{
	window->draw(_body);
	Button::draw(window);
	if (_dino != nullptr)
	{
		switch (_meaning) {
		case C_BUY:
			_dino->drawForShop(window);
			break;
		case C_CHANGE:
			_dino->drawInParty(window);
		}
	}
	if (_sold)
	{
		window->draw(_soldBody);
		window->draw(_soldText);
	}
}

void DinoCard::toggleFocus(bool focus)
{
	_body.setFillColor(focus ? C_ALMOST_TRANSPARENT : C_TRANSPARENT);
	Button::toggleFocus(focus);
}

void DinoCard::toggleAlmostExecuted(bool focus)
{
	_body.setFillColor(focus ? C_SEMITRANSPARENT : _focused ? C_ALMOST_TRANSPARENT : C_TRANSPARENT);
	Button::toggleAlmostExecuted(focus);
}

int DinoCard::dinoCost()
{
	return _dino->cost();
}

std::string DinoCard::dinoName() const
{
	return _dino->name();
}

sf::FloatRect DinoCard::getBounds()
{
	return _body.getGlobalBounds();
}
