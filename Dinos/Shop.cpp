#include "Shop.h"

void Shop::GenerateShop()
{
	_shopList.clear();
	for (int i = 0; i < 6; i++)
		_shopList.push_back(generateDino());
}
