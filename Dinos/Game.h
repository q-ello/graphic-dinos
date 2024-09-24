#pragma once
#include "./stdafx.h"

enum GroupType { Party, Resting };

class Game
{
public:
    Game();
    ~Game();

private:

    void start();

    sf::RenderWindow _window;
};

/*
class Console {
public:
    Console() {
        player = new Player();
        shop = new Shop();
        PrintIntro();
    }
    void ClearScreen()
    {
        system("cls");
    }
    void PrintIntro() {
        ClearScreen();
        std::cout << "Money: " << player->GetMoney() << std::endl;
        std::cout << "Your party: " << player->GetParty().size() << " dino";
        if (player->GetParty().size() != 1) {
            std::cout << 's';
        }
        std::cout << '\n';
        std::cout << "Your resting dinos: " << player->getOwnedDinos().size() << " dino";
        if (player->getOwnedDinos().size() != 1) {
            std::cout << 's';
        }
        std::cout << '\n';
        std::cout << "Available commands:" << std::endl;
        std::cout << "\tgetparty - look at your party\n";
        std::cout << "\tgetslackers - look at your resting dinos\n";
        std::cout << "\tsetdino - switch your party members" << std::endl;
        std::cout << "\tshop - visit a Dino shop" << std::endl;
        std::cout << "\tshopupdate - get new Dinos to the shop" << std::endl;
        std::cout << "\tstartfight - init a fight" << std::endl;
        std::cout << "\tfight - get right into the fight" << std::endl;
        std::cout << "\tconcede - run away before the fight is started" << std::endl;
        std::cout << "\taskfortune - generate one random dino (if you have no money to buy some)" << std::endl;
        std::cout << "\tback - back to main screen" << std::endl;
        std::cout << "\tquit - quit for good" << std::endl;

    }

    bool GetCommand() {
        std::string inputCommand;
        while (true) {
            std::cin >> inputCommand;
            if (!AnalyzeCommand(inputCommand)) {
                return false;
            }
        }
    }

    bool AnalyzeCommand(std::string inputCommand) {
        player->Save();
        PrintIntro();
        if (inputCommand == "startfight") {
            std::cout << "Starting fight!" << std::endl;
            fight = new Fight(static_cast<int>(player->GetParty().size()));
            return true;
        }
        if (inputCommand == "fight") {
            if (!fight)
            {
                std::cout << "You need to find a fight first! Use startfight" << std::endl;
                return true;
            }
            fight->FightLoop(player);
            fight = nullptr;
            return true;
        }
        if (inputCommand == "concede")
        {
            if (!fight)
            {
                std::cout << "There is no fight to run away from" << std::endl;
                return true;
            }
            int lostMoney = fight->GetEnemyCount() * 25;
            std::cout << "You tactically ran away before the fight started. Enemy got some of your money [-" << lostMoney << "]" << std::endl;
            player->AddCash(-1 * lostMoney);
            fight = nullptr;
            std::cout << "Now you have " << player->GetMoney() << '\n';
            return true;
        }
        if (inputCommand == "shop")
        {
            if (fight) {
                std::cout << "Nah, honey, you can't go to the shop while some dino can bite you in the back\n";
                return true;
            }
            if (shop->BuyDino(player)) {
                return true;
            }
            else {
                ClearScreen();
                PrintIntro();
            }
        }
        if (inputCommand == "shopupdate")
        {
            if (fight) {
                std::cout << "That is really not a good time for that...\n";
                return true;
            }
            shop->GenerateShop();
            std::cout << "New dinos are available at the shop!" << std::endl;
            return true;
        }
        if (inputCommand == "setdino")
        {
            if (fight)
            {
                std::cout << "Your dinos can't breach the enemy defences. Can't update your party" << std::endl;
                return true;
            }
            if (player->SetDinos()) {
                return true;
            }
            else {
                ClearScreen();
                PrintIntro();
            }

        }

        if (inputCommand == "getparty") {
            player->ShowDinos(party);
            return true;
        }

        if (inputCommand == "getslackers") {
            player->ShowDinos(owned);
            return true;
        }

        if (inputCommand == "back") {
            if (fight) {
                std::cout << "You can't just come back in the middle of a fight. You can 'concede' though, losing some money on the way\n";
                return true;
            }
            ClearScreen();
            PrintIntro();
            return true;
        }

        if (inputCommand == "askfortune") {
            if (fight) {
                std::cout << "You are in a battle, so behave like a soldier. No fortune, no luck, only strength\n";
                return true;
            }
            else if (player->GetParty().size() + player->getOwnedDinos().size() > 0) {
                std::cout << "You still have dinosauruses, go away\n";
                return true;
            }
            else if (player->GetMoney() >= 50) {
                std::cout << "You have enough money to buy a dinosaur, go away you cheater\n";
                return true;
            }

            else {
                player->GetLuckyDino();
                return true;
            }
        }

        if (inputCommand == "quit") {
            return false;
        }
    }
private:
    Player* player;
    Shop* shop;
    Fight* fight;
};
*/