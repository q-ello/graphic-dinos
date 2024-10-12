#pragma once
#include "ScreenEmptyBase.h"
#include "FightMainScreen.h"

class FightWelcomeScreen : public ScreenEmptyBase
{
public:
	using ScreenEmptyBase::ScreenEmptyBase;
private:
	void setScreenData() override;
	void createBG() override;

	Terrain _terrain;
	sf::Texture _texture;

	void goToNextScreen() override;
};