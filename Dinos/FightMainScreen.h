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
	bool _isAnimating{ false };
    std::vector<Dino*> _party;
	std::vector<Dino*> _enemies{};
	sf::Text _turnText;
    Button* _escapeButton{ nullptr };
    Button* _atkButton{ nullptr };
    sf::Vector2f _dinoPos{ 0, 0 };
    sf::Vector2f _enemyPos{ 0, 0 };

    int _dinoScale{ 2 };

    //fight logic data
    FightState _state{ F_WAITING_INPUT };
    Dino* _currentDino{ nullptr };
    Dino* _oldDino{ nullptr };
    Dino* _currentEnemy{ nullptr };
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
    Dino* _attackingDino{ nullptr };
    Dino* _damagedDino{ nullptr };

    //final
    void fightEnded(bool won);
};

/*

    bool FightLoop(Player* player)
    {
        int Steps = 0;
        while (GetPlayerCount(player) && GetEnemyCount())
        {
            std::shared_ptr<Dino> currentDino = player->GetParty()[PlayerCurrentSlot];
            std::shared_ptr<Dino> currentEnemy = EnemyDinos[EnemyCurrentSlot];
            if (Steps % 2 == 0)
            {
                showTerrain();

                std::cout << "Your turn. Use 'help' if you feel disabled!" << std::endl;
                std::string input;

                std::cout << '\n';

                std::string yourState = "Your dino: " + currentDino->GetName() + ", Damage: " + std::to_string(currentDino->damage(fightTerrain)) + ", HP: " + std::to_string(currentDino->GetHP());
                yourState.resize(46, ' ');
                std::cout << yourState;
                std::cout << "Enemy dino: " << currentEnemy->GetName() << ", Damage: " << currentEnemy->damage(fightTerrain) << ", HP: " << currentEnemy->GetHP();
                renderTwoDinos(currentDino->getASCII(), currentEnemy->getASCII());
                std::cout << '\n';

                do
                {
                    std::cout << "Select command: ";
                    std::cin >> input;
                    if (input == "help")
                    {
                        std::cout << "viewparty - look at your party state. Doesn't waste your turn" << std::endl;
                        std::cout << "viewenemy - look at the enemy party state. Doesn't waste your turn" << std::endl;
                        std::cout << "switch - change your active party member" << std::endl;
                        std::cout << "fight - attack with your current party member" << std::endl;
                        std::cout << "concede - for weaklings" << std::endl;
                    }

                    if (input == "viewparty") {
                        ViewParty(player);
                    }
                    if (input == "viewenemy")
                    {
                        int counter = 1;
                        for (auto& it : EnemyDinos) {
                            std::cout << "\t[Enemy " << counter++ << "] Name: " << it.get()->GetName() << ", Type: ";
                            std::cout << it.get()->GetType() << ", HP: " << it.get()->GetHP() << ", Plain ATK: ";
                            std::cout << it.get()->damage(Terrain::Plain) << ", River ATK: " << it.get()->damage(Terrain::River);
                            std::cout << ", Mountain ATK: " << it.get()->damage(Terrain::Mountain) << std::endl;
                        }
                    }
                } while (input != "switch" && input != "fight" && input != "concede");

                if (input == "switch")
                {
                    std::cout << "Your current Dino slot is:" << std::endl;
                    std::cout << currentDino->GetName() << ", Damage: " << currentDino->damage(fightTerrain) << ", HP: " << currentDino->GetHP() << '\n';

                    int inputID = -1;
                    std::string answer;

                    std::cout << "Your whole party: \n";

                    ViewParty(player);

                    std::cout << "Select new party Dino ID: ";
                    std::getline(std::cin, answer); //another dummy to make it work

                    do
                    {
                        std::getline(std::cin, answer);
                        if (isDigits(answer)) {
                            inputID = stoi(answer);
                        }
                        else {
                            continue;
                        }
                    } while (inputID < 0 || inputID >= GetPlayerCount(player));

                    PlayerCurrentSlot = inputID;
                    std::cout << "New active party member is Dino [ID " << PlayerCurrentSlot << ']' << std::endl;
                    Steps++;
                    continue;
                }

                if (input == "fight")
                {
                    std::cout << "You attack!" << std::endl;
                    if (currentDino->damage(fightTerrain) >= currentEnemy->GetHP())
                    {
                        EnemyDinos.erase(EnemyDinos.begin() + EnemyCurrentSlot);
                        std::cout << "Enemy dino defeated! ";
                        if (GetEnemyCount())
                        {
                            std::cout << "New enemy dino inbound!" << std::endl;
                            if (EnemyCurrentSlot == GetEnemyCount()) {
                                EnemyCurrentSlot = 0;
                            }
                        }
                        else
                        {
                            std::cout << "There are no more dinos against your mighty party! You gained some money! [+" << GetPlayerCount(player) * 50 << "]" << std::endl;
                            player->AddCash(GetPlayerCount(player) * 50);
                            std::cout << "Now you have " << player->GetMoney() << '\n';
                            fightWin = true;

                            HealDinos(player);

                            break;
                        }
                    }
                    else
                    {
                        std::cout << "Enemy dino loses " << currentDino->damage(fightTerrain) << " health" << std::endl;
                        currentEnemy->DepleteHP(currentDino->damage(fightTerrain));
                    }
                    Steps++;
                }
                if (input == "concede")
                {
                    std::cout << "You ran away. Coward. You lost your pocket change on the way back [" << -1 * GetEnemyCount() * 40 << "]" << std::endl;
                    player->AddCash(-1 * GetEnemyCount() * 40);
                    std::cout << "Now you have " << player->GetMoney() << '\n';

                    HealDinos(player);
                    break;
                }
            }
            else
            {
                if (rand() % 10 == 0)
                {
                    std::cout << "Enemy Dino stalls. Enemy loses a turn" << std::endl;
                    Steps++;
                }
                else if (currentEnemy->damage(fightTerrain) >= currentDino->GetHP())
                {
                    std::cout << "Your dino defeated! You lost them forever... ";
                    player->ThrowDinoOut(PlayerCurrentSlot);
                    if (GetPlayerCount(player))
                    {
                        std::cout << "Another dino from your party comes to aid!" << std::endl;
                        if (PlayerCurrentSlot == GetPlayerCount(player)) {
                            PlayerCurrentSlot = 0;
                        }
                    }
                    else
                    {
                        std::cout << "Your dinos are defeated! You lost your pride and some money [" << -1 * GetEnemyCount() * 40 << "]" << std::endl;
                        player->AddCash(-1 * GetEnemyCount() * 40);
                        fightWin = false;

                        HealDinos(player);
                        break;
                    }
                }
                else
                {
                    std::cout << "Your dino loses " << currentEnemy->damage(fightTerrain) << " health" << std::endl;
                    currentDino->DepleteHP(currentEnemy->damage(fightTerrain));
                }
                Steps++;
            }
        }
        return fightWin;
    }

    int GetEnemyCount()
    {
        return static_cast<int>(EnemyDinos.size());
    }

    int GetPlayerCount(Player* player)
    {
        return static_cast<int>(player->GetParty().size());
    }

    void HealDinos(Player* player) {
        for (auto& survivedDino : player->GetParty()) {
            survivedDino->Regenerate();
        }
    }
    */
