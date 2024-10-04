#pragma once

#include "./stdafx.h"
#include "Utils.h"

enum EDinoName { N_Tyranosaurus, N_Tryceratops, N_Brontozaurus };

enum DinoState { D_Idle = 3, D_Walking = 0, D_Attacking = 1, D_Dying  = 2};

static EDinoName convertToEnum(const std::string& str)
{
    if (str == "Tyranosaurus") return N_Tyranosaurus;
    if (str == "Tryceratops") return N_Tryceratops;
    if (str == "Brontozaurus") return N_Brontozaurus;

    return N_Tyranosaurus;
}

const int DINO_SIZE{ 50 };
const sf::Vector2i DINO_VEC{ sf::Vector2i(DINO_SIZE, DINO_SIZE) };
const int SPRITE_OFFSET{ 60 };

class Dino {
public:
    Dino(Terrain type, EDinoName dinoName, int str, int dex, int intellect);

    ~Dino();

    int damage(Terrain terrain);

    std::string name() const;

    std::string type() const;

    int cost() {
        return _cost;
    }

    int strength() {
        return _STR;
    }

    int dexterity() {
        return _DEX;
    }

    int intellect() {
        return _INT;
    }

    int hp() {
        return _HP;
    }

    void takeDamage(int dmg) {
        _HP -= dmg;
        if (_HP < 0)
            _HP = 0;
    }

    void Regenerate() {
        _HP = 100;
    }

    void draw(sf::RenderWindow* window, DinoState state, int x, int y);

    void resetActiveFrame()
    {
        _activeFrame = 0;
    }

    static Dino* generateDino();

    void setDataForDrawing(sf::Vector2f position);

    void drawForShop(sf::RenderWindow* window);

    void drawInParty(sf::RenderWindow* window);

    void drawInMain(sf::RenderWindow* window, sf::Vector2f position);

private:
    int _STR;
    int _DEX;
    int _INT;
    int _HP{ 100 };
    EDinoName _name;
    int _cost;
    Terrain _type;
    int _activeFrame{ 0 };
    DinoState _state{ D_Idle };

    sf::Sprite _sprite;
    sf::Texture _texture;
    std::vector<sf::Text> _info{};
    sf::Text _nameText;
    sf::Clock _clock;
};
