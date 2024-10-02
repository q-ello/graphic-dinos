#pragma once
#include "Popup.h"
#include "Dino.h"
#include "Player.h"
#include "DinoCard.h"

class DinoPopup : public Popup
{
public:
	using Popup::Popup;
	DinoPopup(boolean isParty);
};