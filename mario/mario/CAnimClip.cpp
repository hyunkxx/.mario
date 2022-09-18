#include "pch.h"
#include "CAnimClip.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CScrollMgr.h"

CAnimClip::CAnimClip(CPlayer* _pOwner)
	: m_iCurFrame(0)
	, m_fAnimSpeed(100.f)
{
	m_pOwner = _pOwner;
}

CAnimClip::~CAnimClip()
{
	m_vecAnim.clear();
}

void CAnimClip::AddClip(HDC _hDC , tClipSize _size)
{
	Clip animClip{ _hDC , _size };
	m_vecAnim.push_back(animClip);
}

void CAnimClip::Play(HDC _hdc)
{
	animTick(100.f);

	GdiTransparentBlt(_hdc
		, (float)(m_pOwner->GetX() + CScrollMgr::GetInst()->GetScrollX()) - m_vecAnim[m_iCurFrame].size.width * 0.5f
		, (float)(m_pOwner->GetY() + CScrollMgr::GetInst()->GetScrollY()) - m_vecAnim[m_iCurFrame].size.height * 0.5f
		, m_vecAnim[m_iCurFrame].size.width
		, m_vecAnim[m_iCurFrame].size.height
		, m_vecAnim[m_iCurFrame].image
		, 0, 0, m_vecAnim[m_iCurFrame].size.width, m_vecAnim[m_iCurFrame].size.height, RGB(237, 28, 36));
}

void CAnimClip::Play(HDC _hdc,float _fAnimSpeed)
{
	animTick(_fAnimSpeed);
	
	GdiTransparentBlt(_hdc
		, (float)(m_pOwner->GetX() + CScrollMgr::GetInst()->GetScrollX()) - m_vecAnim[m_iCurFrame].size.width  * 0.5f
		, (float)(m_pOwner->GetY() + CScrollMgr::GetInst()->GetScrollY()) - m_vecAnim[m_iCurFrame].size.height * 0.5f
		, m_vecAnim[m_iCurFrame].size.width
		, m_vecAnim[m_iCurFrame].size.height
		, m_vecAnim[m_iCurFrame].image
		, 0, 0, m_vecAnim[m_iCurFrame].size.width, m_vecAnim[m_iCurFrame].size.height, RGB(237, 28, 36));
}

bool CAnimClip::animTick(float _fAnimSpeed)
{
	if (GetTickCount64() - begin > _fAnimSpeed)
	{
		if (m_iCurFrame < m_vecAnim.size() - 1)
			m_iCurFrame++;
		else
			m_iCurFrame = 0;

		begin = GetTickCount64();

		return true;
	}
	return false;
}
