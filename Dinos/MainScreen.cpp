#include "MainScreen.h"

MainScreen::~MainScreen()
{
	for (auto vec : _buttons)
	{
		vec.clear();
	}
	_buttons.clear();
}

void MainScreen::setScreenData()
{
	const int textSize = 40;
	const int xOriginal = 40;
	const int yOriginal = 250;
	const int xOffset = 350;
	const int yOffset = 100;

	

	_buttons[0].push_back(new Button(textSize, "FIGHT", C_DARK_GREEN,
		sf::Vector2f(xOriginal, yOriginal), C_FIGHT, true));
	_buttons[0].push_back(new Button(textSize, "PARTY", C_DARK_GREEN,
		sf::Vector2f(xOriginal + xOffset, yOriginal), C_PARTY));
	_buttons[1].push_back(new Button(textSize, "SHOP", C_DARK_GREEN,
		sf::Vector2f(xOriginal, yOriginal + yOffset), C_SHOP));
	_buttons[1].push_back(new Button(textSize, "RESTING", C_DARK_GREEN,
		sf::Vector2f(xOriginal + xOffset, yOriginal + yOffset), C_RESTING));
	_buttons[2].push_back(new Button(textSize, "SAVE", C_DARK_GREEN,
		sf::Vector2f(xOriginal, yOriginal + 2 * yOffset), C_SAVE));
	_buttons[2].push_back(new LuckyDinoButton(textSize, "LUCKY DINO", C_DARK_GREEN,
		sf::Vector2f(xOriginal + xOffset, yOriginal + 2 * yOffset), C_LUCKY_DINO));
	_buttons[3].push_back(new Button(textSize, "QUIT", C_DARK_GREEN,
		sf::Vector2f(xOriginal, yOriginal + 3 * yOffset), C_QUIT));
}

void MainScreen::drawData()
{
	for (auto vec : _buttons)
	{
		for (auto button : vec)
		{
			button->draw(_window);
		}
	}
	
	_window->draw(_moneyText);

	const sf::Vector2f partyPosition = sf::Vector2f(550, 250);
	const int xDinoOffset = 50;
	const int yOffset = 100;
	std::vector<Dino*> party = Player::party();
	for (int i = 0; i < party.size(); i++)
	{
		if (party[i] == nullptr)
		{
			continue;
		}
		party[i]->drawInMain(_window, sf::Vector2f(partyPosition.x + xDinoOffset * i, partyPosition.y));

	}
	std::vector<Dino*> resting = Player::owned();
	for (int i = 0; i < resting.size(); i++)
	{
		resting[i]->drawInMain(_window, sf::Vector2f(partyPosition.x + xDinoOffset * i, partyPosition.y + yOffset));

	}
}

void MainScreen::handleKeyPressedEvent(sf::Keyboard::Scancode code)
{
	if (code == sf::Keyboard::Scan::Enter)
	{
		_buttons[_activeIndex.first][_activeIndex.second]->toggleAlmostExecuted(true);
		return;
	}

	if (Utils::keyIsArrow(code))
	{
		changeFocusedButton(Utils::handleArrows(code));
	}
}

void MainScreen::handleKeyReleasedEvent(sf::Keyboard::Scancode code)
{
	if (code == sf::Keyboard::Scan::Enter)
	{
		changeState();
	}
	if (code == sf::Keyboard::Scan::Escape)
	{
		handleCloseWindowEvent();
	}
}

void MainScreen::handleMouseButtonPressedEvent(sf::Event::MouseButtonEvent button)
{
	for (int i = 0; i < _buttons.size(); i++)
	{
		for (int j = 0; j < _buttons[i].size(); j++)
		{
			if (_buttons[i][j]->handleMousePressed(button.x, button.y))
			{
				return;
			}
		}
	}
}

void MainScreen::handleMouseButtonReleasedEvent(sf::Event::MouseButtonEvent button)
{
	for (int i = 0; i < _buttons.size(); i++)
	{
		for (int j = 0; j < _buttons[i].size(); j++)
		{
			if (_buttons[i][j]->handleMouseReleased(button.x, button.y))
			{
				changeState();
				return;
			}
		}
	}
}

void MainScreen::handleMouseMovedEvent(sf::Event::MouseMoveEvent moveEvent)
{
	for (int i = 0; i < _buttons.size(); i++)
	{
		for (int j = 0; j < _buttons[i].size(); j++)
		{
			if (_buttons[i][j]->handleMouseMovement(moveEvent.x, moveEvent.y))
			{
				changeFocusedButton({ i, j }, false);
				return;
			}
		}
	}
}

void MainScreen::setNewActiveIndex(std::pair<int, int> direction)
{
	const int arrWidth = static_cast<int>(_buttons[_activeIndex.first].size());
	const int arrHeight = static_cast<int>(_buttons.size());
	std::pair<int, int> newActiveIndex = _activeIndex;
	_activeIndex.second = (_activeIndex.second + direction.first + arrWidth) % arrWidth;
	_activeIndex.first = (_activeIndex.first + direction.second + arrHeight) % arrHeight;
	
	_activeIndex.second %= _buttons[_activeIndex.first].size();
	if (!_buttons[_activeIndex.first][_activeIndex.second]->checkCondition())
	{
		setNewActiveIndex({-1, 0});
	}
}

void MainScreen::changeFocusedButton(std::pair<int, int> direction, bool withArrows)
{
	_buttons[_activeIndex.first][_activeIndex.second]->toggleFocus(false);
	if (withArrows)
	{
		setNewActiveIndex(direction);
	}
	else
	{
		_activeIndex = direction;
	}
	_buttons[_activeIndex.first][_activeIndex.second]->toggleFocus(true);
}

void MainScreen::changeState()
{
	int choice = _buttons[_activeIndex.first][_activeIndex.second]->meaning();
	switch (choice)
	{
	case C_SHOP:
	{
		ShopScreen* shop = new ShopScreen(_window);
		shop->show();
		delete shop;
		break;
	}
	case C_SAVE:
		Player::save();
		_popup = new Popup("Your progress was\nsuccessfully saved.");
		return;
	case C_LUCKY_DINO:
	{
		Dino* dino = Dino::generateDino();
		_popup = new Popup("You got a lucky dino!");
		Player::addDino(std::move(dino));
		return;
	}
	case C_PARTY:
	{
		PartyScreen* partyScreen = new PartyScreen(_window);
		partyScreen->show();
		delete partyScreen;
		return;
	}
	case C_RESTING:
	{
		if (Player::owned().empty())
		{
			_popup = new Popup("You have no resting dinos");
			return;
		}
		RestingScreen* restingScreen = new RestingScreen(_window);
		restingScreen->show();
		delete restingScreen;
		return;
	}
	case C_QUIT:
		handleCloseWindowEvent();
		break;
	}
}
