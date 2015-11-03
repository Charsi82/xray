#include "stdafx.h"
#include "Car.h"
#include "UIGameSP.h"
#include "HudManager.h"
#include "Actor.h"

void CCar::ShowTrunk()
{
	CUIGameSP* pGameSP = smart_cast<CUIGameSP*>(HUD().GetUI()->UIGame());
	if (pGameSP) pGameSP->StartCarBody(Actor(), this);
}
