#pragma once
#include "CMonster.h"

class CMonsterSlime : public CMonster
{
public:
	CMonsterSlime(MON_INFO _tMonInfo);
	~CMonsterSlime();

public:
	virtual void Initalize();
	virtual int  Update(float _fDeltaTime);
	virtual void LateUpdate(float _fDeltaTime);
	virtual void Render(HDC _hDC);
	virtual void Release();

public:
	void		 SlimeCurMotion();


private:
	bool	 m_bDirLeft = false;


	// �ǰ�, �׾����� Ȯ��
	RECT	m_BOX;
	RECT	m_DeadBOX;
};

