#pragma once
#include "CObject.h"


enum MONSTER_STATE
{
	MON_IDLE,
	MON_WALK,
	MON_HIT,
	MON_DEAD,
	MON_SKILL_ONE,
	MON_SKILL_TWO,

	MON_END
};

class CMonster : public CObject
{
public:
	CMonster(MON_INFO _eMonInfo);
	CMonster();
	virtual ~CMonster();

public:
	virtual void	Initalize() {}
	virtual int		Update(float _fDeltaTime) { return EVENT_SUCCEED; }
	virtual void	LateUpdate(float _fDeltaTime) {}
	virtual void	Render(HDC _hdc) {}
	virtual void	Release() {}

	vector<RECT>	GetMonSkillRect() { return m_vecMonSKill; }
	void			ClearMonBox();

protected:
	void			SetMonRect();
	void			SetMonSKillRect(MON_INFO _tMonInfo);

	void			MoveFrame();

protected:
	MON_INFO m_tMonInfo;
	MON_INFO m_tMonSkiLLInfo;
	// RECT	 m_tMonRect;
	FRAME    m_tMonFrame;
	FRAME    m_tMonSkillFrame;

	float 	 m_fSpeed;
	float	 m_fSkillDistance;
	float	 m_fTargetX;

protected:
	bool			 m_bIsDead = false;
	bool			 m_bIsSkillOn = false;
	bool			 m_bIsHit = false;
	bool			 m_bIsSkillTwoOn = false;

	MONSTER_STATE	 m_eMonCurState = MON_END;
	MONSTER_STATE	 m_eMonPreState = MON_END;;
					 
	DWORD	   		 m_dwMonTimer;
	RECT			 m_rtMonSKillRect;

	vector<RECT>	 m_vecMonSKill;

};

