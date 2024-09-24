#pragma once

#include "./stdafx.h"
#include "./Dino.h"

class Player
{
public:
    static void clearData();

    static int money()
    {
        return _money;
    }

    static std::vector<Dino*> owned()
    {
        return _ownedDinosaurs;
    }

    static std::vector<Dino*> party()
    {
        return _currentParty;
    }

    static void save();

    static void addCash(int income)
    {
        _money = _money + income >= 0 ? _money + income : 0;
    }

    static void addDino(Dino* newDino)
    {
        _ownedDinosaurs.emplace_back(std::move(newDino));
    }

    static void load();

private:
	static int _money;
    static std::vector<Dino*> _ownedDinosaurs;
    static std::vector<Dino*> _currentParty;
};

/*
* class Player
{
public:
    bool SetDinos()
    {
        ShowDinos(party);
        std::cout << "Select slot to edit (0-2): ";
        std::cout << "(type 'quit' if you changed your mind)\n";


        std::string answer;

        int inputSlot = -1;

        std::getline(std::cin, answer); //just a dummy to make getline work

        do
        {
            std::getline(std::cin, answer);
            if (isDigits(answer)) {
                inputSlot = stoi(answer);
            }
            else if (answer == "quit") {
                return false;
            }
            else {
                continue;
            }
        } while (inputSlot < 0 || inputSlot > 2);

        if (CurrentParty.size() > inputSlot) {
            std::cout << "Slot " << inputSlot << ": Name: " << CurrentParty[inputSlot].get()->GetName() << ", Type: ";
            std::cout << CurrentParty[inputSlot].get()->GetType();
            std::cout << ", Plain ATK: " << CurrentParty[inputSlot].get()->damage(Terrain::Plain) << ", River ATK: ";
            std::cout << CurrentParty[inputSlot].get()->damage(Terrain::River) << ", Mountain ATK: ";
            std::cout << CurrentParty[inputSlot].get()->damage(Terrain::Mountain) << std::endl;
        }
        else
            std::cout << "Slot " << inputSlot << " is empty" << std::endl;

        if (OwnedDinosaurs.size() == 0)
        {
            std::cout << "You cannot select any other dinos. Go buy some using shop\n";
            return false;
        }

        std::cout << "Select a new dino from the list" << std::endl;
        std::cout << "(you still can 'quit')\n";

        int counter = 0;
        for (auto& it : OwnedDinosaurs) {
            std::cout << "\t[ID " << counter++ << "] Name: " << it.get()->GetName() << ", Type: " << it.get()->GetType();
            std::cout << ", Plain ATK: " << it.get()->damage(Plain) << ", River ATK: " << it.get()->damage(River);
            std::cout << ", Mountain ATK: " << it.get()->damage(Mountain) << std::endl;
        }

        counter--;
        int inputID = -1;

        std::cout << "\nSelect Dino by ID: ";
        
        do
        {
            std::getline(std::cin, answer);
            if (isDigits(answer)) {
                inputID = stoi(answer);
            }
            else if (answer == "quit") {
                return false;
            }
            else {
                continue;
            }
        } while (inputID < 0 || inputID >= OwnedDinosaurs.size());

        if (CurrentParty.size() > inputSlot)
        {
            OwnedDinosaurs.emplace_back(CurrentParty[inputSlot]);
            CurrentParty[inputSlot] = OwnedDinosaurs[inputID];
            std::cout << "Dino[ID " << inputID << "] is a new hotshot in the Slot " << inputSlot << std::endl;
        }
        else {
            std::cout << "Dino[ID " << inputID << "] filled the empty Slot " << inputSlot << std::endl;
            CurrentParty.emplace_back(OwnedDinosaurs[inputID]);
        }

        OwnedDinosaurs.erase(OwnedDinosaurs.begin() + inputID);
        std::cout << '\n';
        ShowDinos(party);
        return true;
    }

    void ThrowDinoOut(int deadDino) {
        CurrentParty.erase(CurrentParty.begin() + deadDino);
    }

    void ShowDinos(ActiveDino dinos) {
        std::vector<std::shared_ptr<Dino>>* dinosToShow;

        if (dinos == party) {
            if (CurrentParty.size() == 0) {
                std::cout << "You have no dinos in your party.\n";
                return;
            }
            dinosToShow = &CurrentParty;
            std::cout << "Your party:\n\n";
        }
        else {
            if (OwnedDinosaurs.size() == 0) {
                std::cout << "You have no resting dinos.\n";
                return;
            }
            dinosToShow = &OwnedDinosaurs;
            std::cout << "Your resting dinos:\n\n";
        }
        
        for (auto& dino : *dinosToShow) {
            std::cout << dino->GetName() << '\n';
            dino->Render();
            std::cout << "Type: " << dino->GetType() << '\n';
            std::cout << "STR: " << dino->GetSTR() << ", DEX: " << dino->GetDEX() << ", INT: " << dino->GetINT() << "\n\n";
        }
        std::cout << '\n';
    }

    void GetLuckyDino() {
        generateDinos(1, &CurrentParty);
        std::shared_ptr<Dino> newDino = CurrentParty[0];
        std::cout << "Congrats! Now you have 1 Dino in your party: ";
        std::cout << "Name: " << newDino->GetName() << ", Type: " << newDino->GetType() << ", Plain ATK: ";
        std::cout << newDino->damage(Terrain::Plain) << ", River ATK: " << newDino->damage(Terrain::River);
        std::cout << ", Mountain ATK, " << newDino->damage(Terrain::Mountain) << std::endl;
    }
};

*/