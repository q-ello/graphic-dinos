#include "ScreenBase.h"

ScreenBase::ScreenBase(sf::RenderWindow* window)
	: _window {window}
	, _popup {nullptr}
{
	_money = Player::money();
	_moneyText = Utils::setText(40, C_BRIGHT_GREEN, "MONEY: " + std::to_string(_money), 
		sf::Vector2f(750, 50));
}

void ScreenBase::show()
{
	sf::Event event;

	createBG();
	setScreenData();
	setMoneyData();

	while (true)
	{
		while (_window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::EventType::Closed:
			{
				handleCloseWindowEvent();
				break;
			}
			case sf::Event::EventType::KeyPressed:
				if (_popup != nullptr)
				{
					_popup->handleKeyPressedEvent(event.key.scancode);
				}
				else
				{
					handleKeyPressedEvent(event.key.scancode);
				}
				break;
			case sf::Event::EventType::KeyReleased:
				if (_popup != nullptr)
				{
					E_Choice choice = _popup->handleKeyReleasedEvent(event.key.scancode);
					handlePopupChoice(choice);
				}
				else
				{
					handleKeyReleasedEvent(event.key.scancode);
				}
				break;
			case sf::Event::EventType::MouseButtonPressed:
				if (_popup != nullptr)
				{
					_popup->handleMouseButtonPressedEvent(event.mouseButton.x, event.mouseButton.y);
				}
				else
				{
					handleMouseButtonPressedEvent(event.mouseButton);
				}
				break;
			case sf::Event::EventType::MouseButtonReleased:
				if (_popup != nullptr)
				{
					E_Choice choice = _popup->handleMouseButtonReleasedEvent(event.mouseButton.x, 
						event.mouseButton.y);
					handlePopupChoice(choice);
				}
				else
				{
					handleMouseButtonReleasedEvent(event.mouseButton);
				}
				break;
			case sf::Event::EventType::MouseMoved:
				if (_popup != nullptr)
				{
					_popup->handleMouseMovedEvent(event.mouseButton.x,
						event.mouseButton.y);
				}
				else
				{
					handleMouseMovedEvent(event.mouseMove);
				}
				break;
			default:
				break;
			}

			_window->clear();
		}

		drawBG();
		drawData();

		if (_popup != nullptr)
		{
			_popup->draw(_window);
		}

		_window->display();

		if (!_window->isOpen())
			return;
	}
	return;
}

void ScreenBase::setMoneyData()
{
	int playerMoney = Player::money();
	if (_money != playerMoney)
	{
		int dir = (playerMoney > _money) - (playerMoney < _money);
		_money += dir;
		_moneyText.setString("MONEY: " + std::to_string(_money));
	}
}

void ScreenBase::handleKeyPressedEvent(sf::Keyboard::Scancode code)
{
}

void ScreenBase::handleKeyReleasedEvent(sf::Keyboard::Scancode code)
{
}

void ScreenBase::handleMouseButtonPressedEvent(sf::Event::MouseButtonEvent button)
{
}

void ScreenBase::handleMouseButtonReleasedEvent(sf::Event::MouseButtonEvent button)
{
}

void ScreenBase::handleMouseMovedEvent(sf::Event::MouseMoveEvent moveEvent)
{
}

void ScreenBase::handleCloseWindowEvent()
{
	if (_popup != nullptr && _popup->type() == P_SAVE)
	{
		_window->close();
		return;
	}
	_popup = new Popup("Do you want to\nsave your data?", P_SAVE, std::vector<std::string>{"YES", "NO"}, 
		std::vector<E_Choice>{C_YES, C_NO});
	return;
}

void ScreenBase::createBG()
{
	_bg = Utils::setBG(C_DULL_GREEN);
}

void ScreenBase::drawBG()
{
	_window->draw(_bg);
}

void ScreenBase::handlePopupChoice(E_Choice choice)
{
	switch (choice)
	{
	case C_NOTHING:
		return;
	case C_RETURN:
		_popup = nullptr;
		return;
	case C_YES:
		if (_popup->type() == P_SAVE)
		{
			Player::save();
			_window->close();
		}
		break;
	case C_NO:
		if (_popup->type() == P_SAVE)
		{
			_window->close();
		}
		else
		{
			_popup = nullptr;
		}
		return;
	}
	
	handleDiffPopupChoice(choice);
}

void ScreenBase::handleDiffPopupChoice(E_Choice choice)
{
}
