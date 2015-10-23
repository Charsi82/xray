#pragma once

#include "WeaponMagazinedWGrenade.h"
#include "script_export_space.h"

class CUIFrameWindow;
class CUIStatic;
class CBinocularsVision;

class CWeaponZoomable : public CWeaponMagazinedWGrenade
{
private:
	typedef CWeaponMagazinedWGrenade inherited;

protected:
	float			m_fRTZoomFactor; //run-time zoom factor
	bool			m_bVision;
	CBinocularsVision*					m_binoc_vision;

public:
	CWeaponZoomable(ESoundTypes eSoundType = SOUND_TYPE_WEAPON_SUBMACHINEGUN);
	virtual			~CWeaponZoomable();

	void			Load(LPCSTR section);

	virtual void	OnZoomIn();
	virtual void	OnZoomOut();
	virtual	void	ZoomInc();
	virtual	void	ZoomDec();
	virtual void	net_Destroy();
	virtual BOOL	net_Spawn(CSE_Abstract* DC);
	virtual void	UpdateCL();
	virtual void	render_item_ui();
	virtual bool	Action(s32 cmd, u32 flags);
	virtual void	net_Relcase(CObject *object);

	DECLARE_SCRIPT_REGISTER_FUNCTION
};
add_to_type_list(CWeaponZoomable)
#undef script_type_list
#define script_type_list save_type_list(CWeaponZoomable)