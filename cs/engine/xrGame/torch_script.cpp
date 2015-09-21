#include "pch_script.h"
#include "torch.h"

using namespace luabind;

#pragma optimize("s",on)
void CTorch::script_register	(lua_State *L)
{
	module(L)
	[
		class_<CTorch,CGameObject>("CTorch")
			.def(constructor<>())
			.def("is_active", &CTorch::GetTorchStatus)
			.def("is_nv_active", &CTorch::GetNightVisionStatus)
	];
}
