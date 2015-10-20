/* detector 'SVAROG' from Call of Priryat */

#pragma once
#include "CustomDetector.h"
#include "level.h"
class CUIArtefactDetectorSci;

class CScientificDetector :public CCustomDetector
{
	typedef CCustomDetector	inherited;

public:
	CScientificDetector();
	virtual			~CScientificDetector();

	virtual void	render_item_3d_ui();
	virtual bool	render_item_3d_ui_query();

	virtual void 	Load(LPCSTR section);
	virtual void 	OnH_B_Independent(bool just_before_destroy);
	virtual void 	shedule_Update(u32 dt);
	virtual LPCSTR	ui_xml_tag() const { return "scientific"; }
protected:
	virtual void 	CreateUI();
	CUIArtefactDetectorSci& ui();

	virtual void	UpfateWork();
	CZoneList		m_zones;
};

class CUIArtefactDetectorSci :public CUIArtefactDetectorBase, public CUIWindow
{
	typedef CUIArtefactDetectorBase	inherited;

	CUIWindow*			m_wrk_area;

	xr_map<shared_str, CUIStatic*>	m_palette;

	struct SDrawOneItem{
		SDrawOneItem(CUIStatic* s, const Fvector& p) :pStatic(s), pos(p){}
		CUIStatic*		pStatic;
		Fvector			pos;
	};
	xr_vector<SDrawOneItem>	m_items_to_draw;
	CScientificDetector*			m_parent;
	Fmatrix					m_map_attach_offset;

	void				GetUILocatorMatrix(Fmatrix& _m);
public:

	virtual void	update();
	virtual void	Draw();

	void		construct(CScientificDetector* p);
	void		Clear();
	void		RegisterItemToDraw(const Fvector& p, const shared_str& palette_idx);
};