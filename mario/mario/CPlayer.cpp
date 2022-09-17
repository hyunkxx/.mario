#include "pch.h"
#include "CPlayer.h"

#include "CCore.h"
#include "CInputMgr.h"
#include "CLineMgr.h"
#include "CLine.h"
#include "CScrollMgr.h"
#include "CMapEditor.h"
#include "CSceneMgr.h"

CPlayer::CPlayer()
	: CObject()
	, m_fMoveSpeed(200.f)
	, m_bIsJump(false)
	, m_bIsGround(true)
{
}

CPlayer::CPlayer(float _x, float _y, float _scale)
	: CObject(_x, _y, _scale)
	, m_fMoveSpeed(200.f)
	, m_bIsJump(false)
	, m_bIsGround(true)
{
}

CPlayer::CPlayer(Transform _transform)
	: CObject(_transform)
	, m_fMoveSpeed(200.f)
	, m_bIsJump(false)
	, m_bIsGround(true)
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Initalize()
{
	m_fMoveSpeed = 150.f;
}

int CPlayer::Update(float _fDeltaTime)
{
	CObject::Update(_fDeltaTime);

	beginTime = GetTickCount64();

	Scroll();

	//gravity(true);

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

	size_t curMap = CSceneMgr::GetInstance()->GetCurIndex();
	MapSize size = CMapEditor::GetInst()->GetMapSize((MAP)curMap);//curmap2
	CScrollMgr::GetInst()->ScrollLock(size.m_iWidth, size.m_iHeight);
}

void CPlayer::Render(HDC _hdc)
{
	const RECT& rcRect = GetRect();
	Rectangle(_hdc, rcRect.left + (int)CScrollMgr::GetInst()->GetScrollX()
		, rcRect.top + (int)CScrollMgr::GetInst()->GetScrollY()
		, rcRect.right + (int)CScrollMgr::GetInst()->GetScrollX()
		, rcRect.bottom + (int)CScrollMgr::GetInst()->GetScrollY());

#ifdef _DEBUG
	TCHAR	szBuf[128] = L"";
	wsprintf(szBuf, L"ÇÃ·¹ÀÌ¾î XÁÂÇ¥ : %d       YÁÂÇ¥ : %d", (int)GetX(), (int)GetY());
	TextOut(_hdc, 500, 10, szBuf, lstrlen(szBuf));


	wsprintf(szBuf, L"½ºÅ©·Ñ   XÁÂÇ¥ : %d       YÁÂÇ¥ : %d", (int)CScrollMgr::GetInst()->GetScrollX(), (int)CScrollMgr::GetInst()->GetScrollY());
	TextOut(_hdc, 500, 30, szBuf, lstrlen(szBuf));
#endif // _DEBUG


}

void CPlayer::Release()
{

}

void CPlayer::Scroll()
{
	float fX = GetX();
	float fY = GetY();
	float fOffSetMinX = 100.f;
	float fOffSetMaxX = 700.f;
	float fOffSetMinY = 100.f;
	float fOffSetMaxY = 500.f;

	float fScrollX = CScrollMgr::GetInst()->GetScrollX();
	float fScrollY = CScrollMgr::GetInst()->GetScrollY();

	if (fX < fOffSetMinX)
	{
		CScrollMgr::GetInst()->SetScrollX(abs((fX - fOffSetMinX)));
	}
	if (fX > fOffSetMaxX)
	{
		CScrollMgr::GetInst()->SetScrollX(-abs((fOffSetMaxX - fX)));
	}
	if (fY < fOffSetMinY)
	{
		CScrollMgr::GetInst()->SetScrollY(abs((fY - fOffSetMinY)));
	}
	if (fY > fOffSetMaxY)
	{
		CScrollMgr::GetInst()->SetScrollY(-abs((fOffSetMaxY - fY)));
	}
}

void CPlayer::moveUp()
{
	AddPosition(0.0f, -m_fMoveSpeed * CCore::fDeltaTime);
}

void CPlayer::moveDown()
{
	AddPosition(0.0f, m_fMoveSpeed * CCore::fDeltaTime);
}

void CPlayer::moveRight()
{
	AddPosition(m_fMoveSpeed * CCore::fDeltaTime, 0.0f);
}

void CPlayer::moveLeft()
{
	AddPosition(-m_fMoveSpeed * CCore::fDeltaTime, 0.0f);
}

void CPlayer::scrollOffset()
{
	//float	fOffSetMinX = 100.f;
	//float	fOffSetMaxX = 700.f;

	//float	fOffSetMinY = 100.f;
	//float	fOffSetMaxY = 500.f;

	//int		iScrollX = (int)CScrollMgr::GetInst()->GetScrollX();
	//int		iScrollY = (int)CScrollMgr::GetInst()->GetScrollY();

	//if (fOffSetMinX > GetX() + iScrollX)
	//	CScrollMgr::GetInst()->SetScrollX(m_fMoveSpeed);

	//if (fOffSetMaxX < GetX() + iScrollX)
	//	CScrollMgr::GetInst()->SetScrollX(-m_fMoveSpeed);

	//if (fOffSetMinY > GetY() + iScrollY)
	//	CScrollMgr::GetInst()->SetScrollY(m_fMoveSpeed);

	//if (fOffSetMaxY < GetY() + iScrollY)
	//	CScrollMgr::GetInst()->SetScrollY(-m_fMoveSpeed);
}

void CPlayer::onLine()
{
	vector<CLine*> lines = *(CLineMgr::GetInstance()->GetLines(SCENE_STATE::STAGE_1));

	for (auto* line : lines)
	{
		MYPOINT pLeft = line->GetLine().tLPoint;
		MYPOINT pRight = line->GetLine().tRPoint;

		if (pLeft.fX > GetX() || pRight.fX <= GetX())
			continue;

		float fSlope = (pRight.fY - pLeft.fY) / (pRight.fX - pLeft.fX);

		float b = -(fSlope * pLeft.fX - pLeft.fY);
		float fY = fSlope * GetX() + b;
		SetY(fY - GetScale() * 0.4f);
	}
}

void CPlayer::gravity(bool _value)
{
	AddPosition(0.0f, 9.8f * DeltaTime);
}
