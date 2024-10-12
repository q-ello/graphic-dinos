#pragma once

#include "./stdafx.h"
#include "Utils.h"

enum EDinoName { N_Tyranosaurus, N_Tryceratops, N_Brontozaurus };

enum DinoState { D_Idle = 3, D_Walking = 0, D_Attacking = 1, D_Dying  = 2, D_Damaged = 4};

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

    //getters
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

    //fight logic
    bool takeDamage(int dmg);
    void regenerate();

    static Dino* generateDino();

<<<<<<< HEAD
    //draw in different screens
    void setDataForDrawing(sf::Vector2f position);
=======
    void setDataForDrawing(sf::Vector2f position, boolean enemy = false);

>>>>>>> 0d96cc83f140eb7dd43676eac8e44306101e1709
    void drawForShop(sf::RenderWindow* window);
    void drawInParty(sf::RenderWindow* window);
    void setDataForMain(sf::Vector2f position);
    void drawInMain(sf::RenderWindow* window);
    void setFightData(sf::Vector2f position, Terrain terrain, bool turnedLeft = false, bool isCurrent = true, int number = 0);
    void drawInFight(sf::RenderWindow* window);

    //animation
    bool animCompleted()
    {
        return _animComplete;
    }
    void setAnimation(DinoState animation);

    //render from center
    void countOffset();

    //handle mouse
    bool handleMousePressed(float x, float y);
    bool handleMouseReleased(float x, float y);
    void toggleAlmostExecuted(bool focus);
    
    //fight
    void changeNumText(int num);

    //move around
    sf::Vector2f position() const;
    void move(int dir);
    void changeDirection();
    void showNumText();

    void offset();

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
<<<<<<< HEAD
    bool _animComplete{ false };
    bool _isCurrent { false };
=======
    sf::Vector2f _offset{ 0, 0 };
>>>>>>> 0d96cc83f140eb7dd43676eac8e44306101e1709

    //stuff for render
    sf::Sprite _sprite;
    sf::Texture _texture;
    std::vector<sf::Text> _info{};
    std::vector<sf::Text> _fightInfo{};
    sf::Text _nameText;
    sf::Clock _clock;
    sf::Text _numText;
    sf::Vector2f _offset{ 0, 0 };

    //for mouse handle
    bool _focused;

    //for animating damaged
    int _damagedFrame{ 0 };
};
