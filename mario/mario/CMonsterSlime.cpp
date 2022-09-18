#include "pch.h"
#include "CMonsterSlime.h"
#include "CBitmapMgr.h"
#include "CObject.h"
#include "CScrollMgr.h"

CMonsterSlime::CMonsterSlime(MON_INFO _eMonInfo)
	: CMonster(_eMonInfo)
{
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Slime/SlimeMoveL.bmp", L"SlimeMoveL");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Slime/SlimeMoveR.bmp", L"SlimeMoveR");

	/*m_BOX.left = 700;
	m_BOX.top = 500.f;
	m_BOX.right = 750.f;
	m_BOX.bottom = 630.f;

	m_DeadBOX.left = 1200;
	m_DeadBOX.top = 500;
	m_DeadBOX.right = 1300;
	m_DeadBOX.bottom = 630;*/

	m_eMonCurState = MON_IDLE;
	m_eMonPreState = MON_END;
	m_fSpeed = 0.3f;
}

CMonsterSlime::~CMonsterSlime()
{

}

void CMonsterSlime::Initalize()
{

}

int CMonsterSlime::Update(float _fDeltaTime)
{
	SetMonRect();
	SlimeCurMotion();
	MoveFrame();

	if (m_dwMonTimer + 2700 < GetTickCount())
	{
		if (m_eMonCurState == MON_WALK)
			m_eMonCurState = MON_IDLE;
		else if (m_eMonCurState == MON_IDLE)
			m_eMonCurState = MON_WALK;


		m_dwMonTimer = GetTickCount();
	}

	if (m_tMonInfo.fY <= 500 && !m_bIsHit)
		m_tMonInfo.fY += 3.f;

	if (!m_bIsDead && m_eMonCurState == MON_WALK)
		m_tMonInfo.fX += m_fSpeed;

	if (m_bIsDead)
		return EVENT_AIA_END;

	return EVENT_SUCCEED;
}

void CMonsterSlime::LateUpdate(float _fDeltaTime)
{

	if (m_tMonInfo.fX >= 690 || m_tMonInfo.fX <= 110)
	{
		m_fSpeed *= -1.f;
		if (m_bDirLeft)
			m_bDirLeft = false;
		else
			m_bDirLeft = true;
	}
	// 임시 충돌 체크
	/*if (m_tMonInfo.fX >= m_BOX.left && m_tMonInfo.fX <= m_BOX.right && !m_bIsHit)
	{
		m_bIsHit = true;
		m_eMonCurState = MON_HIT;
	}*/
	// 임시 죽음 체크
	if (m_tMonInfo.fX >= m_DeadBOX.left && m_tMonInfo.fX <= m_DeadBOX.right)
	{
		m_bIsDead = true;
		m_eMonCurState = MON_DEAD;
	}

}

void CMonsterSlime::Render(HDC _hDC)
{
	int iScrollX = (int)CScrollMgr::GetInst()->GetScrollX();
	int iScrollY = (int)CScrollMgr::GetInst()->GetScrollY();

	if (!m_bDirLeft)
	{
		HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"SlimeMoveR");

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
			RGB(255, 255, 255));
	}
	else if (m_bDirLeft)
	{
		HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"SlimeMoveL");

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
			RGB(255, 255, 255));
	}

	if (m_bIsHit)
	{
		m_tMonInfo.fX -= 20.f;
		m_bIsHit = false;
	}
}

void CMonsterSlime::Release()
{

}

void CMonsterSlime::SlimeCurMotion()
{


	if (m_eMonCurState != m_eMonPreState)
	{
		switch (m_eMonCurState)
		{
		case MON_IDLE:
			m_tMonFrame.iStart = 0;
			m_tMonFrame.iEnd = 3;
			m_tMonFrame.iMotion = 0;
			m_tMonFrame.dwSpeed = 250;
			m_tMonFrame.dwTime = GetTickCount();
			break;
		case MON_WALK:
			m_tMonFrame.iStart = 0;
			m_tMonFrame.iEnd = 6;
			m_tMonFrame.iMotion = 3;
			m_tMonFrame.dwSpeed = 250;
			m_tMonFrame.dwTime = GetTickCount();
			break;

		case MON_HIT:
			m_tMonFrame.iStart = 0;
			m_tMonFrame.iEnd = 1;
			m_tMonFrame.iMotion = 1;
			m_tMonFrame.dwSpeed = 200;
			m_tMonFrame.dwTime = GetTickCount();
			break;

		case MON_DEAD:
			m_tMonFrame.iStart = 0;
			m_tMonFrame.iEnd = 5;
			m_tMonFrame.iMotion = 4;
			m_tMonFrame.dwSpeed = 300;
			m_tMonFrame.dwTime = GetTickCount();
			break;

		default:
			break;

		}
	}

	if (m_eMonCurState == MON_HIT)
		m_eMonCurState = MON_IDLE;

	m_eMonPreState = m_eMonCurState;
}
