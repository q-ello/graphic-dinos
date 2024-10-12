#pragma once

#define C_DULL_GREEN sf::Color(82, 122, 89)
#define C_BRIGHT_GREEN sf::Color(32, 198, 59)
#define C_DARK_GREEN sf::Color(43, 100, 46)
#define C_FOCUSED sf::Color(80, 180, 80)
#define C_EXECUTABLE sf::Color(80, 255, 80)
#define C_SEMITRANSPARENT sf::Color(255, 255, 255, 100)
#define C_ALMOST_TRANSPARENT sf::Color(255, 255, 255, 50)
#define C_TRANSPARENT sf::Color(0, 0, 0, 0)
#define C_STR sf::Color(230, 14, 18)
#define C_DEX sf::Color(100, 180, 18)
#define C_INT sf::Color(18, 180, 230)

#define SCREEN_SIZE sf::Vector2f(1000, 800)
#define DINOCARD_SIZE sf::Vector2f(280, 300)

enum E_Choice
{
	C_NOTHING = 10,
	C_RETURN = 11,
	C_YES,
	C_NO,
	C_FIGHT,
	C_SHOP,
	C_PARTY,
	C_RESTING,
	C_SAVE,
	C_QUIT,
	C_LUCKY_DINO,
	C_BUY,
	C_CHANGE
};

enum Terrain { T_Plain, T_River, T_Mountain };
