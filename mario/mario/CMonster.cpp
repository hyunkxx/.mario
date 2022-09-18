#include "pch.h"
#include "CMonster.h"
#include "CScrollMgr.h"

CMonster::CMonster(MON_INFO _tMonInfo) : m_tMonInfo(_tMonInfo), m_dwMonTimer(GetTickCount())
, m_fSpeed(false), m_fSkillDistance(0.f)
{

}

CMonster::CMonster() : m_dwMonTimer(GetTickCount()), m_fSkillDistance(0.f), m_fSpeed(0.f)
	,m_fTargetX(0.f)
{
}

CMonster::~CMonster()
{
	Release();
}

void CMonster::SetMonRect()
{
	m_rcRect.left = (LONG)(m_tMonInfo.fX - (m_tMonInfo.fCX * 0.5f));
	m_rcRect.top = (LONG)(m_tMonInfo.fY - (m_tMonInfo.fCY * 0.5f));
	m_rcRect.right = (LONG)(m_tMonInfo.fX + (m_tMonInfo.fCX * 0.5f));
	m_rcRect.bottom = (LONG)(m_tMonInfo.fY + (m_tMonInfo.fCY * 0.5f));

	/*m_rtMonSKillRect.left = (LONG)(m_tMonSkiLLInfo.fX - (m_tMonSkiLLInfo.fCX * 0.5f));
	m_rtMonSKillRect.top = (LONG)(m_tMonSkiLLInfo.fY - (m_tMonSkiLLInfo.fCY * 0.5f));
	m_rtMonSKillRect.right = (LONG)(m_tMonSkiLLInfo.fX + (m_tMonSkiLLInfo.fCX * 0.5f));
	m_rtMonSKillRect.bottom = (LONG)(m_tMonSkiLLInfo.fY + (m_tMonSkiLLInfo.fCY * 0.5f));*/

}

void CMonster::SetMonSKillRect(MON_INFO _tMonInfo)
{
	m_rtMonSKillRect.left = (LONG)(_tMonInfo.fX - (m_tMonInfo.fCX * 0.5f));
	m_rtMonSKillRect.top = (LONG)(_tMonInfo.fY - (m_tMonInfo.fCY * 0.5f));
	m_rtMonSKillRect.right = (LONG)(_tMonInfo.fX + (m_tMonInfo.fCX * 0.5f));
	m_rtMonSKillRect.bottom = (LONG)(_tMonInfo.fY + (m_tMonInfo.fCY * 0.5f));

	m_vecMonSKill.push_back(m_rtMonSKillRect);
}

void CMonster::ClearMonBox()
{
	m_vecMonSKill.clear();
}

void CMonster::MoveFrame()
{
	if (m_tMonFrame.dwTime + m_tMonFrame.dwSpeed < GetTickCount())
	{
		++m_tMonFrame.iStart;
		m_tMonFrame.dwTime = GetTickCount();
	}

	if (m_tMonSkillFrame.dwTime + m_tMonSkillFrame.dwSpeed < GetTickCount())
	{
		++m_tMonSkillFrame.iStart;
		m_tMonSkillFrame.dwTime = GetTickCount();
	}
	
	if (m_tMonSkillFrame.iStart >= m_tMonSkillFrame.iEnd)
	{
		m_tMonSkillFrame.iStart = 0;
		m_bIsSkillOn = false;
		m_bIsSkillTwoOn = false;
		m_eMonCurState = MON_WALK;
	}

	if (m_tMonFrame.iStart >= m_tMonFrame.iEnd /*&& abs(m_tMonFrame.iStart - m_tMonFrame.iEnd) > 2*/)
		m_tMonFrame.iStart = 0;

}

