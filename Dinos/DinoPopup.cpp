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
        dinos = Player::owned();
        if (dinos.size() > 6)
        {
            dinos.resize(6);
        }
    }

    _bg = Utils::setBG(C_SEMITRANSPARENT);
    _clueText = Utils::setClueText(C_DARK_GREEN);
    sf::Vector2f size = sf::Vector2f(975, 775);
    sf::Vector2f bodyPos = sf::Vector2f((SCREEN_SIZE.x - size.x) / 2,
        (SCREEN_SIZE.y - size.y) / 2);

    const int textSize = 40;
    const int xPos = 50;
    const int yPos = isParty ? 240 : 100;
    const int xOffset = 300;
    const int yOffset = 300;

    for (int i = 0; i < dinos.size(); i++)
    {
        sf::Vector2f dinoPos = sf::Vector2f(static_cast<float>(xPos + xOffset * (i % 3)),
            static_cast<float>(yPos + yOffset * std::floor(i / 3)));
        _buttons.push_back(new DinoCard(20, "REPLACE", C_DARK_GREEN, dinoPos, i, i == 0));
    }

    _mainText = Utils::setText(40, C_DARK_GREEN, "Choose Dino");

}