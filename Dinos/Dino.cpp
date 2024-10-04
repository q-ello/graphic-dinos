#include "Dino.h"
#include <iostream>
#include <direct.h>

Dino::Dino(Terrain typ, EDinoName dinoName, int str, int dex, int intel)
    : _type{ typ }
    , _name{ dinoName }
    , _STR{ str }
    , _DEX{ dex }
    , _INT{ intel }
{
    _cost = rand() % 11 + 50;

    switch (dinoName)
    {
    case N_Tyranosaurus:
        _texture.loadFromFile("./images/Rex.png");
        break;
    case N_Tryceratops:
        _texture.loadFromFile("./images/Tri.png");
        break;
    case N_Brontozaurus:
        _texture.loadFromFile("./images/Bron.png");
        break;
    default:
        break;
    }

    _sprite.setTexture(_texture);
    const int textSize = 20;

    sf::Color typeColor;
    switch (_type)
    {
    case T_Mountain:
        typeColor = C_INT;
        break;
    case T_Plain:
        typeColor = C_STR;
        break;
    default:
        typeColor = C_DEX;
        break;
    }
    _nameText = Utils::setText(30, typeColor, name());

    _info.push_back(Utils::setText(textSize, C_DARK_GREEN, "STR: " + std::to_string(strength())));
    _info.push_back(Utils::setText(textSize, C_DARK_GREEN, "DEX: " + std::to_string(dexterity())));
    _info.push_back(Utils::setText(textSize, C_DARK_GREEN, "INT: " + std::to_string(intellect())));
    _info.push_back(Utils::setText(textSize, C_DARK_GREEN, "TYPE: " + type()));
    _info.push_back(Utils::setText(textSize, C_DARK_GREEN, "COST: " + std::to_string(cost())));
}

Dino::~Dino()
{
    _info.clear();
}

int Dino::damage(Terrain terrain)
{
    int damage;

    switch (terrain)
    {
    case T_Plain:
        damage = _STR;
        break;
    case T_River:
        damage = _DEX;
        break;
    default:
        damage = _INT;
        break;
    }

    return terrain == _type ? damage * 2 : damage;
}

std::string Dino::name() const
{
    switch (_name) {
    case N_Tyranosaurus:
        return "Tyranosaurus";
    case N_Brontozaurus:
        return "Brontozaurus";
    default:
        return "Tryceratops";
    }
}

std::string Dino::type() const
{
    switch (_type)
    {
    case T_Plain:
        return "STR";
        break;
    case T_River:
        return "DEX";
        break;
    default:
        return "INT";
        break;
    }
}

void Dino::draw(sf::RenderWindow* window, DinoState state, int x, int y)
{
    /*int spriteX;
    int spriteY;*/

   /* switch (state)
    {
    case D_Idle:
        relevantState = idle;
        break;
    case D_Walking:
        relevantState = walking;
        break;
    case D_Attacking:
        relevantState = attacking;
        break;
    case D_Dying:
        relevantState = dying;
        break;
    default:
        relevantState = idle;
        break;
    }*/

    /*spriteX = relevantState[_activeFrame].x;
    spriteY = relevantState[_activeFrame].y;
    _activeFrame = (_activeFrame + 1) % sizeof(_activeFrame);*/

    //_sprite.setTextureRect(sf::IntRect(dinoSize, dinoSize, spriteX, spriteY));

    //_sprite.setPosition(x, y);

    window->draw(_sprite);
}

Dino* Dino::generateDino()
{
    EDinoName DinoName;
    switch (rand() % 3)
    {
    case 0:
        DinoName = N_Tyranosaurus;
        break;
    case 1:
        DinoName = N_Tryceratops;
        break;
    default:
        DinoName = N_Brontozaurus;
        break;
    }

    Terrain type;

    switch (rand() % 3)
    {
    case 0:
        type = T_Plain;
        break;
    case 1:
        type = T_River;
        break;
    default:
        type = T_Mountain;
        break;
    }

    return new Dino(type, DinoName, rand() % 20 + 10, rand() % 20 + 10, rand() % 20 + 10);
}

void Dino::setDataForDrawing(sf::Vector2f position, boolean enemy)
{
    _state = D_Idle;
    _sprite.setOrigin(sf::Vector2f(25, 25));
    _sprite.setScale(sf::Vector2f(enemy ? -3 : 3, 3));
    offset();
    _sprite.setPosition(sf::Vector2f(position.x + _offset.x, position.y + _offset.y));

    const int xOffset = 150;
    const int yOffset = 30;
    const int infoSize = static_cast<int>(_info.size());
    const sf::Vector2f nameSize = _nameText.getLocalBounds().getSize();
    const sf::Vector2f namePosition = sf::Vector2f(position.x + (DINOCARD_SIZE.x - nameSize.x) / 2, position.y - 40);

    _nameText.setPosition(namePosition);

    for (int i = 0; i < infoSize; i++)
    {
        _info[i].setPosition(sf::Vector2f(position.x + xOffset, position.y + yOffset * i));
    }
    _clock.restart();
    _sprite.setTextureRect(sf::IntRect(sf::Vector2i(SPRITE_OFFSET * _activeFrame,
        SPRITE_OFFSET * _state), DINO_VEC));
}

void Dino::drawForShop(sf::RenderWindow* window)
{
    if (_clock.getElapsedTime().asSeconds() >= .2)
    {
        _activeFrame = (_activeFrame + 1) % 2;
        _sprite.setTextureRect(sf::IntRect(sf::Vector2i(SPRITE_OFFSET * _activeFrame,
            SPRITE_OFFSET * _state), DINO_VEC));
        _clock.restart();
    }
    window->draw(_sprite);
    window->draw(_nameText);
    for (auto& infopart : _info)
    {
        window->draw(infopart);
    }
}

void Dino::drawInParty(sf::RenderWindow* window)
{
    if (_clock.getElapsedTime().asSeconds() >= .2)
    {
        _activeFrame = (_activeFrame + 1) % 2;
        _sprite.setTextureRect(sf::IntRect(sf::Vector2i(SPRITE_OFFSET * _activeFrame,
            SPRITE_OFFSET * _state), DINO_VEC));
        _clock.restart();
    }
    window->draw(_sprite);
    window->draw(_nameText);
    for (int i = 0; i < 5; i++)
    {
        window->draw(_info[i]);
    }
}

void Dino::drawInMain(sf::RenderWindow* window, sf::Vector2f position)
{
    if (_clock.getElapsedTime().asSeconds() >= .2)
    {
        _activeFrame = (_activeFrame + 1) % 2;
        _sprite.setTextureRect(sf::IntRect(sf::Vector2i(SPRITE_OFFSET * _activeFrame,
            SPRITE_OFFSET * _state), DINO_VEC));
        _clock.restart();
    }
    _sprite.setScale(sf::Vector2f(1, 1));
    _sprite.setPosition(position);
    _sprite.setTextureRect(sf::IntRect(sf::Vector2i(SPRITE_OFFSET * _activeFrame,
        SPRITE_OFFSET * _state), DINO_VEC));
    window->draw(_sprite);
}

void Dino::offset()
{
    const sf::Vector2f dinoSize{ _sprite.getGlobalBounds().getSize() };
    _offset = sf::Vector2f( dinoSize.x / 2, dinoSize.y / 2 );
}
