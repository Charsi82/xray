#include "stdafx.h"
#include "car.h"
#include "UIGameSP.h"
#include "HudManager.h"
#include "inventory_item.h"
#include "Actor.h"

void CCar::AddAvailableItems(TIItemContainer& items_container) const
{
	xr_vector<u16>::const_iterator it = m_items.begin();
	xr_vector<u16>::const_iterator it_e = m_items.end();

	for (; it != it_e; ++it)
	{
		PIItem itm = smart_cast<PIItem>(Level().Objects.net_Find(*it)); VERIFY(itm);
		items_container.push_back(itm);
	}
}

void CCar::ShowTrunk()
{
//	CUIGameSP* pGameSP = smart_cast<CUIGameSP*>(HUD().GetUI()->UIGame());
//	if (pGameSP) pGameSP->StartCarBody(Actor(), this);
}
