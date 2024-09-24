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
}

void MainScreen::handleKeyPressedEvent(sf::Keyboard::Scancode code)
{
	if (code == sf::Keyboard::Scan::Enter)
	{
		_buttons[_activeIndex.first][_activeIndex.second]->toggleAlmostExecuted(true);
		return;
	}

	const int arrHeight = 4;
	const int arrWidth = 2;

	std::pair<int, int> newActiveIndex = _activeIndex;
	if (code == sf::Keyboard::Scan::Left || code == sf::Keyboard::Scan::A)
	{
		newActiveIndex.second = (_activeIndex.second - 1 + arrWidth) % arrWidth;
	}
	else if (code == sf::Keyboard::Scan::Up || code == sf::Keyboard::Scan::W)
	{
		newActiveIndex.first = (_activeIndex.first - 1 + arrHeight) % arrHeight;
	}
	else if (code == sf::Keyboard::Scan::Right || code == sf::Keyboard::Scan::D)
	{
		newActiveIndex.second = (_activeIndex.second + 1) % arrWidth;
	}
	else if (code == sf::Keyboard::Scan::Down || code == sf::Keyboard::Scan::S)
	{
		newActiveIndex.first = (_activeIndex.first + 1) % arrHeight;
	}
	newActiveIndex.second %= _buttons[newActiveIndex.first].size();
	changeFocusedButton(newActiveIndex);
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
				changeFocusedButton({ i, j });
				return;
			}
		}
	}
}

void MainScreen::changeFocusedButton(std::pair<int, int> index)
{
	_buttons[_activeIndex.first][_activeIndex.second]->toggleFocus(false);
	_activeIndex = index;
	_buttons[_activeIndex.first][_activeIndex.second]->toggleFocus(true);
}

void MainScreen::changeState()
{
	E_Choice choice = _buttons[_activeIndex.first][_activeIndex.second]->meaning();
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
	case C_QUIT:
		handleCloseWindowEvent();
		break;
	}
}
