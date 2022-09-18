#include "pch.h"
#include "CMonsterDragon.h"
#include "CBitmapMgr.h"
#include "CScrollMgr.h"

CMonsterDragon::CMonsterDragon(MON_INFO _tMonInfo) : CMonster(_tMonInfo)
{
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Dragon/DragonMoveL.bmp", L"DragonMoveL");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Dragon/DragonMoveR.bmp", L"DragonMoveR");

	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Dragon/DragonHitL.bmp", L"DragonHitL");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Dragon/DragonHitR.bmp", L"DragonHitR");

	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Dragon/DragonDieL.bmp", L"DragonDieL");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Dragon/DragonDieR.bmp", L"DragonDieR");

	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Dragon/DragonStandR.bmp", L"DragonStandR");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Dragon/DragonStandL.bmp", L"DragonStandL");

	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Dragon/DragonSkillL.bmp", L"DragonSkillL");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Dragon/DragonSkillR.bmp", L"DragonSkillR");

	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Dragon/DragonSkill2R.bmp", L"DragonSkill2R");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Dragon/DragonSkill2L.bmp", L"DragonSkill2L");

	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Dragon/DragonSkillHit.bmp", L"DragonSkillHit");

	m_eMonCurState = MON_WALK;
	m_eMonPreState = MON_IDLE;

	m_fSpeed = 0.2;

	
}

CMonsterDragon::~CMonsterDragon()
{

}

void CMonsterDragon::Initalize()
{

}

int CMonsterDragon::Update(float _fDeltaTime)
{
	SetMonRect();
	DragonCurMotion();
	MoveFrame();

	if (m_tMonInfo.fY <= 350)
		m_tMonInfo.fY += 3.f;

	if (!m_bIsDead && m_eMonCurState == MON_WALK)
	{
		if (m_bDirLeft)
			m_tMonInfo.fX -= m_fSpeed;
		else if (!m_bDirLeft)
			m_tMonInfo.fX += m_fSpeed;
	}

	if (m_pTarget->GetX() > m_tMonInfo.fX)
		m_bDirLeft = false;
	else if (m_tMonInfo.fX > m_pTarget->GetX())
		m_bDirLeft = true;

	int Distance = abs(m_pTarget->GetX() - m_tMonInfo.fX);

	if (Distance <= 200)
	{
		m_bIsSkillTwoOn = true;
		m_eMonCurState = MON_SKILL_TWO;
		m_dwMonTimer = GetTickCount();

		m_tMonSkiLLInfo.fX = m_tMonInfo.fX;
		m_tMonSkiLLInfo.fY = m_tMonInfo.fY;// +100;
		m_tMonSkiLLInfo.fCX = 250.f;
		m_tMonSkiLLInfo.fCY = 211.f;

		SetMonSKillRect(m_tMonSkiLLInfo);
	}
	else if (m_dwMonTimer + 2500 < GetTickCount())
	{
		m_bIsSkillOn = true;
		m_fTargetX = m_pTarget->GetX() - 90;
		m_dwMonTimer = GetTickCount();

		m_tMonSkiLLInfo.fX = m_fTargetX;
		m_tMonSkiLLInfo.fY = m_tMonInfo.fY;// +100;
		m_tMonSkiLLInfo.fCX = 180.f;
		m_tMonSkiLLInfo.fCY = 211.f;

		SetMonSKillRect(m_tMonSkiLLInfo);
	}

	if (m_bIsSkillOn)
	{
		m_eMonCurState = MON_SKILL_ONE;
		SkillPosSetting();
	}

	return EVENT_SUCCEED;
}
// 303 260
void CMonsterDragon::LateUpdate(float _fDeltaTime)
{
	if (m_tMonSkiLLInfo.fX < m_pTarget->GetX())
		m_tMonSkiLLInfo.fX += 1.f;
	else if (m_tMonSkiLLInfo.fX > m_pTarget->GetX())
		m_tMonSkiLLInfo.fX -= 1.f;

	auto a = CScrollMgr::GetInst()->GetScrollX();

	if (m_tMonInfo.fX >= WIDTH - CScrollMgr::GetInst()->GetScrollX() || m_tMonInfo.fX <= 0)
	{
		m_fSpeed *= -1;
		if (m_bDirLeft)
			m_bDirLeft = false;
		else if (!m_bDirLeft)
			m_bDirLeft = true;
	}
	

}

void CMonsterDragon::Render(HDC _hDC)
{
	int iScrollX = (int)CScrollMgr::GetInst()->GetScrollX();
	int iScrollY = (int)CScrollMgr::GetInst()->GetScrollY();
	
	// 208 236
	if (!m_bDirLeft)
	{
		if (m_bIsDead)
		{
			HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"DragonDieR");

			GdiTransparentBlt(_hDC,
				(int)m_rcRect.left,
				(int)m_rcRect.top,
				(int)m_tMonInfo.fCX,
				(int)m_tMonInfo.fCY,
				hMemDC,
				192 * m_tMonFrame.iStart,
				288 * m_tMonFrame.iMotion,
				192,
				288,
				RGB(0, 255, 0));
		}
		else
		{
			if (m_eMonCurState == MON_SKILL_ONE)
			{
				HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"DragonSkillR");

				GdiTransparentBlt(_hDC,
					(int)m_rcRect.left + iScrollX,
					(int)m_rcRect.top + iScrollY,
					(int)m_tMonInfo.fCX + 70,
					(int)m_tMonInfo.fCY,
					hMemDC,
					303 * m_tMonFrame.iStart,
					260 * m_tMonFrame.iMotion,
					303,
					260,
					RGB(255, 255, 255));

				/*if (m_vecSkillPoint.empty())
					return;*/
	
				HDC	hMemDC2 = CBitmapMgr::GetInstance()->FindBmp(L"DragonSkillHit");

				GdiTransparentBlt(_hDC,
					(int)m_fTargetX + iScrollX,
					(int)m_rtMonSKillRect.top + iScrollY,
					(int)m_tMonSkiLLInfo.fCX,
					(int)m_tMonSkiLLInfo.fCY,
					hMemDC2,
					104 * m_tMonSkillFrame.iStart,
					96 * m_tMonSkillFrame.iMotion,
					104,
					96,
					RGB(255, 255, 255));

			}
			else if (m_eMonCurState == MON_SKILL_TWO)
			{
				HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"DragonSkill2R");

				GdiTransparentBlt(_hDC,
					(int)m_rcRect.left + iScrollX,
					(int)m_rcRect.top + iScrollY - 30,
					(int)m_tMonInfo.fCX + 180,
					(int)m_tMonInfo.fCY + 40,
					hMemDC,
					386 * m_tMonFrame.iStart,
					308 * m_tMonFrame.iMotion,
					386,
					308,
					RGB(255, 255, 255));
			}
			else if (m_eMonCurState == MON_IDLE)
			{
				HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"DragonStandR");

				GdiTransparentBlt(_hDC,
					(int)m_rcRect.left + iScrollX,
					(int)m_rcRect.top + iScrollY,
					(int)m_tMonInfo.fCX,
					(int)m_tMonInfo.fCY,
					hMemDC,
					211 * m_tMonFrame.iStart,
					239 * m_tMonFrame.iMotion,
					211,
					239,
					RGB(255, 255, 255));
			}
			else if (m_eMonCurState == MON_WALK)
			{
				HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"DragonMoveR");

				GdiTransparentBlt(_hDC,
					(int)m_rcRect.left + iScrollX,
					(int)m_rcRect.top + iScrollY,
					(int)m_tMonInfo.fCX,
					(int)m_tMonInfo.fCY,
					hMemDC,
					208 * m_tMonFrame.iStart,
					236 * m_tMonFrame.iMotion,
					208,
					236,
					RGB(255, 255, 255));
			}
		}
	}
	else if (m_bDirLeft)
	{
		if (m_bIsDead)
		{
			HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"DragonDieL");

			GdiTransparentBlt(_hDC,
				(int)m_rcRect.left + iScrollX,
				(int)m_rcRect.top + iScrollY,
				(int)m_tMonInfo.fCX ,
				(int)m_tMonInfo.fCY,
				hMemDC,
				247 * m_tMonFrame.iStart,
				290 * m_tMonFrame.iMotion,
				247,
				290,
				RGB(255, 255, 255));
		}
		else
		{
			if (m_eMonCurState == MON_SKILL_ONE)
			{
				HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"DragonSkillL");

				GdiTransparentBlt(_hDC,
					(int)m_rcRect.left + iScrollX,
					(int)m_rcRect.top + iScrollY,
					(int)m_tMonInfo.fCX + 70,
					(int)m_tMonInfo.fCY,
					hMemDC,
					303 * m_tMonFrame.iStart,
					260 * m_tMonFrame.iMotion,
					303,
					260,
					RGB(255, 255, 255));

				/*if (m_vecSkillPoint.empty())
					return;*/

				HDC	hMemDC2 = CBitmapMgr::GetInstance()->FindBmp(L"DragonSkillHit");

				GdiTransparentBlt(_hDC,
					(int)m_fTargetX + iScrollX,
					(int)m_rtMonSKillRect.top + iScrollY,
					(int)m_tMonSkiLLInfo.fCX,
					(int)m_tMonSkiLLInfo.fCY,
					hMemDC2,
					104 * m_tMonSkillFrame.iStart,
					96 * m_tMonSkillFrame.iMotion,
					104,
					96,
					RGB(255, 255, 255));

			}
			else if (m_eMonCurState == MON_SKILL_TWO)
			{
				HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"DragonSkill2L");

				GdiTransparentBlt(_hDC,
					(int)m_rcRect.left + iScrollX,
					(int)m_rcRect.top + iScrollY - 20,
					(int)m_tMonInfo.fCX + 180,
					(int)m_tMonInfo.fCY + 40,
					hMemDC,
					386 * m_tMonFrame.iStart,
					308 * m_tMonFrame.iMotion,
					386,
					308,
					RGB(255, 255, 255));
			}
			else if (m_eMonCurState == MON_IDLE)
			{
				HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"DragonStandL");

				GdiTransparentBlt(_hDC,
					(int)m_rcRect.left + iScrollX,
					(int)m_rcRect.top + iScrollY,
					(int)m_tMonInfo.fCX,
					(int)m_tMonInfo.fCY,
					hMemDC,
					211 * m_tMonFrame.iStart,
					239 * m_tMonFrame.iMotion,
					211,
					239,
					RGB(255, 255, 255));
			}
			else
			{
				HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"DragonMoveL");

				GdiTransparentBlt(_hDC,
					(int)m_rcRect.left + iScrollX,
					(int)m_rcRect.top + iScrollY,
					(int)m_tMonInfo.fCX,
					(int)m_tMonInfo.fCY,
					hMemDC,
					208 * m_tMonFrame.iStart,
					236 * m_tMonFrame.iMotion,
					208,
					236,
					RGB(255, 255, 255));
			}
		}
	}

	// 104 96
}

void CMonsterDragon::Release()
{

}

void CMonsterDragon::DragonCurMotion()
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
		case MON_WALK:
			m_tMonFrame.iStart = 0;
			m_tMonFrame.iEnd = 6;
			m_tMonFrame.iMotion = 0;
			m_tMonFrame.dwSpeed = 200;
			m_tMonFrame.dwTime = GetTickCount();
			break;
		case MON_SKILL_ONE:
			m_tMonFrame.iStart = 1;
			m_tMonFrame.iEnd = 24;
			m_tMonFrame.iMotion = 0;
			m_tMonFrame.dwSpeed = 70;
			m_tMonFrame.dwTime = GetTickCount();

			m_tMonSkillFrame.iStart = 0;
			m_tMonSkillFrame.iEnd = 8;
			m_tMonSkillFrame.iMotion = 0;
			m_tMonSkillFrame.dwSpeed = 150;
			m_tMonSkillFrame.dwTime = GetTickCount();
			break;
		case MON_SKILL_TWO:
			m_tMonFrame.iStart = 0;
			m_tMonFrame.iEnd = 31;
			m_tMonFrame.iMotion = 0;
			m_tMonFrame.dwSpeed = 70;
			m_tMonFrame.dwTime = GetTickCount();

			m_tMonSkillFrame.iStart = 0;
			m_tMonSkillFrame.iEnd = 8;
			m_tMonSkillFrame.iMotion = 0;
			m_tMonSkillFrame.dwSpeed = 150;
			m_tMonSkillFrame.dwTime = GetTickCount();
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

void CMonsterDragon::SkillPosSetting()
{
	if (!m_vecSkillPoint.empty())
		return;

	int iSkillPoint = (int)abs(m_tMonSkiLLInfo.fX - m_pTarget->GetX());

	if (iSkillPoint <= 300)
		return;

	iSkillPoint /= 8;

	for (int i = 7; i >= 1; --i)
	{
		if (m_pTarget->GetX() > m_tMonInfo.fX)
			m_vecSkillPoint.push_back(iSkillPoint * i);
		else
			m_vecSkillPoint.push_back(-(iSkillPoint * i));
	}


}
