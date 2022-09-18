#pragma once
#include "CMonster.h"

class CObject;

class CMonsterDog : public CMonster
{
public:
	CMonsterDog(MON_INFO _tMonInfo);
	~CMonsterDog();

public:
	virtual void Initalize();
	virtual int  Update(float _fDeltaTime);
	virtual void LateUpdate(float _fDeltaTime);
	virtual void Render(HDC _hDC);
	virtual void Release();

public:
	void		 DogCurMotion();

private:
	CObject* m_pTarget;

private:
	bool	 m_bDirLeft = false;


	// 피격, 죽었을때 확인
	RECT	m_BOX;
	RECT	m_DeadBOX;
};

