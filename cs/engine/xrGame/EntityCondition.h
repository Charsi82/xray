#pragma once

class CWound;
class NET_Packet;
class CEntityAlive;
class CLevel;

#include "hit_immunity.h"
#include "Hit.h"
#include "Level.h"

class CEntityConditionSimple
{
	float					m_fHealth;
	float					m_fHealthMax;
public:
							CEntityConditionSimple	();
	virtual					~CEntityConditionSimple	();

	IC		 float				GetHealth				() const			{return m_fHealth;}
	IC		 void				SetHealth				( float value ) 	{ m_fHealth = value; }
	IC		 float 				GetMaxHealth			() const			{return m_fHealthMax;}
	IC const float&				health					() const			{return	m_fHealth;}
	IC		 float&				max_health				()					{return	m_fHealthMax;}
};

class CEntityCondition: public CEntityConditionSimple, public CHitImmunity
{
private:
	bool					m_use_limping_state;
	CEntityAlive			*m_object;

public:
							CEntityCondition		(CEntityAlive *object);
	virtual					~CEntityCondition		(void);

	virtual void			LoadCondition			(LPCSTR section);
	virtual void			remove_links			(const CObject *object);

	virtual void			save					(NET_Packet &output_packet);
	virtual void			load					(IReader &input_packet);

	IC float				GetPower				() const			{return m_fPower;}	
	IC float				GetRadiation			() const			{return m_fRadiation;}
	IC float				GetPsyHealth			() const			{return m_fPsyHealth;}

	IC float 				GetEntityMorale			() const			{return m_fEntityMorale;}

	IC float 				GetHealthLost			() const			{return m_fHealthLost;}

	virtual bool 			IsLimping				() const;

	virtual float			GetSatiety()					{ return 0.f; }; //+
	virtual float xr_stdcall	GetAlcohol()					{ return 0.f; };//+
	virtual void			ChangeSatiety			(float value)		{};
	void 					ChangeHealth			(float value);
	void 					ChangePower				(float value);
	void 					ChangeRadiation			(float value);
	void 					ChangePsyHealth			(float value);
	virtual void 			ChangeAlcohol			(float value){};

	IC void					MaxPower				()					{m_fPower = m_fPowerMax;};
	IC void					SetMaxPower				(float val)			{m_fPowerMax = val; clamp(m_fPowerMax,0.1f,1.0f);};
	IC float				GetMaxPower				() const			{return m_fPowerMax;};

	void 					ChangeBleeding			(float percent);

	void 					ChangeCircumspection	(float value);
	void 					ChangeEntityMorale		(float value);

	virtual CWound*			ConditionHit			(SHit* pHDS);
	//îáíîâëåíèÿ ñîñòîÿíèÿ ñ òå÷åíèåì âðåìåíè
	virtual void			UpdateCondition			();
	void					UpdateWounds			();
	void					UpdateConditionTime		();
	IC void					SetConditionDeltaTime	(float DeltaTime) { m_fDeltaTime = DeltaTime; };

	
	//ñêîðîñòü ïîòåðè êðîâè èç âñåõ îòêðûòûõ ðàí 
	float					BleedingSpeed			();

	CObject*				GetWhoHitLastTime		() {return m_pWho;}
	u16						GetWhoHitLastTimeID		() {return m_iWhoID;}

	CWound*					AddWound				(float hit_power, ALife::EHitType hit_type, u16 element);

	IC void 				SetCanBeHarmedState		(bool CanBeHarmed) 			{m_bCanBeHarmed = CanBeHarmed;}
	IC bool					CanBeHarmed				() const					{return OnServer() && m_bCanBeHarmed;};
	
	void					ClearWounds();
protected:
	void					UpdateHealth			();
	void					UpdatePower				();
	virtual void			UpdateRadiation			();
	void					UpdatePsyHealth			();

	void					UpdateEntityMorale		();


	//èçìåíåíèå ñèëû õèòà â çàâèñèìîñòè îò íàäåòîãî êîñòþìà
	//(òîëüêî äëÿ InventoryOwner)
	float					HitOutfitEffect			(float hit_power, ALife::EHitType hit_type, s16 element, float ap, bool& add_wound );
	//èçìåíåíèå ïîòåðè ñèë â çàâèñèìîñòè îò íàäåòîãî êîñòþìà
	float					HitPowerEffect			(float power_loss);
	
	//äëÿ ïîäñ÷åòà ñîñòîÿíèÿ îòêðûòûõ ðàí,
	//çàïîìèíàåòñÿ êîñòü êóäà áûë íàíåñåí õèò
	//è ñêîðîñòü ïîòåðè êðîâè èç ðàíû
	using WOUND_VECTOR = xr_vector<CWound*>;
	using WOUND_VECTOR_IT = WOUND_VECTOR::iterator;
	WOUND_VECTOR			m_WoundVector;
	//î÷èñòêà ìàññèâà ðàí
	

	//âñå âåëè÷èíû îò 0 äî 1			
	float m_fPower;					//ñèëà
	float m_fRadiation;				//äîçà ðàäèàêòèâíîãî îáëó÷åíèÿ
	float m_fPsyHealth;				//çäîðîâüå

	float m_fEntityMorale;			//ìîðàëü

	//ìàêñèìàëüíûå âåëè÷èíû
	//	float m_fSatietyMax;
	float m_fPowerMax;
	float m_fRadiationMax;
	float m_fPsyHealthMax;

	float m_fEntityMoraleMax;

	//âåëè÷èíû èçìåíåíèÿ ïàðàìåòðîâ íà êàæäîì îáíîâëåíèè
	float m_fDeltaHealth;
	float m_fDeltaPower;
	float m_fDeltaRadiation;
	float m_fDeltaPsyHealth;

	float m_fDeltaCircumspection;
	float m_fDeltaEntityMorale;

	struct SConditionChangeV
	{
		float			m_fV_Radiation;
		float			m_fV_PsyHealth;
		float			m_fV_Circumspection;
		float			m_fV_EntityMorale;
		float			m_fV_RadiationHealth;
		float			m_fV_Bleeding;
		float			m_fV_WoundIncarnation;
		float			m_fV_HealthRestore;
		void			load(LPCSTR sect, LPCSTR prefix);
	};
	
	SConditionChangeV m_change_v;

	float				m_fMinWoundSize;
	bool				m_bIsBleeding;		//åñòü êðîâîòå÷åíèå

	//÷àñòè õèòà, çàòðà÷èâàåìûå íà óìåíüøåíèå çäîðîâüÿ è ñèëû
	float				m_fHealthHitPart;
	float				m_fPowerHitPart;


	//ïîòåðÿ çäîðîâüÿ îò ïîñëåäíåãî õèòà
	float				m_fHealthLost;


	//äëÿ îòñëåæèâàíèÿ âðåìåíè 
	u64					m_iLastTimeCalled;
	float				m_fDeltaTime;
	//êòî íàíåñ ïîñëåäíèé õèò
	CObject*			m_pWho;
	u16					m_iWhoID;

	//äëÿ ïåðåäà÷è ïàðàìåòðîâ èç DamageManager
	float				m_fHitBoneScale;
	float				m_fWoundBoneScale;

	float				m_limping_threshold;

	bool				m_bTimeValid;
	bool				m_bCanBeHarmed;

public:
	virtual void					reinit				();
	
	IC const	float				fdelta_time			() const 	{return		(m_fDeltaTime);			}
	IC const	WOUND_VECTOR&		wounds				() const	{return		(m_WoundVector);		}
	IC float&						radiation			()			{return		(m_fRadiation);			}
	IC float&						hit_bone_scale		()			{return		(m_fHitBoneScale);		}
	IC float&						wound_bone_scale	()			{return		(m_fWoundBoneScale);	}
	IC SConditionChangeV&			change_v			()			{return		(m_change_v);			}

};
