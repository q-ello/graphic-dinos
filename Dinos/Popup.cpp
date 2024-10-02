#include "Popup.h"

Popup::Popup(const std::string& mainText, PopupType type, const std::vector<std::string>& buttons, 
	std::vector<E_Choice> choices)
	: _meaning {type}
{
	_mainText = Utils::setText(40, C_DARK_GREEN, mainText);
	_bg = Utils::setBG(C_SEMITRANSPARENT);
	_clueText = Utils::setClueText(C_DARK_GREEN);

	sf::Vector2f size = _mainText.getLocalBounds().getSize();
	sf::Vector2f bodySize = sf::Vector2f(size.x + 20, size.y + 20);
	sf::Vector2f bodyPos = sf::Vector2f((SCREEN_SIZE.x - bodySize.x) / 2,
		(SCREEN_SIZE.y - bodySize.y) / 2);
	
	if (!buttons.empty())
	{
		bodySize.y += 25;

		const sf::Vector2f buttonPos = sf::Vector2f(bodyPos.x + 10, bodyPos.y + bodySize.y - 30);
		const int buttonOffset = 50;

		for (int i = 0; i < buttons.size(); i++)
		{
			_buttons.push_back(new Button(20, buttons[i], C_DARK_GREEN,
				sf::Vector2f(buttonPos.x + buttonOffset * i, buttonPos.y), choices[i], i == 0));
		}
	}

	_body = Utils::setRect(bodySize, C_DULL_GREEN, C_DARK_GREEN, 3, bodyPos);
	_mainText.setPosition(sf::Vector2f(bodyPos.x + 10,
		bodyPos.y + 5));
}

Popup::Popup()
	: _meaning {P_INFORM}
{
}

Popup::~Popup()
{
	_buttons.clear();
}

void Popup::draw(sf::RenderWindow* window)
{
	window->draw(_bg);
	window->draw(_body);
	window->draw(_clueText);
	window->draw(_mainText);
	for (auto& button : _buttons)
	{
		button->draw(std::move(window));
	}
}

void Popup::handleKeyPressedEvent(sf::Keyboard::Scancode code)
{
	if (!_buttons.empty())
	{
		const int btnsSize = static_cast<int>(_buttons.size());
		if (code == sf::Keyboard::Scan::A || code == sf::Keyboard::Scan::Left)
		{
			changeFocusedButton((_activeIndex - 1 + btnsSize) % btnsSize);
			return;
		}
		if (code == sf::Keyboard::Scan::D || code == sf::Keyboard::Scan::Right)
		{
			changeFocusedButton((_activeIndex + 1) % btnsSize);
			return;
		}
		if (code == sf::Keyboard::Scan::Enter)
		{
			_buttons[_activeIndex]->toggleAlmostExecuted(true);
			return;
		}
	}
}

int Popup::handleKeyReleasedEvent(sf::Keyboard::Scancode code)
{
	if (_buttons.empty())
	{
		return C_RETURN;
	}
	if (code == sf::Keyboard::Scancode::Enter)
	{
		return _buttons[_activeIndex]->meaning();
	}
	if (code == sf::Keyboard::Scancode::Escape)
	{
		return C_RETURN;
	}
	return C_NOTHING;
}

void Popup::handleMouseButtonPressedEvent(int mouseX, int mouseY)
{
	for (auto& button : _buttons)
	{
		if (button->handleMousePressed(mouseX, mouseY))
		{
			return;
		}
	}
}

int Popup::handleMouseButtonReleasedEvent(int mouseX, int mouseY)
{
	for (int i = 0; i < _buttons.size(); i++)
	{
		if (_buttons[i]->handleMouseReleased(mouseX, mouseY))
		{
			return _buttons[i]->meaning();
		}
	}

	if (!_body.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(mouseX), 
		static_cast<float>(mouseY))))
	{
		return C_RETURN;
	}

	return C_NOTHING;
}

void Popup::handleMouseMovedEvent(int mouseX, int mouseY)
{
	for (int i = 0; i < _buttons.size(); i++)
	{
		if (_buttons[i]->handleMouseMovement(mouseX, mouseY))
		{
			changeFocusedButton(i);
			return;
		}
	}
}

void Popup::changeFocusedButton(int newIndex)
{
	_buttons[_activeIndex]->toggleFocus(false);
	_activeIndex = newIndex;
	_buttons[_activeIndex]->toggleFocus(true);
}
