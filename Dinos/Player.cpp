#include "Player.h"

void Player::clearData()
{
    _ownedDinosaurs.clear();
    _currentParty.clear();
}

void Player::save()
{
    std::ofstream savefile("savefile.txt");
    if (savefile.is_open())
    {
        savefile << "MONEY: " << _money << "\n";
        for (auto& it : _currentParty) {
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

void Player::load()
{
    std::ifstream savefile("savefile.txt");

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
                std::vector<Dino*>* dinosToLoad;

                if (v[0] == "CURRENT") {
                    dinosToLoad = &_currentParty;
                }
                else {
                    dinosToLoad = &_ownedDinosaurs;
                }
                if (v[1] == "DinoStr")
                    dinosToLoad->emplace_back(new Dino(T_Plain, convertToEnum(v[2]), stoi(v[3]), stoi(v[4]), stoi(v[5])));
                if (v[1] == "DinoInt")
                    dinosToLoad->emplace_back(new Dino(T_River, convertToEnum(v[2]), stoi(v[3]), stoi(v[4]), stoi(v[5])));
                if (v[1] == "DinoDex")
                    dinosToLoad->emplace_back(new Dino(T_Mountain, convertToEnum(v[2]), stoi(v[3]), stoi(v[4]), stoi(v[5])));
            }
        }
        savefile.close();
    }
}

int Player::_money{ 100 };
std::vector<Dino*> Player::_ownedDinosaurs{};
std::vector<Dino*> Player::_currentParty{};