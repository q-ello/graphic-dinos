#pragma once

#include "./stdafx.h"
#include "Dino.h"
#include "ScreenBase.h"

class ShopScreen : public ScreenBase
{
public:
    using ScreenBase::ScreenBase;
private:
    void setScreenData() override;
    void drawData() override;

    void updateShop();
    std::vector<Dino*> _shopList;
};

    /*
    bool BuyDino(Player* playerData)
    {
        std::cout << "Dinos you can purchase:" << std::endl;
        int counter = 0;
        for (auto& it : ShopList) {
            std::cout << "\t[ID " << counter++ << "] Name: " << it.get()->GetName() << ", Type: " << it.get()->GetType();
            std::cout << ", Price: " << it.get()->GetCost() << ", Plain ATK: " << it.get()->damage(Terrain::Plain);
            std::cout << ", River ATK: " << it.get()->damage(Terrain::River) << ", Mountain ATK: ";
            std::cout << it.get()->damage(Terrain::Mountain) << std::endl;

        }

        std::cout << "(type 'quit' if you changed your mind)\n";

        if (counter == 0)
        {
            std::cout << "No dinos. Your shop is empty. Use shopupdate" << std::endl;
            return false;
        }

        counter--;

        int inputID = -1;

        std::cout << "\nSelect Dino by ID: ";

        std::string answer;
        std::getline(std::cin, answer); //just a dummy to make getline work

        do
        {
            std::getline(std::cin, answer);
            if (isDigits(answer)) {
                inputID = stoi(answer);
            }
            else if (answer == "shopupdate") {
                GenerateShop();
                std::cout << "New dinos are available in the shop! type shop to see a new list\n";
                return true;
            }
            else if (answer == "quit") {
                return false;
            }
            else {
                continue;
            }
        } while (inputID < 0 || inputID > counter);

        int cost = ShopList[inputID].get()->GetCost();

        if (cost > playerData->GetMoney())
        {
            std::cout << "You are too poor, get the hell out of the shop!" << std::endl;
            return true;
        }

        playerData->AddCash(-1 * cost);

        std::string NewDinoNameStr = ShopList[inputID].get()->GetName();
        int NewDinoStr = ShopList[inputID].get()->GetSTR();
        int NewDinoDex = ShopList[inputID].get()->GetDEX();
        int NewDinoInt = ShopList[inputID].get()->GetINT();

        std::cout << "Congratulations, you bought the " << NewDinoNameStr << "!" << std::endl;
        std::cout << "Money you're left with: " << playerData->GetMoney() << '\n';

        EDinoName NewDinoName = convertToEnum(NewDinoNameStr);

        if (ShopList[inputID].get()->GetType() == "DinoStr")
        {
            playerData->AddDino(new DinoStr(NewDinoName, NewDinoStr, NewDinoDex, NewDinoInt, right));
        }
        else if (ShopList[inputID].get()->GetType() == "DinoInt")
        {
            playerData->AddDino(new DinoInt(NewDinoName, NewDinoStr, NewDinoDex, NewDinoInt, right));
        }
        else if (ShopList[inputID].get()->GetType() == "DinoDex")
        {
            playerData->AddDino(new DinoDex(NewDinoName, NewDinoStr, NewDinoDex, NewDinoInt, right));
        }
        else {
            return false;
        }
        ShopList.erase(ShopList.begin() + inputID);

        std::cout << "Your dinos in total: " << playerData->GetParty().size() + playerData->getOwnedDinos().size() << '\n';

        playerData->Save();

        return true;
    }
    */