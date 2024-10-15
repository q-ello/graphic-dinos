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

	_buttons[0].emplace_back(new Button(textSize, "FIGHT", C_DARK_GREEN,
		sf::Vector2f(xOriginal, yOriginal), C_FIGHT, true));
	_buttons[0].emplace_back(new Button(textSize, "PARTY", C_DARK_GREEN,
		sf::Vector2f(xOriginal + xOffset, yOriginal), C_PARTY));
	_buttons[1].emplace_back(new Button(textSize, "SHOP", C_DARK_GREEN,
		sf::Vector2f(xOriginal, yOriginal + yOffset), C_SHOP));
	_buttons[1].emplace_back(new Button(textSize, "RESTING", C_DARK_GREEN,
		sf::Vector2f(xOriginal + xOffset, yOriginal + yOffset), C_RESTING));
	_buttons[2].emplace_back(new Button(textSize, "SAVE", C_DARK_GREEN,
		sf::Vector2f(xOriginal, yOriginal + 2 * yOffset), C_SAVE));
	_buttons[2].emplace_back(new LuckyDinoButton(textSize, "LUCKY DINO", C_DARK_GREEN,
		sf::Vector2f(xOriginal + xOffset, yOriginal + 2 * yOffset), C_LUCKY_DINO));
	_buttons[3].emplace_back(new Button(textSize, "QUIT", C_DARK_GREEN,
		sf::Vector2f(xOriginal, yOriginal + 3 * yOffset), C_QUIT));

	setDinosData();
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

	for (auto& dino : Player::party())
	{
		if (dino != nullptr)
		{
			dino->drawInMain(_window);
		}
	}

	for (auto& dino : Player::owned())
	{
		dino->drawInMain(_window);
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
			if (i == 2 && j == 1)
			{
				i = 2;
			}

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

void MainScreen::handlePopupChoice(int choice)
{
	if (_popup.get()->type() == P_LUCKY_DINO && choice == C_RETURN)
	{
		setDinosData();
	}

	ScreenBase::handlePopupChoice(choice);
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
		_popup = std::make_unique<Popup>(Popup("Your progress was\nsuccessfully saved."));
		break;
	case C_LUCKY_DINO:
	{
		std::shared_ptr<Dino> dino = Dino::generateDino();
		_popup = std::make_unique<Popup>(Popup("You got\na lucky dino!", dino));
		Player::addDino(std::move(dino));
		return;
	}
	case C_PARTY:
	{
		PartyScreen* partyScreen = new PartyScreen(_window);
		partyScreen->show();
		delete partyScreen;
		break;
	}
	case C_RESTING:
	{
		if (Player::owned().empty())
		{
			_popup = std::make_unique<Popup>(Popup("You have no resting dinos"));
			break;
		}
		RestingScreen* restingScreen = new RestingScreen(_window);
		restingScreen->show();
		delete restingScreen;
		break;
	}
	case C_FIGHT:
	{
		if (Player::partyIsEmpty())
		{
			_popup = std::make_unique<Popup>(Popup("You have no dinos\nin your party"));
			break;
		}
		FightWelcomeScreen* fight = new FightWelcomeScreen(_window);
		fight->show();
		delete fight;
		break;
	}
	case C_QUIT:
		handleCloseWindowEvent();
		break;
	}
	_buttons[_activeIndex.first][_activeIndex.second]->toggleAlmostExecuted(false);
	setDinosData();
	setMoneyData();
}

void MainScreen::setDinosData()
{
	const sf::Vector2f partyPosition{ 600, 250 };
	const float xDinoOffset = 50;
	const float yOffset = 100;
	auto party = Player::party();
	for (int i = 0; i < party.size(); i++)
	{
		if (party[i] == nullptr)
		{
			continue;
		}
		party[i]->setDataForMain({ partyPosition.x + xDinoOffset * i, partyPosition.y + 25 });

	}
	auto resting = Player::owned();
	for (int i = 0; i < resting.size(); i++)
	{
		resting[i]->setDataForMain({ partyPosition.x + xDinoOffset * i, partyPosition.y + yOffset + 25 });
	}
}
