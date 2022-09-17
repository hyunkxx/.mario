#include "pch.h"
#include "CPotal.h"

#include "CBitmapMgr.h"
#include "CScrollMgr.h"

CPotal::CPotal(float _x, float _y, float _scale)
	: CObject(_x,_y,_scale)
	, m_iCurFrame(0)
	, m_fAnimSpeed(100.f)
{
	ZeroMemory(&m_hSubDC, sizeof(HDC) * 8);

	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/potal/potal_0.bmp", L"potal0");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/potal/potal_1.bmp", L"potal1");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/potal/potal_2.bmp", L"potal2");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/potal/potal_3.bmp", L"potal3");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/potal/potal_4.bmp", L"potal4");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/potal/potal_5.bmp", L"potal5");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/potal/potal_6.bmp", L"potal6");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/potal/potal_7.bmp", L"potal7");

	m_hSubDC[0] = CBitmapMgr::GetInstance()->FindBmp(L"potal0");
	m_hSubDC[1] = CBitmapMgr::GetInstance()->FindBmp(L"potal1");
	m_hSubDC[2] = CBitmapMgr::GetInstance()->FindBmp(L"potal2");
	m_hSubDC[3] = CBitmapMgr::GetInstance()->FindBmp(L"potal3");
	m_hSubDC[4] = CBitmapMgr::GetInstance()->FindBmp(L"potal4");
	m_hSubDC[5] = CBitmapMgr::GetInstance()->FindBmp(L"potal5");
	m_hSubDC[6] = CBitmapMgr::GetInstance()->FindBmp(L"potal6");
	m_hSubDC[7] = CBitmapMgr::GetInstance()->FindBmp(L"potal7");

	begin = GetTickCount64();
}

void CPotal::Initalize()
{
}

int CPotal::Update(float _fDeltaTime)
{
	AnimationTick(m_fAnimSpeed, POTAL_FRAME_MAX);

	return EVENT_SUCCEED;
}

void CPotal::LateUpdate(float _fDeltaTime)
{
}

void CPotal::Render(HDC _hdc)
{
	GdiTransparentBlt(_hdc
		, GetX() + CScrollMgr::GetInst()->GetScrollX()
		, GetY() + CScrollMgr::GetInst()->GetScrollY()
		, POTAL_WITDH
		, POTAL_HEIGHT
		, m_hSubDC[m_iCurFrame]
		, 0, 0, POTAL_WITDH, POTAL_HEIGHT, RGB(0, 0, 0));
} 

void CPotal::Release()
{

}

bool CPotal::AnimationTick(float _fAnimSpeed, int _iFrameCount)
{
	if (GetTickCount64() - begin > _fAnimSpeed)
	{
		if (m_iCurFrame >= _iFrameCount - 1)
			m_iCurFrame = 0;
		else
			m_iCurFrame++;

		begin = GetTickCount64();

		return true;
	}

	return false;
}

