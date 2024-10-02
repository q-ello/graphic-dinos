#include "LuckyDinoButton.h"

bool LuckyDinoButton::checkCondition()
{
    return Player::owned().empty() && Player::partyIsEmpty() && Player::money() < 50;
}
