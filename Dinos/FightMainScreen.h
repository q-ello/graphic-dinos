#pragma once
#include "ScreenBase.h"
#include "FightFinalScreen.h"

enum FightState
{
    F_WAITING_INPUT,
    F_ATK_ATTACK,
    F_ATK_DAMAGED,
    F_ATK_DIE,
    F_CHANGE
};

class FightMainScreen : public ScreenBase
{
public:
	using ScreenBase::ScreenBase;
	FightMainScreen(sf::RenderWindow* window, sf::Texture* texture, Terrain terrain);
    ~FightMainScreen();
private:
    //render stuff mostly
	sf::Texture* _texture;
	Terrain _terrain;
    std::vector<std::shared_ptr<Dino>> _party;
	std::vector<std::shared_ptr<Dino>> _enemies{};
	sf::Text _turnText;
    Button _escapeButton{ };
    Button _atkButton{ };
    sf::Vector2f _dinoPos{ 0, 0 };
    sf::Vector2f _enemyPos{ 0, 0 };

    int _dinoScale{ 2 };

    //fight logic data
    FightState _state{ F_WAITING_INPUT };
    std::shared_ptr<Dino> _currentDino{ nullptr };
    std::shared_ptr<Dino> _oldDino{ nullptr };
    std::shared_ptr<Dino> _currentEnemy{ nullptr };
    bool _playerTurn{ true };

    //basic render
	void setScreenData() override;
	void createBG() override;
	void drawData() override;

    void handleKeyPressedEvent(sf::Keyboard::Scancode code) override;
    void handleKeyReleasedEvent(sf::Keyboard::Scancode code) override;
    void handleMouseButtonPressedEvent(sf::Event::MouseButtonEvent button) override;
    void handleMouseButtonReleasedEvent(sf::Event::MouseButtonEvent button) override;
    void handleDiffPopupChoice(int choice) override;

    //fight logic methods
    void showConcedePopup();
    void returnToMain();
    void startAttack();
    void executeDino(int i, bool attackToo = false);
    void changeDinosData();
    void nextTurn();

    //check animation complete
    void dinoAttacking();
    void dinoDamaged();
    void dinoDying();
    void dinosChanging();

    //who attacks who
    std::shared_ptr<Dino> _attackingDino{ nullptr };
    std::shared_ptr<Dino> _damagedDino{ nullptr };

    //final
    void fightEnded(bool won);
};
