#include "RestingScreen.h"

void RestingScreen::setScreenData()
{
	const float xPos = 50;
	const float yPos = 100;
	const float xOffset = 300;
	const float yOffset = 300;
	std::vector<std::shared_ptr<Dino>> resting = Player::owned();
	if (resting.size() > 6)
	{
		resting.resize(6);
	}
	for (int i = 0; i < resting.size(); i++)
	{
		sf::Vector2f position{ xPos + xOffset * (i % 3), static_cast<float>(yPos + yOffset * std::floor(i / 3)) };
		_dinos.push_back(DinoCard(30, "ADD TO PARTY", C_DARK_GREEN, position, C_CHANGE, 
			std::move(resting[i]), i == _activeIndex));
	}
}

void RestingScreen::setNewActiveIndex(std::pair<int, int> direction)
{
	_activeIndex = (direction.first + direction.second * 3 + _activeIndex + _dinos.size()) 
		% static_cast<int>(_dinos.size());
}

void RestingScreen::handleDiffPopupChoice(int choice)
{
	Player::changeDino(choice, _activeIndex);
	_popup = std::make_unique<Popup>(Popup("Dino was successfully\nadded to party"));
	updateDinoCards();
}

void RestingScreen::changeDino()
{
	_popup = std::make_unique<Popup>(DinoPopup(true));
}

void RestingScreen::updateDinoCards()
{
	auto resting = Player::owned();
	for (int i = 0; i < resting.size(); i++)
	{
		_dinos[i].setDino(resting[i]);
	}
	if (_dinos.size() > resting.size())
	{
		_dinos.pop_back();
	}
}
