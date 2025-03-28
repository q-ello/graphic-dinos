#include "ShopScreen.h"

void ShopScreen::setScreenData()
{
	const int textSize = 25;
	_updateBtn = Button(40, "U - Update Shop", C_DARK_GREEN, sf::Vector2f(600, 700));

	updateShop();
}

void ShopScreen::drawData()
{
	for (auto& card : _shopList)
	{
		card.draw(_window);
	}
	_updateBtn.draw(_window);
	_window->draw(_moneyText);
	_returnBtn.draw(_window);
}

void ShopScreen::updateShop()
{
	const int textSize = 40;
	const float xPos = 50;
	const float yPos = 100;
	const float xOffset = 300;
	const float yOffset = 300;

	_shopList.clear();
	for (int i = 0; i < 6; i++)
	{
		sf::Vector2f position = sf::Vector2f(static_cast<float>(xPos + xOffset * (i % 3)),
			static_cast<float>(yPos + yOffset * std::floor(i / 3)));
		_shopList.push_back(DinoCard(textSize, "BUY", C_DARK_GREEN, position, C_BUY, 
			Dino::generateDino(), i == _activeIndex));
	}

	_updateBtn.toggleFocus(false);
}

void ShopScreen::handleKeyPressedEvent(sf::Keyboard::Scancode code)
{
	if (Utils::keyIsArrow(code))
	{
		changeFocusedButton(Utils::handleArrows(code), true);
		return;
	}

	if (code == sf::Keyboard::Scancode::Enter)
	{
		_shopList[_activeIndex].toggleAlmostExecuted(true);
		return;
	}

	if (code == sf::Keyboard::Scancode::U)
	{
		_updateBtn.toggleAlmostExecuted(true);
		return;
	}

	ScreenBase::handleKeyPressedEvent(code);
}

void ShopScreen::handleKeyReleasedEvent(sf::Keyboard::Scancode code)
{
	if (code == sf::Keyboard::Scancode::Enter)
	{
		showBuyPopup();
		return;
	}

	if (code == sf::Keyboard::Scancode::U)
	{
		updateShop();
		return;
	}

	ScreenBase::handleKeyReleasedEvent(code);
}

void ShopScreen::handleMouseButtonPressedEvent(sf::Event::MouseButtonEvent button)
{
	for (int i = 0; i < 6; i++)
	{
		if (!_shopList[i].isSold())
		{
			if (_shopList[i].handleMousePressed(button.x, button.y))
			{
				return;
			}
		}
	}
	if (_updateBtn.handleMousePressed(button.x, button.y))
	{
		return;
	}
	ScreenBase::handleMouseButtonPressedEvent(button);
}

void ShopScreen::handleMouseButtonReleasedEvent(sf::Event::MouseButtonEvent button)
{
	for (int i = 0; i < 6; i++)
	{
		if (_shopList[i].handleMouseReleased(button.x, button.y))
			{
				showBuyPopup();
			}
	}
	if (_updateBtn.handleMouseReleased(button.x, button.y))
	{
		updateShop();
	}
	ScreenBase::handleMouseButtonReleasedEvent(button);
}

void ShopScreen::handleMouseMovedEvent(sf::Event::MouseMoveEvent moveEvent)
{
	for (int i = 0; i < 6; i++)
	{
		if (!_shopList[i].isSold() && _shopList[i].handleMouseMovement(moveEvent.x, moveEvent.y))
		{
			changeFocusedButton({ i, 0 }, false);
			return;
		}
	}
}

void ShopScreen::setNewActiveIndex(std::pair<int, int> direction)
{
	_activeIndex = (direction.first + direction.second * 3 + _activeIndex + 6) % 6;
	
	bool everythingSoldOut = true;
	for (auto& button : _shopList)
	{
		if (!button.isSold())
		{
			everythingSoldOut = false;
			break;
		}
	}

	if (everythingSoldOut)
	{
		updateShop();
		return;
	}

	if (_shopList[_activeIndex].isSold())
	{
		setNewActiveIndex(direction);
	}
}

void ShopScreen::changeFocusedButton(std::pair<int, int> index, bool withArrows)
{
	_shopList[_activeIndex].toggleFocus(false);
	if (withArrows)
	{
		setNewActiveIndex(index);
	}
	else
	{
		_activeIndex = index.first;
	}
	_shopList[_activeIndex].toggleFocus(true);
}

void ShopScreen::handleDiffPopupChoice(int choice)
{
	if (_popup->type() == P_BUY)
	{
		switch (choice)
		{
		case C_YES:
			int dinoCost = _shopList[_activeIndex].dinoCost();
			if (Player::money() >= dinoCost)
			{
				Player::addCash(-1 * dinoCost);
				Player::addDino(std::move(_shopList[_activeIndex].dino()));
				const std::string dinoName = _shopList[_activeIndex].dinoName();
				_popup = std::make_unique<Popup>(Popup("You successfully\nbought " + dinoName + "!"));
				_shopList[_activeIndex].buyDino();
				changeFocusedButton({ 1, 0 });
				setMoneyData();
			}
			else
			{
				_popup = std::make_unique<Popup>(Popup("You do not have\nenough money."));
			}
			
		}
	}
}

void ShopScreen::showBuyPopup()
{
	const std::string dinoName = _shopList[_activeIndex].dinoName();
	const int dinoCost = _shopList[_activeIndex].dinoCost();
	_popup = std::make_unique<Popup>(Popup("Do you want to\nbuy " + dinoName + " for " + std::to_string(dinoCost) + "?",
		P_BUY, { "YES", "NO" }, { C_YES, C_NO }));
}
