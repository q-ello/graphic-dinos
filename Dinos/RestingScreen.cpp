#include "RestingScreen.h"

void RestingScreen::setScreenData()
{
	const int xPos = 50;
	const int yPos = 100;
	const int xOffset = 300;
	const int yOffset = 300;
	std::vector<Dino*> resting = Player::owned();
	if (resting.size() > 6)
	{
		resting.resize(6);
	}
	for (int i = 0; i < resting.size(); i++)
	{
		sf::Vector2f position = sf::Vector2f(xPos + xOffset * (i % 3),
			yPos + yOffset * std::floor(i / 3));
		_dinos.push_back(new DinoCard(30, "ADD TO PARTY", C_DARK_GREEN, position, C_CHANGE, 
			std::move(resting[i]), i == _activeIndex));
	}
}

void RestingScreen::setNewActiveIndex(std::pair<int, int> direction)
{
	_activeIndex = (direction.first + direction.second * 3 + _activeIndex + _dinos.size()) 
		% _dinos.size();
}

void RestingScreen::handleDiffPopupChoice(int choice)
{
	Player::changeDino(choice, _activeIndex);
	_popup = new Popup("Dino was successfully\nadded to party");
	updateDinoCards();
}

void RestingScreen::changeDino()
{
	_popup = new DinoPopup(true);
}

void RestingScreen::updateDinoCards()
{
	std::vector<Dino*> resting = Player::owned();
	for (int i = 0; i < resting.size(); i++)
	{
		_dinos[i]->setDino(resting[i]);
	}

	if (_dinos.size() > resting.size())
	{
		_dinos.pop_back();
	}
}
