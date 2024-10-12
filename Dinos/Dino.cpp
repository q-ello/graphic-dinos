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

    _fightInfo.push_back(Utils::setText(textSize, C_BRIGHT_GREEN, "HP: " + std::to_string(_HP)));
    _fightInfo.push_back(Utils::setText(textSize, C_STR, "DMG: " + std::to_string(strength())));

    _numText = Utils::setText(textSize, C_DARK_GREEN, "");

    _sprite.setOrigin({ DINO_SIZE / 2, DINO_SIZE / 2 });
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

bool Dino::takeDamage(int dmg)
{
    _HP -= dmg;
    if (_HP < 0)
    {
        _HP = 0;
    }
    setAnimation(D_Damaged);
    _fightInfo[0].setString("HP: " + std::to_string(_HP));

    return _HP == 0;
}

void Dino::regenerate()
{
    _HP = 100;
    _fightInfo[0].setString("HP: " + std::to_string(_HP));
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
    _sprite.setScale(sf::Vector2f(3, 3));
    countOffset();
    _sprite.setPosition(position + _offset);


    const int xOffset = 150;
    const int yOffset = 30;
    const int infoSize = static_cast<int>(_info.size());
    const sf::Vector2f namePosition = sf::Vector2f(position.x + Utils::alignToCenter(&_nameText, DINOCARD_SIZE).x, position.y - 40);

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
    for (int i = 0; i < 4; i++)
    {
        window->draw(_info[i]);
    }
}

void Dino::setDataForMain(sf::Vector2f position)
{
    _state = D_Idle;
    _activeFrame = 0;
    _sprite.setScale({1, 1});
    _sprite.setPosition(position);
    _sprite.setTextureRect(sf::IntRect(sf::Vector2i(SPRITE_OFFSET * _activeFrame,
        SPRITE_OFFSET * _state), DINO_VEC));
}

void Dino::drawInMain(sf::RenderWindow* window)
{
    if (_clock.getElapsedTime().asSeconds() >= .2)
    {
        _activeFrame = (_activeFrame + 1) % 2;
        _sprite.setTextureRect(sf::IntRect(sf::Vector2i(SPRITE_OFFSET * _activeFrame,
            SPRITE_OFFSET * _state), DINO_VEC));
        _clock.restart();
    }
    
    window->draw(_sprite);
}

<<<<<<< HEAD
void Dino::offset()
{
    const sf::Vector2f dinoSize{ _sprite.getGlobalBounds().getSize() };
    _offset = sf::Vector2f( dinoSize.x / 2, dinoSize.y / 2 );
=======
void Dino::setFightData(sf::Vector2f position, Terrain terrain, bool turnedLeft, bool isCurrent, int number)
{
    _isCurrent = isCurrent;

    _state = D_Idle;
    _sprite.setScale({ turnedLeft ? 2.f : -2.f, 2.f });
    countOffset();
    _sprite.setPosition(position + _offset);

    const int yOffset = 30;

    const int infoSize = static_cast<int>(_fightInfo.size());

    for (int i = 0; i < infoSize; i++)
    {
        _fightInfo[i].setPosition({position.x, position.y - yOffset * infoSize + yOffset * i});
    }
    _clock.restart();
    _sprite.setTextureRect(sf::IntRect(sf::Vector2i(SPRITE_OFFSET * _activeFrame,
        SPRITE_OFFSET * _state), DINO_VEC));

    _fightInfo[1].setFillColor(_type == T_Mountain ? C_INT : _type == T_Plain ? C_STR : C_DEX);
    _fightInfo[1].setString("DMG: " + std::to_string(damage(terrain)));

    _numText.setString(std::to_string(number + 1));
    const float numXOffset = Utils::alignToCenter(&_numText, { DINO_SIZE * 2, DINO_SIZE * 2 }).x;
    _numText.setPosition({position.x + numXOffset, position.y + DINO_SIZE * 2});
}


void Dino::drawInFight(sf::RenderWindow* window)
{
    if (_clock.getElapsedTime().asSeconds() > .2)
    {
        //draw damaged
        if (_state == D_Damaged)
        {
            if (_damagedFrame > 5)
            {
                _animComplete = true;
            }
            else
            {
                _damagedFrame++;
            }
        }

        //other animations
        if (_activeFrame == 3 && _state != D_Idle && _state != D_Walking)
        {
            _animComplete = true;
        }
        else {
            _activeFrame = (_activeFrame + 1) % (_state == D_Idle ? 2 : 4);
        }
        _sprite.setTextureRect(sf::IntRect(sf::Vector2i(SPRITE_OFFSET * _activeFrame,
            SPRITE_OFFSET * _state), DINO_VEC));
        _clock.restart();
    }

    if (_damagedFrame % 2 != 0)
    {
        return;
    }

    window->draw(_sprite);
    for (auto& part : _fightInfo)
    {
        window->draw(part);
    }

    if (!_isCurrent)
    {
        window->draw(_numText);
    }
}


void Dino::setAnimation(DinoState animation)
{
    _animComplete = false;
    if (_state == animation)
    {
        return;
    }

    _state = animation;
    _activeFrame = 0;
    _damagedFrame = 0;
}

void Dino::countOffset()
{
    sf::Vector2f scale = _sprite.getScale();
    _offset = { abs(DINO_SIZE * scale.x / 2) , abs(DINO_SIZE * scale.y / 2)};
}

bool Dino::handleMousePressed(float x, float y)
{
    if (_sprite.getGlobalBounds().contains({ x, y }))
    {
        toggleAlmostExecuted(true);
        _focused = true;
        return true;
    }
    return false;
}

bool Dino::handleMouseReleased(float x, float y)
{
    toggleAlmostExecuted(false);
    if (_focused == true && _sprite.getGlobalBounds().contains({ x, y }))
    {
        return true;
    }
    return false;
}

void Dino::toggleAlmostExecuted(bool focus)
{
    _numText.setFillColor(focus ? C_EXECUTABLE : C_DARK_GREEN);
}

void Dino::changeNumText(int num)
{
    _numText.setString(std::to_string(num));
}

sf::Vector2f Dino::position() const
{
    return _sprite.getPosition() - _offset;
}

void Dino::move(int dir)
{
    const float speed = 0.1;
    sf::Vector2f movement = { speed * dir, 0 };
    _sprite.move(movement);
    _numText.move(movement);

    for (auto& part : _fightInfo)
    {
        part.move(movement);
    }
}

void Dino::changeDirection()
{
    const sf::Vector2f oldScale = _sprite.getScale();
    _sprite.setScale(-1 * oldScale.x, oldScale.y);
}

void Dino::showNumText()
{
    _isCurrent = !_isCurrent;
>>>>>>> 0176da6 (now it's acceptable)
}
