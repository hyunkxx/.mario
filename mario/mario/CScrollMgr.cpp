#include "pch.h"
#include "CScrollMgr.h"


CScrollMgr* CScrollMgr::pInstance;

CScrollMgr::CScrollMgr()
	:m_fX(0.f)
	,m_fY(0.f)
{
}

CScrollMgr::~CScrollMgr()
{
}

void CScrollMgr::ScrollLock(float _MapWidth, float _MapHeight)
{
	if (m_fX > 0.f)
		m_fX = 0.f;

	if (m_fY > 0.f)
		m_fY = 0.f;

	if (WIDTH - _MapWidth > m_fX)
		m_fX = float(WIDTH - _MapWidth);
	if (HEIGHT - _MapHeight > m_fY)
		m_fY = float(HEIGHT - _MapHeight);
}
