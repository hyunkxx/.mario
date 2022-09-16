#include "pch.h"
#include "CPlayer.h"

#include "CCore.h"
#include "CInputMgr.h"
#include "CLineMgr.h"
#include "CLine.h"
#include "CScrollMgr.h"

CPlayer::CPlayer()
	: CObject()
	, m_fMoveSpeed(50.f)
	, m_bIsJump(false)
	, m_bIsGround(true)
{
}

CPlayer::CPlayer(float _x, float _y, float _scale)
	: CObject(_x, _y, _scale)
	, m_fMoveSpeed(50.f)
	, m_bIsJump(false)
	, m_bIsGround(true)
{
}

CPlayer::CPlayer(Transform _transform)
	: CObject(_transform)
	, m_fMoveSpeed(50.f)
	, m_bIsJump(false)
	, m_bIsGround(true)
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Initalize()
{
}

int CPlayer::Update(float _fDeltaTime)
{
	CObject::Update(_fDeltaTime);

	if (CInputMgr::GetInstance()->GetKey(VK_UP, KEY_STATE::PRESSED))
		moveUp();
	if (CInputMgr::GetInstance()->GetKey(VK_DOWN, KEY_STATE::PRESSED))
		moveDown();
	if (CInputMgr::GetInstance()->GetKey(VK_RIGHT, KEY_STATE::PRESSED))
		moveRight();
	if (CInputMgr::GetInstance()->GetKey(VK_LEFT, KEY_STATE::PRESSED))
		moveLeft();

	return EVENT_SUCCEED;
}

void CPlayer::LateUpdate(float _fDeltaTime)
{
	if (m_bIsGround)
		onLine();
}

void CPlayer::Render(HDC _hdc)
{
	const RECT& rcRect = GetRect();
	Rectangle(_hdc, rcRect.left, rcRect.top, rcRect.right, rcRect.bottom);
}

void CPlayer::Release()
{

}

void CPlayer::moveUp()
{
	AddPosition(0.0f, -m_fMoveSpeed * CCore::fDeltaTime);
	CScrollMgr::GetInst()->SetScrollY(+m_fMoveSpeed * CCore::fDeltaTime);
}

void CPlayer::moveDown()
{
	AddPosition(0.0f, m_fMoveSpeed * CCore::fDeltaTime);
	CScrollMgr::GetInst()->SetScrollY(-m_fMoveSpeed * CCore::fDeltaTime);
}

void CPlayer::moveRight()
{
	AddPosition(m_fMoveSpeed * CCore::fDeltaTime ,0.0f);
	CScrollMgr::GetInst()->SetScrollX(-m_fMoveSpeed * CCore::fDeltaTime);
}

void CPlayer::moveLeft()
{
	AddPosition(-m_fMoveSpeed * CCore::fDeltaTime, 0.0f);
	CScrollMgr::GetInst()->SetScrollX(m_fMoveSpeed * CCore::fDeltaTime);
}

void CPlayer::scrollOffset()
{
}

void CPlayer::onLine()
{
	vector<CLine*> lines = *(CLineMgr::GetInstance()->GetLines(SCENE_STATE::STAGE_1));

	for (auto* line : lines)
	{
		MYPOINT pLeft  = line->GetLine().tLPoint;
		MYPOINT pRight = line->GetLine().tRPoint;

		if (pLeft.fX > GetX() || pRight.fX <= GetX())
			continue;

		float fSlope = (pRight.fY - pLeft.fY) / (pRight.fX - pLeft.fX);

		float b = -(fSlope * pLeft.fX - pLeft.fY);
		float fY = fSlope * GetX() + b;
		SetY(fY - GetScale() * 0.4f);
	}
}
