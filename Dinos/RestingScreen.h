#pragma once

#include "PartyScreen.h"

class RestingScreen : public PartyScreen
{
public:
	using PartyScreen::PartyScreen;
private:
	void setScreenData() override;
	void setNewActiveIndex(std::pair<int, int> direction) override;
	void handleDiffPopupChoice(int choice) override;
	void changeDino() override;
	void updateDinoCards() override;
};