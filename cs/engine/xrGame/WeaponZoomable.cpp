#include "stdafx.h"
#include "WeaponZoomable.h"

#include "xr_level_controller.h"

#include "Level.h"
#include "ui\UIFrameWindow.h"
#include "WeaponBinocularsVision.h"
#include "object_broker.h"
#include "hudmanager.h"
#include "inventory.h"

void GetZoomData(const float scope_factor, float& delta, float& min_zoom_factor);

CWeaponZoomable::CWeaponZoomable(ESoundTypes eSoundType) : CWeaponMagazinedWGrenade(eSoundType)
{
	m_binoc_vision = NULL;
	m_bVision = false;
}

CWeaponZoomable::~CWeaponZoomable()
{
	xr_delete(m_binoc_vision);
}

void CWeaponZoomable::Load(LPCSTR section)
{
	inherited::Load(section);

	// Sounds
	m_sounds.LoadSound(section, "snd_zoomin", "sndZoomIn", SOUND_TYPE_ITEM_USING);
	m_sounds.LoadSound(section, "snd_zoomout", "sndZoomOut", SOUND_TYPE_ITEM_USING);
	m_bVision = !!pSettings->r_bool(section, "vision_present");
}

void CWeaponZoomable::OnZoomIn()
{
	if (H_Parent() && !IsZoomed())
	{
		m_sounds.StopSound("sndZoomOut");
		bool b_hud_mode = (Level().CurrentEntity() == H_Parent());
		m_sounds.PlaySound("sndZoomIn", H_Parent()->Position(), H_Parent(), b_hud_mode);
		if (m_bVision && !m_binoc_vision)
		{
			//.VERIFY			(!m_binoc_vision);
			m_binoc_vision = new CBinocularsVision(cNameSect());
		}
	}

	inherited::OnZoomIn();

	if (!ZoomTexture())
		m_fRTZoomFactor = pSettings->r_float(cNameSect(), "scope_zoom_factor");

	SetZoomFactor(m_fRTZoomFactor);
}

void CWeaponZoomable::OnZoomOut()
{
	if (H_Parent() && IsZoomed() && !IsRotatingToZoom())
	{		
		m_sounds.StopSound("sndZoomIn");
		bool b_hud_mode = (Level().CurrentEntity() == H_Parent());
		m_sounds.PlaySound("sndZoomOut", H_Parent()->Position(), H_Parent(), b_hud_mode);
		VERIFY(m_binoc_vision);
		xr_delete(m_binoc_vision);

		m_fRTZoomFactor = GetZoomFactor();//store current
	}

	inherited::OnZoomOut();
}

BOOL CWeaponZoomable::net_Spawn(CSE_Abstract* DC)
{
	m_fRTZoomFactor = m_zoom_params.m_fScopeZoomFactor;
	inherited::net_Spawn(DC);
	return					TRUE;
}

void CWeaponZoomable::net_Destroy()
{
	inherited::net_Destroy();
	xr_delete(m_binoc_vision);
}

void CWeaponZoomable::UpdateCL()
{
	inherited::UpdateCL();
	//manage visible entities here...
	if (H_Parent() && IsZoomed() && !IsRotatingToZoom() && m_binoc_vision && ZoomTexture())
		m_binoc_vision->Update();
}

bool CWeaponZoomable::Action(s32 cmd, u32 flags)
{
	switch (cmd)
	{
	case kWPN_FUNC:
		if (flags&CMD_START && ZoomTexture())
		{
			m_bVision = !m_bVision;
			if (m_bVision)
			{
				m_binoc_vision = new CBinocularsVision(cNameSect());
			}
			else
			{
				xr_delete(m_binoc_vision);
				m_binoc_vision = NULL;
			}
		}				
		if (IsZoomed()) return true;
	}

	return inherited::Action(cmd, flags);
}

/*bool CWeaponZoomable::render_item_ui_query()
{
	//bool b_is_active_item = m_pInventory->ActiveItem() == this;
	//return b_is_active_item && H_Parent() && IsZoomed() && !IsRotatingToZoom() && m_binoc_vision;
	return inherited::render_item_ui_query();
}*/

void CWeaponZoomable::render_item_ui()
{
	if (m_binoc_vision) m_binoc_vision->Draw();
	inherited::render_item_ui();
}

void CWeaponZoomable::ZoomInc()
{
	if (ZoomTexture())
	{
		float delta, min_zoom_factor;
		GetZoomData(m_zoom_params.m_fScopeZoomFactor, delta, min_zoom_factor);

		float f = GetZoomFactor() - delta;
		clamp(f, m_zoom_params.m_fScopeZoomFactor, min_zoom_factor);
		SetZoomFactor(f);
	}
	
}

void CWeaponZoomable::ZoomDec()
{
	if (ZoomTexture())
	{
		float delta, min_zoom_factor;
		GetZoomData(m_zoom_params.m_fScopeZoomFactor, delta, min_zoom_factor);

		float f = GetZoomFactor() + delta;
		clamp(f, m_zoom_params.m_fScopeZoomFactor, min_zoom_factor);
		SetZoomFactor(f);
	}
}

void CWeaponZoomable::net_Relcase(CObject *object)
{
	if (!m_binoc_vision)
		return;

	m_binoc_vision->remove_links(object);
}

/*
using namespace luabind;

#pragma optimize("s",on)
void CWeaponZoomable::script_register(lua_State *L)
{
	module(L)
		[
			class_<CWeaponZoomable, CGameObject>("CWeaponAK74SZ")
			.def(constructor<>())
		];
}*/