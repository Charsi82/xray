#include "stdafx.h"
#include "holder_custom.h"
#include "pch_script.h"
#include "script_callback_ex.h"
#include "script_game_object.h"
#include "game_object_space.h"
#include "Actor.h"

bool CHolderCustom::attach_Actor(CGameObject* actor)
{
	m_owner						= actor;
	m_ownerActor				= smart_cast<CActor*>(actor);
	CObject* pObj = smart_cast<CObject*>(this);
	Actor()->callback(GameObject::eAttachVehicle)(pObj->ID());
	return true;
}

void CHolderCustom::detach_Actor()
{
	CObject* pObj = smart_cast<CObject*>(this);
	Actor()->callback(GameObject::eDetachVehicle)(pObj->ID());
	m_owner						= NULL;
	m_ownerActor				= NULL;
}
