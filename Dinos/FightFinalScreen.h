#pragma once
#include "ScreenEmptyBase.h"

class FightFinalScreen : public ScreenEmptyBase
{
public:
	using ScreenEmptyBase::ScreenEmptyBase;
	FightFinalScreen(sf::RenderWindow* window, const std::string& verdict, sf::Texture* texture);
private:
	sf::Texture* _texture;
	void createBG() override;
	void goToNextScreen() override;
};