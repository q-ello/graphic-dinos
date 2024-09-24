#include "ShopScreen.h"

void ShopScreen::setScreenData()
{
	updateShop();
	const int listSize = static_cast<int>(_shopList.size());

	const int xPos = 50;
	const int yPos = 100;
	const int xOffset = 300;
	const int yOffset = 400;
	for (int i = 0; i < listSize; i++)
	{
		_shopList[i]->setDataForDrawing(sf::Vector2f(xPos + xOffset * (i % 3), 
			yPos + yOffset * std::floor(i / 3)));
	}
}

void ShopScreen::drawData()
{
	for (auto& dino : _shopList)
	{
		dino->drawForShop(_window);
	}
}

void ShopScreen::updateShop()
{
	_shopList.clear();
	for (int i = 0; i < 6; i++)
	{
		_shopList.push_back(Dino::generateDino());
	}
}
