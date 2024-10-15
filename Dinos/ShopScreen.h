#pragma once

#include "./stdafx.h"
#include "Dino.h"
#include "ScreenBase.h"
#include "DinoCard.h"

class ShopScreen : public ScreenBase
{
public:
    using ScreenBase::ScreenBase;
private:
    void setScreenData() override;
    void drawData() override;

    void updateShop();
    std::vector<DinoCard> _shopList;
    Button _updateBtn;
    int _activeIndex{ 0 };

    void handleKeyPressedEvent(sf::Keyboard::Scancode code) override;
    void handleKeyReleasedEvent(sf::Keyboard::Scancode code) override;
    void handleMouseButtonPressedEvent(sf::Event::MouseButtonEvent button) override;
    void handleMouseButtonReleasedEvent(sf::Event::MouseButtonEvent button) override;
    void handleMouseMovedEvent(sf::Event::MouseMoveEvent moveEvent) override;
    void setNewActiveIndex(std::pair<int, int> direction);

    void changeFocusedButton(std::pair<int, int> index, bool withArrows = true);
    void handleDiffPopupChoice(int choice) override;
    void showBuyPopup();
};
  