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

    static std::vector<std::shared_ptr<Dino>> owned()
    {
        return _ownedDinosaurs;
    }

    static std::vector<std::shared_ptr<Dino>> party()
    {
        return _currentParty;
    }

    static void save();

    static void addCash(int income)
    {
        _money = _money + income >= 0 ? _money + income : 0;
    }

    static void addDino(std::shared_ptr<Dino> newDino);

    static void load();

    static void changeDino(int partyIndex, int restingIndex);

    static boolean partyIsEmpty();

    static Terrain newTerrain();

    static void dinoDied(std::shared_ptr<Dino> dino);
private:
	static int _money;
    static std::vector<std::shared_ptr<Dino>> _ownedDinosaurs;
    static std::vector<std::shared_ptr<Dino>> _currentParty;
    static int _restingIndex;
};
