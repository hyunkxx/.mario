#pragma once
#include "CMonster.h"

class CMonsterDragon : public CMonster
{
public:
	CMonsterDragon(MON_INFO _tMonInfo);
	~CMonsterDragon();

public:
	virtual void Initalize();
	virtual int  Update(float _fDeltaTime);
	virtual void LateUpdate(float _fDeltaTime);
	virtual void Render(HDC _hDC);
	virtual void Release();

public:
	void		 DragonCurMotion();
	void		 SetTarget(CObject* _pObject) { m_pTarget = _pObject; }

	void		 SkillPosSetting();

private:
	CObject*	 m_pTarget;

private:
	bool		 m_bDirLeft = false;

	vector<int> m_vecSkillPoint;

};

