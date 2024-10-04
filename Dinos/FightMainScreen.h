#pragma once
#include "ScreenBase.h"

class FightMainScreen : ScreenBase
{
public:
	using ScreenBase::ScreenBase;
	FightMainScreen(sf::RenderWindow* window, sf::Texture* texture, Terrain terrain)
		: ScreenBase(window)
		, _texture {texture}
		, _terrain {terrain}
	{};
private:
	sf::Texture* _texture;
	Terrain _terrain;
	boolean _isAnimating;
	std::vector<Dino*> _enemies{};
	sf::Text _turn;
	sf::Text _escapeButton;

	void setScreenData() override;
	void createBG() override;
	void drawData() override;
};