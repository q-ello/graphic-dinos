#include "DinoPopup.h"

DinoPopup::DinoPopup(boolean isParty)
{
    std::vector<Dino*> dinos;
    if (isParty)
    {
        dinos = Player::party();
    }
    else
    {
        dinos = (Player::owned());
        if (dinos.size() > 6)
        {
            dinos.resize(6);
        }
    }

    _bg = Utils::setBG(C_SEMITRANSPARENT);
    _clueText = Utils::setClueText(C_DARK_GREEN);
    sf::Vector2f size = sf::Vector2f(950, 750);
    sf::Vector2f bodyPos = Utils::alignToCenter(size);
    _body = Utils::setRect(size, C_DULL_GREEN, C_DARK_GREEN, 4, bodyPos);

    const int textSize = 40;
    const int xPos = 50;
    const int yPos = isParty ? 240 : 100;
    const int xOffset = 300;
    const int yOffset = 300;

    for (int i = 0; i < dinos.size(); i++)
    {
        sf::Vector2f dinoPos = sf::Vector2f(static_cast<float>(xPos + xOffset * (i % 3)),
            static_cast<float>(yPos + yOffset * std::floor(i / 3)));
        _buttons.push_back(new DinoCard(20, "REPLACE", C_DARK_GREEN, dinoPos, i, dinos[i], i == 0));
    }

    _mainText = Utils::setText(40, C_DARK_GREEN, "Choose Dino");

    _mainText.setPosition(bodyPos.x + Utils::alignToCenter(&_mainText, size).x, bodyPos.y + 5);
}