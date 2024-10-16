#include "Player.h"

void Player::clearData()
{
    _ownedDinosaurs.clear();
    _currentParty.clear();
}

void Player::save()
{
    std::ofstream savefile("data/savefile.txt");
    if (savefile.is_open())
    {
        savefile << "MONEY: " << _money << "\n";
        for (auto& it : _currentParty) {
            if (it == nullptr)
            {
                continue;
            }
            savefile << "CURRENT " << it->type() << " " << it->name() << " " << it->strength() << " ";
            savefile << it->dexterity() << " " << it->intellect() << "\n";
        }
        for (auto& it : _ownedDinosaurs)
        {
            savefile << "OWNED " << it->type() << " " << it->name() << " " << it->strength() << " ";
            savefile << it->dexterity() << " " << it->intellect() << "\n";
        }
        savefile.close();
    }
}

void Player::addDino(std::shared_ptr<Dino> newDino)
{
    auto emptySlot = std::find(_currentParty.begin(), _currentParty.end(), nullptr);
    if (emptySlot != _currentParty.end())
    {
        *emptySlot = newDino;
    }
    else
    {
        _ownedDinosaurs.push_back(std::move(newDino));
    }
}

void Player::load()
{
    std::ifstream savefile("data/savefile.txt");

    if (savefile.is_open()) {
        std::string line;

        while (std::getline(savefile, line)) {
            std::string s;
            std::stringstream ss(line);

            std::vector<std::string> v;
            while (getline(ss, s, ' ')) {
                v.push_back(s);
            }

            if (v.size() == 2) {
                if (v[0] == "MONEY:") {
                    _money = stoi(v[1]);
                }
            }
            else if (v.size() == 6) {
                std::vector<std::shared_ptr<Dino>>* dinosToLoad;

                if (v[0] == "CURRENT") {
                    dinosToLoad = &_currentParty;
                }
                else {
                    dinosToLoad = &_ownedDinosaurs;
                }
                Terrain dinoType;
                if (v[1] == "STR")
                    dinoType = T_Plain;
                else if (v[1] == "INT")
                    dinoType = T_River;
                else if (v[1] == "DEX")
                    dinoType = T_Mountain;

                dinosToLoad->emplace_back(new Dino(dinoType, convertToEnum(v[2]), stoi(v[3]), stoi(v[4]), stoi(v[5])));
            }
        }
        savefile.close();
    }
    _currentParty.resize(3);
}

void Player::changeDino(int partyIndex, int restingIndex)
{
    std::shared_ptr<Dino> partyDino = _currentParty[partyIndex];
    _currentParty[partyIndex] = std::move(_ownedDinosaurs[restingIndex]);

    if (partyDino == nullptr)
    {
        _ownedDinosaurs.erase(_ownedDinosaurs.begin() + restingIndex);
    }
    else
    {
        _ownedDinosaurs[restingIndex] = std::move(partyDino);
    }
}

boolean Player::partyIsEmpty()
{
    for (int i = 0; i < 3; i++)
    {
        if (_currentParty[i] != nullptr)
        {
            return false;
        }
    }

    return true;
}

Terrain Player::newTerrain()
{
    switch (rand() % 3)
    {
    case 0:
        return T_Plain;
    case 1:
        return T_River;
        break;
    default:
        return T_Mountain;
        break;
    }
}

void Player::dinoDied(std::shared_ptr<Dino> dino)
{
    int i = 0;
    for (; i < 3; i++)
    {
        if (_currentParty[i] == dino)
        {
            _currentParty[i] = nullptr;
            return;
        }
    }
}

int Player::_money{ 100 };
std::vector<std::shared_ptr<Dino>> Player::_ownedDinosaurs{};
std::vector<std::shared_ptr<Dino>> Player::_currentParty{};
