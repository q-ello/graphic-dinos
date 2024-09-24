#pragma once

#define C_DULL_GREEN sf::Color(82, 122, 89)
#define C_BRIGHT_GREEN sf::Color(32, 198, 59)
#define C_DARK_GREEN sf::Color(43, 100, 46)
#define C_FOCUSED sf::Color(10, 10, 10)
#define C_EXECUTABLE sf::Color(80, 255, 80)
#define C_POPUP_BG sf::Color(255, 255, 255, 50)

#define SCREEN_SIZE sf::Vector2f(1000, 800)

enum E_Choice
{
	C_NOTHING,
	C_RETURN,
	C_YES,
	C_NO,
	C_FIGHT,
	C_SHOP,
	C_PARTY,
	C_RESTING,
	C_SAVE,
	C_QUIT
};