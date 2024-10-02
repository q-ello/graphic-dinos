#pragma once

#include "Button.h"
#include "Player.h"

class LuckyDinoButton : public Button
{
public:
	using Button::Button;
	bool checkCondition() override;
};