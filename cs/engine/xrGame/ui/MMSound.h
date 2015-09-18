#pragma once

class CUIXml;

class CMMSound
{
public:
					CMMSound	();
					~CMMSound	();
	void 			Init		(CUIXml& xml_doc, LPCSTR path);
	void 			whell_Play	();
	void 			whell_Stop	();
	void 			whell_Click	();
	void 			whell_UpdateMoving(float frequency);

	void 			music_Play	();
	void 			music_Stop	();
	void 			music_Update();

	void 			all_Stop	();
	void 			music_prev_track();
	void 			music_next_track();
protected:

	IC	bool		check_file			(LPCSTR fname);

	ref_sound		m_music_stereo;

	ref_sound		m_whell;
	ref_sound		m_whell_click;
	bool			m_bRandom;
#ifdef RND_MM_SOUND
	s32			m_iCurrentTrack;
#endif
	xr_vector<xr_string>m_play_list;
};
