#pragma once

#include "CObject.h"

class CPotal : public CObject 
{
public:
	CPotal(float _x, float _y, float _scale);
public:
	void Initalize() override;
	int  Update(float _fDeltaTime) override;
	void LateUpdate(float _fDeltaTime) override;
	void Render(HDC _hdc) override;
	void Release() override;
public:
	bool AnimationTick(float _fAnimSpeed, int _iFrameCount);
private:
	void collisionPosUpdate();
public:
	enum
	{
		POTAL_WIDTH  = 134,
		POTAL_HEIGHT = 172,
		POTAL_FRAME_MAX = 8
	};
	RECT m_CollisionRect;
	wstring m_szImageName[POTAL_FRAME_MAX];
	HDC m_hSubDC[POTAL_FRAME_MAX];
	int m_iCurFrame;
	float m_fAnimSpeed;
	ULONGLONG begin, end;
};

