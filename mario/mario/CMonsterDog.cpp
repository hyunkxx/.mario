#include "pch.h"
#include "CMonsterDog.h"
#include "CBitmapMgr.h"
#include "CObject.h"
#include "CScrollMgr.h"

CMonsterDog::CMonsterDog(MON_INFO _tMonInfo) : CMonster(_tMonInfo), m_pTarget(nullptr)
{
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Dog/DogMoveL.bmp", L"DogMoveL");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Dog/DogMoveR.bmp", L"DogMoveR");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Dog/DogDie.bmp", L"DogDie");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Dog/DogHitL.bmp", L"DogHitL");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Dog/DogHitR.bmp", L"DogHitR");

	m_eMonCurState = MON_WALK;
	m_eMonPreState = MON_IDLE;

	m_fSpeed = 0.5;
}

CMonsterDog::~CMonsterDog()
{

}

void CMonsterDog::Initalize()
{

}

int CMonsterDog::Update(float _fDeltaTime)
{
	SetMonRect();
	DogCurMotion();
	MoveFrame();

	if (m_tMonInfo.fY <= 523)
		m_tMonInfo.fY += 3.f;

	if (!m_bIsDead && m_eMonCurState == MON_WALK)
		m_tMonInfo.fX += m_fSpeed;


	return EVENT_SUCCEED;
}

void CMonsterDog::LateUpdate(float _fDeltaTime)
{
	if (m_tMonInfo.fX >= (WIDTH - CScrollMgr::GetInst()->GetScrollX() - 30) || m_tMonInfo.fX <= 0 + CScrollMgr::GetInst()->GetScrollX())
	{
		m_fSpeed *= -1.f;
		if (m_bDirLeft)
			m_bDirLeft = false;
		else
			m_bDirLeft = true;
	}

	// 벽이랑 충돌 예정
}

void CMonsterDog::Render(HDC _hDC)
{
	int iScrollX = (int)CScrollMgr::GetInst()->GetScrollX();
	int iScrollY = (int)CScrollMgr::GetInst()->GetScrollY();

	if (m_bIsDead)
	{
		HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"DogDie");

		GdiTransparentBlt(_hDC,
			(int)m_rcRect.left + iScrollX,
			(int)m_rcRect.top + iScrollY,
			(int)m_tMonInfo.fCX,
			(int)m_tMonInfo.fCY,
			hMemDC,
			192 * m_tMonFrame.iStart,
			288 * m_tMonFrame.iMotion,
			192,
			288,
			RGB(0, 255, 0));

		//m_tMonInfo.fX -= 1.f;
	}
	else if (!m_bDirLeft)
	{
		if (m_bIsHit)
		{
			HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"DogHitR");

			GdiTransparentBlt(_hDC,
				(int)m_rcRect.left + iScrollX,
				(int)m_rcRect.top + iScrollY,
				(int)m_tMonInfo.fCX,
				(int)m_tMonInfo.fCY,
				hMemDC,
				0,
				0,
				166,
				166,
				RGB(0, 255, 0));

			m_tMonInfo.fX -= 1.f;
		}

		if (!m_bIsHit)
		{
			HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"DogMoveR");

			GdiTransparentBlt(_hDC,
				(int)m_rcRect.left + iScrollX,
				(int)m_rcRect.top + iScrollY,
				(int)m_tMonInfo.fCX,
				(int)m_tMonInfo.fCY,
				hMemDC,
				(int)m_tMonInfo.fCX * m_tMonFrame.iStart,
				(int)m_tMonInfo.fCY * m_tMonFrame.iMotion,
				(int)m_tMonInfo.fCX,
				(int)m_tMonInfo.fCY,
				RGB(0, 255, 0));
		}
	}
	else if (m_bDirLeft)
	{
		if (m_bIsHit)
		{
			HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"DogHitL");

			GdiTransparentBlt(_hDC,
				(int)m_rcRect.left + iScrollX,
				(int)m_rcRect.top + iScrollY,
				(int)m_tMonInfo.fCX,
				(int)m_tMonInfo.fCY,
				hMemDC,
				0,
				0,
				166,
				166,
				RGB(0, 255, 0));

			m_tMonInfo.fX += 1.f;
		}
		else
		{
			HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"DogMoveL");

			GdiTransparentBlt(_hDC,
				(int)m_rcRect.left + iScrollX,
				(int)m_rcRect.top + iScrollY,
				(int)m_tMonInfo.fCX,
				(int)m_tMonInfo.fCY,
				hMemDC,
				(int)m_tMonInfo.fCX * m_tMonFrame.iStart,
				(int)m_tMonInfo.fCY * m_tMonFrame.iMotion,
				(int)m_tMonInfo.fCX,
				(int)m_tMonInfo.fCY,
				RGB(0, 255, 0));
		}
	}

	if (m_bIsHit)
		m_bIsHit = false;
}

void CMonsterDog::DogCurMotion()
{
	if (m_eMonCurState != m_eMonPreState)
	{
		switch (m_eMonCurState)
		{
		case MON_IDLE:
			m_tMonFrame.iStart = 0;
			m_tMonFrame.iEnd = 8;
			m_tMonFrame.iMotion = 0;
			m_tMonFrame.dwSpeed = 200;
			m_tMonFrame.dwTime = GetTickCount();
			break;
		case MON_WALK:
			m_tMonFrame.iStart = 0;
			m_tMonFrame.iEnd = 8;
			m_tMonFrame.iMotion = 0;
			m_tMonFrame.dwSpeed = 200;
			m_tMonFrame.dwTime = GetTickCount();
			break;

		case MON_HIT:
			m_tMonFrame.iStart = 0;
			m_tMonFrame.iEnd = 1;
			m_tMonFrame.iMotion = 0;
			m_tMonFrame.dwSpeed = 250;
			m_tMonFrame.dwTime = GetTickCount();
			break;

		case MON_DEAD:
			m_tMonFrame.iStart = 0;
			m_tMonFrame.iEnd = 8;
			m_tMonFrame.iMotion = 0;
			m_tMonFrame.dwSpeed = 200;
			m_tMonFrame.dwTime = GetTickCount();
			break;
		default:
			break;

		}
	}

	m_eMonPreState = m_eMonCurState;
}

void CMonsterDog::Release()
{

}

