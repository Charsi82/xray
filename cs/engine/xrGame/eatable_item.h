#pragma once

#include "inventory_item.h"

class CPhysicItem;
class CEntityAlive;

class CEatableItem : public CInventoryItem {
private:
	typedef CInventoryItem	inherited;

private:
	CPhysicItem		*m_physic_item;

public:
							CEatableItem				();
	virtual					~CEatableItem				();
	virtual	DLL_Pure*		_construct					();
	virtual CEatableItem	*cast_eatable_item			()	{return this;}

	virtual void			Load						(LPCSTR section);
	virtual bool			Useful						() const;

	virtual BOOL			net_Spawn					(CSE_Abstract* DC);

	virtual void			OnH_B_Independent			(bool just_before_destroy);
	virtual void			OnH_A_Independent			();
	virtual	void			UseBy						(CEntityAlive* npc);
	virtual	bool			Empty						()						{return PortionsNum()==0;};
			int				PortionsNum					()	const				{return m_iPortionsNum;}
protected:	
	//âëèÿíèå ïðè ïîåäàíèè âåùè íà ïàðàìåòðû èãðîêà
	float					m_fHealthInfluence;
	float					m_fPowerInfluence;
	float					m_fSatietyInfluence;
	float					m_fRadiationInfluence;
	float					m_fMaxPowerUpInfluence;
	float					m_fPsyHealthInfluence;
	//çàæèâëåíèå ðàí íà êîë-âî ïðîöåíòîâ
	float					m_fWoundsHealPerc;

	//êîëè÷åñòâî ïîðöèé åäû, 
	//-1 - ïîðöèÿ îäíà è áîëüøå íå áûâàåò (÷òîá íå âûâîäèòü íàäïèñü â ìåíþ)
	int						m_iPortionsNum;
	int						m_iStartPortionsNum;
};

