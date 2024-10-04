#include "PartyScreen.h"

PartyScreen::~PartyScreen()
{
	_dinos.clear();
}

void PartyScreen::setScreenData()
{

	const int xPos = 80;
	const int yPos = 240;
	const int xOffset = 300;
	std::vector<Dino*> party = Player::party();
	for (int i = 0; i < party.size(); i++)
	{
		sf::Vector2f dinoPosition = sf::Vector2f(xPos + xOffset * i, yPos);
		_dinos.push_back(new DinoCard(30, "CHANGE", C_DARK_GREEN, dinoPosition, C_CHANGE, std::move(party[i]), i == _activeIndex));
	}
}

void PartyScreen::drawData()
{
	for (auto& card : _dinos)
	{
		card->draw(_window);
	}
	_window->draw(_moneyText);
	_returnBtn->draw(_window);
}

void PartyScreen::handleKeyPressedEvent(sf::Keyboard::Scancode code)
{
	if (Utils::keyIsArrow(code))
	{
		changeFocusedButton(Utils::handleArrows(code), true);
		return;
	}

	if (code == sf::Keyboard::Scancode::Enter)
	{
		_dinos[_activeIndex]->toggleAlmostExecuted(true);
		return;
	}

	ScreenBase::handleKeyPressedEvent(code);
}

void PartyScreen::handleKeyReleasedEvent(sf::Keyboard::Scancode code)
{
	if (code == sf::Keyboard::Scancode::Enter)
	{
		changeDino();
		return;
	}

	ScreenBase::handleKeyReleasedEvent(code);
}

void PartyScreen::handleMouseButtonPressedEvent(sf::Event::MouseButtonEvent button)
{
	for (int i = 0; i < _dinos.size(); i++)
	{
		if (_dinos[i]->handleMousePressed(button.x, button.y))
			{
				return;
			}
	}
	ScreenBase::handleMouseButtonPressedEvent(button);
}

void PartyScreen::handleMouseButtonReleasedEvent(sf::Event::MouseButtonEvent button)
{
	for (int i = 0; i < 3; i++)
	{
		if (_dinos[i]->handleMouseReleased(button.x, button.y))
		{
			changeDino();
			return;
		}
	}
	ScreenBase::handleMouseButtonReleasedEvent(button);
}

void PartyScreen::handleMouseMovedEvent(sf::Event::MouseMoveEvent moveEvent)
{
	for (int i = 0; i < 3; i++)
	{
		if (_dinos[i]->handleMouseMovement(moveEvent.x, moveEvent.y))
		{
			changeFocusedButton({ i, 0 }, false);
			return;
		}
	}
}

void PartyScreen::setNewActiveIndex(std::pair<int, int> direction)
{
	_activeIndex = (direction.first + _activeIndex + 3) % 3;
}

void PartyScreen::handleDiffPopupChoice(int choice)
{
	Player::changeDino(_activeIndex, choice);
	_popup = new Popup("Dino was successfully changed");
	updateDinoCards();
}

void PartyScreen::changeFocusedButton(std::pair<int, int> index, bool withArrows)
{
	_dinos[_activeIndex]->toggleFocus(false);
	if (withArrows)
	{
		setNewActiveIndex(index);
	}
	else
	{
		_activeIndex = index.first;
	}
	_dinos[_activeIndex]->toggleFocus(true);
}

void PartyScreen::changeDino()
{
	if (Player::owned().empty())
	{
		_popup = new Popup("You have no\nresting dinos.");
		return;
	}
	else
	{
		_popup = new DinoPopup(false);
	}
}

void PartyScreen::updateDinoCards()
{
	std::vector<Dino*> party = Player::party();
	for (int i = 0; i < 3; i++)
	{
		_dinos[i]->setDino(party[i]);
	}
}
