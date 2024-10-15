#include "FightMainScreen.h"

FightMainScreen::FightMainScreen(sf::RenderWindow* window, sf::Texture* texture, Terrain terrain)
	: ScreenBase(window)
	, _texture{ texture }
	, _terrain{ terrain }
{
    for (auto& dino : Player::party())
    {
        if (dino != nullptr)
        {
            _party.push_back(std::move(dino));
        }
    }
    
    int enemyNumber = rand() % (_party.size()) + 1;
    
    for (int i = 0; i < enemyNumber; i++)
    {
        _enemies.push_back(Dino::generateDino());
    }

    _currentDino = _party[0];
    _currentEnemy = _enemies[0];

    _attackingDino = _currentDino;
    _damagedDino = _currentEnemy;
}

FightMainScreen::~FightMainScreen()
{
    _party.clear();
    _enemies.clear();
}

void FightMainScreen::setScreenData()
{
    _turnText = Utils::setText(40, C_DARK_GREEN, "Your turn", { 350, 200 });
    const float turnYPos = 200;
    const float turnXPos = Utils::alignToCenter(&_turnText).x;
    _turnText.setPosition({ turnXPos, turnYPos });
    _turnText.setOutlineThickness(2);

    _escapeButton = Button(25, "ESC - CONCEDE", C_DARK_GREEN, { 25, 25 });
    _atkButton = Button(25, "F - ATTACK", C_DARK_GREEN, { 750, 700 });

    float yPos;

    switch (_terrain)
    {
    case T_Mountain:
        yPos = 530;
        break;
    case T_River:
        yPos = 460;
        break;
    default:
        yPos = 580;
        break;
    }

    _dinoPos = { SCREEN_SIZE.x / 2 - DINO_SIZE * 2, yPos };
    _enemyPos = { SCREEN_SIZE.x / 2, yPos };

    for (int i = 0; i < _party.size(); i++)
    {
        const bool isCurrent = _party[i] == _currentDino;
        const float x = isCurrent ? _dinoPos.x : 10 + DINO_SIZE * _dinoScale * i;
        _party[i]->setFightData({ x, yPos }, _terrain, false, isCurrent, i);
    }

    for (int i = 0; i < _enemies.size(); i++)
    {
        const bool isCurrent = _enemies[i] == _currentEnemy;
        const float x = isCurrent ? _enemyPos.x : SCREEN_SIZE.x - (10 + DINO_SIZE * _dinoScale * i);
        _enemies[i]->setFightData({ x, yPos }, _terrain, true);
    }
}

void FightMainScreen::createBG()
{
	_bg = Utils::setBG(_texture);
}

void FightMainScreen::drawData()
{
    switch (_state)
    {
    case F_ATK_ATTACK:
        dinoAttacking();
        break;
    case F_ATK_DAMAGED:
        dinoDamaged();
        break;
    case F_ATK_DIE:
        dinoDying();
        break;
    case F_CHANGE:
        dinosChanging();
        break;
    default:
        break;
    }

    _escapeButton.draw(_window);
    _atkButton.draw(_window);
    _window->draw(_turnText);
    _window->draw(_moneyText);
    
    for (auto& dino : _party)
    {
        dino->drawInFight(_window);
    }

    for (auto& dino : _enemies)
    {
        dino->drawInFight(_window);
    }
}

void FightMainScreen::handleKeyPressedEvent(sf::Keyboard::Scancode code)
{
    if (code == sf::Keyboard::Scancode::Escape)
    {
        _escapeButton.toggleAlmostExecuted(true);
        return;
    }
    
    int num = -1;

    switch (code)
    {
    case sf::Keyboard::Scancode::Num1:
        num = 0;
        break;
    case sf::Keyboard::Scancode::Num2:
        num = 1;
        break;
    case sf::Keyboard::Scancode::Num3:
        num = 2;
        break;
    default:
        break;
    }

    if (num != -1 && _party.size() > num)
    {
        _party[num]->toggleAlmostExecuted(true);
        return;
    }

    if (code == sf::Keyboard::Scancode::F)
    {
        _atkButton.toggleAlmostExecuted(true);
        return;
    }
}

void FightMainScreen::handleKeyReleasedEvent(sf::Keyboard::Scancode code)
{
    if (code == sf::Keyboard::Scancode::Escape)
    {
        showConcedePopup();
        _escapeButton.toggleAlmostExecuted(false);
        return;
    }

    int num = -1;

    switch (code)
    {
    case sf::Keyboard::Scancode::Num1:
        num = 0;
        break;
    case sf::Keyboard::Scancode::Num2:
        num = 1;
        break;
    case sf::Keyboard::Scancode::Num3:
        num = 2;
        break;
    default:
        break;
    }

    if (num != -1 && _party.size() > num)
    {
        executeDino(num);
        _party[num]->toggleAlmostExecuted(false);
        return;
    }

    if (code == sf::Keyboard::Scancode::F)
    {
        startAttack();
        _atkButton.toggleAlmostExecuted(false);
        return;
    }
}

void FightMainScreen::handleMouseButtonPressedEvent(sf::Event::MouseButtonEvent button)
{
    if (_escapeButton.handleMousePressed(button.x, button.y))
    {
        return;
    }

    if (_atkButton.handleMousePressed(button.x, button.y))
    {
        return;
    }

    for (auto& dino : _party)
    {
        if (dino->handleMousePressed(static_cast<float>(button.x), static_cast<float>(button.y)))
        {
            return;
        }
    }
}

void FightMainScreen::handleMouseButtonReleasedEvent(sf::Event::MouseButtonEvent button)
{
    if (_escapeButton.handleMouseReleased(button.x, button.y))
    {
        showConcedePopup();
    }

    if (_atkButton.handleMouseReleased(button.x, button.y))
    {
        startAttack();
    }

    for (int i = 0; i < _party.size(); i++)
    {
        if (_party[i]->handleMouseReleased(static_cast<float>(button.x), static_cast<float>(button.y)))
        {
            executeDino(i, true);
        }
    }
}

void FightMainScreen::handleDiffPopupChoice(int choice)
{
    if (_popup->type() == P_CONCEDE)
    {
        switch (choice)
        {
        case C_YES:
            Player::addCash(-1 * 25 * static_cast<int>(_enemies.size()));
            setMoneyData();
            returnToMain();
            break;
        default:
            _popup = nullptr;
        }
    }
}

void FightMainScreen::showConcedePopup()
{
    int concedeCost = static_cast<int>(_enemies.size()) * 25;
    _popup = std::make_unique<Popup>(Popup("You sure? That will\ncost you " + std::to_string(concedeCost), P_CONCEDE, {"CONCEDE", "STAY"}, {C_YES, C_NO}));
}

void FightMainScreen::returnToMain()
{
    _show = false;
    for (auto& dino : _party)
    {
        dino->regenerate();
    }
}

void FightMainScreen::startAttack()
{
    _state = F_ATK_ATTACK;
    _currentDino->setAnimation(D_Attacking);
    _waitingInput = false;
}

void FightMainScreen::executeDino(int i, bool attackToo)
{
    if (_party[i] == _currentDino)
    {
        if (attackToo)
        {
            startAttack();
        }
        return;
    }

    _oldDino = _currentDino;
    _oldDino->changeDirection();
    _oldDino->showNumText();
    _oldDino->setAnimation(D_Walking);

    _currentDino = _party[i];
    _currentDino->showNumText();
    _currentDino->setAnimation(D_Walking);

    _state = F_CHANGE;

    _waitingInput = false;
}

void FightMainScreen::changeDinosData()
{
    for (int i = 0; i < _party.size(); i++)
    {
        _party[i]->changeNumText(i + 1);
    }
}

void FightMainScreen::nextTurn()
{
    _playerTurn = !_playerTurn;
    const std::string whose = _playerTurn ? "Your" : "Enemy's";
    _turnText.setString(whose + " turn");

    auto& temp = _attackingDino;
    _attackingDino = _playerTurn ? _currentDino : _currentEnemy;
    _damagedDino = _playerTurn ? _currentEnemy : _currentDino;

    if (_playerTurn)
    {
        _state = F_WAITING_INPUT;
        _waitingInput = true;
        return;
    }

    _state = F_ATK_ATTACK;
    _attackingDino->setAnimation(D_Attacking);
}

void FightMainScreen::dinoAttacking()
{
    if (_attackingDino->animCompleted())
    {
        _attackingDino->setAnimation(D_Idle);
        _damagedDino->takeDamage(_attackingDino->damage(_terrain));
        _state = F_ATK_DAMAGED;
    }
}

void FightMainScreen::dinoDamaged()
{
    if (_damagedDino->animCompleted())
    {
        if (_damagedDino->hp() <= 0)
        {
            _damagedDino->setAnimation(D_Dying);
            _state = F_ATK_DIE;
            return;
        }
        _damagedDino->setAnimation(D_Idle);
        nextTurn();
    }
}

void FightMainScreen::dinoDying()
{
    if (!_damagedDino->animCompleted())
    {
        return;
    }

    auto& dinosAtLoss = !_playerTurn ? _party : _enemies;

    for (int i = 0; i < dinosAtLoss.size(); i++)
    {
        if (dinosAtLoss[i] == _damagedDino)
        {
            dinosAtLoss.erase(dinosAtLoss.begin() + i);
            break;
        }
    }

    if (!_playerTurn)
    {
        Player::dinoDied(_damagedDino);
        if (_party.empty())
        {
            fightEnded(false);
            return;
        }
        _currentDino = _party[0];
        _currentDino->setAnimation(D_Walking);
        _currentDino->showNumText();
    }
    else
    {
        if (_enemies.empty())
        {
            fightEnded(true);
            return;
        }
        _currentEnemy = _enemies[0];
        _currentEnemy->setAnimation(D_Walking);
    }

    _damagedDino = nullptr;

    _state = F_CHANGE;
}

void FightMainScreen::dinosChanging()
{
    if (_currentDino->position().x < _dinoPos.x)
    {
        _currentDino->move(1);
        if (_oldDino != nullptr)
        {
            _oldDino->move(-1);
        }
        return;
    }

    if (_currentEnemy->position().x > _enemyPos.x)
    {
        _currentEnemy->move(-1);
        return;
    }

    _currentDino->setAnimation(D_Idle);
    _currentEnemy->setAnimation(D_Idle);
    if (_oldDino != nullptr)
    {
        _oldDino->changeDirection();
        _oldDino->setAnimation(D_Idle);
        _oldDino = nullptr;
    }

    nextTurn();
}

void FightMainScreen::fightEnded(bool won)
{
    std::string finalText;
    int pay;
    if (won)
    {
        pay = 50 * static_cast<int>(_party.size());
        finalText = "You won!\nYou gain " + std::to_string(pay);
    }
    else
    {
        pay = 40 * static_cast<int>(_enemies.size());
        finalText = "You lost...\nYou lose " + std::to_string(pay);
        pay *= -1;
    }

    Player::addCash(pay);

    FightFinalScreen* finalScreen = new FightFinalScreen(_window, finalText, _texture);
    finalScreen->show();
    delete finalScreen;

    returnToMain();
}
