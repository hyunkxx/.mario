#include "pch.h"
#include "CPlayer.h"

#include "CCore.h"
#include "CInputMgr.h"
#include "CLineMgr.h"
#include "CLine.h"
#include "CScrollMgr.h"
#include "CMapEditor.h"
#include "CSceneMgr.h"
#include "CollisionMgr.h"

CPlayer::CPlayer()
	: CObject()
	, m_fMoveSpeed(200.f)
	, m_bIsJump(false)
	, m_bIsGround(true)
{
	m_bIsJump = false;
	m_bIsFloor = false;
	m_bIsHeading = false;
	m_fYSpeed = 0;
}

CPlayer::CPlayer(float _x, float _y, float _scale)
	: CObject(_x, _y, _scale)
	, m_fMoveSpeed(200.f)
	, m_bIsJump(false)
	, m_bIsGround(true)
{
	m_bIsJump = false;
	m_bIsFloor = false;
	m_bIsHeading = false;
	m_fYSpeed = 0;
}

CPlayer::CPlayer(Transform _transform)
	: CObject(_transform)
	, m_fMoveSpeed(200.f)
	, m_bIsJump(false)
	, m_bIsGround(true)
{
	m_bIsJump = false;
	m_bIsFloor = false;
	m_bIsHeading = false;
	m_fYSpeed = 0;
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

	m_bIsJump = false;
	m_bIsFloor = false;
	m_bIsHeading = false;

	Scroll();
	KeyInput();

	if (CInputMgr::GetInstance()->GetKey(VK_RIGHT, KEY_STATE::PRESSED))
		moveRight();
	if (CInputMgr::GetInstance()->GetKey(VK_LEFT, KEY_STATE::PRESSED))
		moveLeft();
	if (CInputMgr::GetInstance()->GetKey(VK_SPACE, KEY_STATE::DOWN))
		m_bIsJump = true;

	YMove(); //Y축 이동은 여기서

	RectUpdate(); //항상 마지막에 호출

	return EVENT_SUCCEED;
}

void CPlayer::LateUpdate(float _fDeltaTime)
{
	if (m_bIsGround)
		onLine();

	size_t curMap = CSceneMgr::GetInstance()->GetCurIndex();
	MapSize size = CMapEditor::GetInst()->GetMapSize((MAP)curMap);
	CScrollMgr::GetInst()->ScrollLock(size.m_iWidth, size.m_iHeight);

	//충돌처리
	vector<LINE*> lines = CMapEditor::GetInst()->GetLineList((MAP)curMap);
	vector<RECT*> rects = CMapEditor::GetInst()->GetRectList((MAP)curMap);

	CObject* pPlayer = CSceneMgr::GetInstance()->GetPlayer();
	CCollisionMgr::CollisionRect_Map(pPlayer, rects);
	
	//Collide_MapEnd(0, 0, (int)size.m_iWidth, (int)size.m_iHeight);

	/*for(auto& rect : rects)
		Collide_MapEnd(0, 0, (int)size.m_iWidth, rect->top);*/


	RectUpdate();//항상 마지막에 호출
}

void CPlayer::Render(HDC _hdc)
{

	//충돌 체크 임시 start
	size_t curMap = CSceneMgr::GetInstance()->GetCurIndex();
	vector<LINE*> lines = CMapEditor::GetInst()->GetLineList((MAP)curMap);
	vector<RECT*> rects = CMapEditor::GetInst()->GetRectList((MAP)curMap);

	int scX = (int)CScrollMgr::GetInst()->GetScrollX();
	int scY = (int)CScrollMgr::GetInst()->GetScrollY();

	for (auto rect = rects.begin(); rect != rects.end(); ++rect)
	{
		Rectangle(_hdc, (*rect)->left + scX, (*rect)->top + scY, (*rect)->right + scX, (*rect)->bottom + scY);
	}
	//충돌체크 임시 end

	const RECT& rcRect = GetRect();
	Rectangle(_hdc, rcRect.left + (int)CScrollMgr::GetInst()->GetScrollX()
		, rcRect.top + (int)CScrollMgr::GetInst()->GetScrollY()
		, rcRect.right + (int)CScrollMgr::GetInst()->GetScrollX()
		, rcRect.bottom + (int)CScrollMgr::GetInst()->GetScrollY());

#ifdef _DEBUG
	TCHAR	szBuf[128] = L"";
	wsprintf(szBuf, L"플레이어 X좌표 : %d       Y좌표 : %d", (int)GetX(), (int)GetY());
	TextOut(_hdc, 500, 10, szBuf, lstrlen(szBuf));


	wsprintf(szBuf, L"스크롤   X좌표 : %d       Y좌표 : %d", (int)CScrollMgr::GetInst()->GetScrollX(), (int)CScrollMgr::GetInst()->GetScrollY());
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
	float fScrollX = CScrollMgr::GetInst()->GetScrollX();
	float fScrollY = CScrollMgr::GetInst()->GetScrollY();

	float fRenderX = fX + fScrollX;
	float fRenderY = fY + fScrollY;

	float fOffSetMinX = 100.f;
	float fOffSetMaxX = 700.f;
	float fOffSetMinY = 100.f;
	float fOffSetMaxY = 500.f;

	if (fRenderX < fOffSetMinX)
	{
		CScrollMgr::GetInst()->SetScrollX(fOffSetMinX - fX);
	}
	if (fRenderX > fOffSetMaxX)
	{
		CScrollMgr::GetInst()->SetScrollX(fOffSetMaxX - fX);
	}
	if (fRenderY < fOffSetMinY)
	{
		CScrollMgr::GetInst()->SetScrollY(fOffSetMinY - fY);
	}
	if (fRenderY > fOffSetMaxY)
	{
		CScrollMgr::GetInst()->SetScrollY(fOffSetMaxY - fY);
	}
}


void CPlayer::KeyInput()
{
	//if (CInputMgr::GetInstance()->GetKey(VK_UP, KEY_STATE::PRESSED))
	//	moveUp();
	//if (CInputMgr::GetInstance()->GetKey(VK_DOWN, KEY_STATE::PRESSED))
	//	moveDown();

	////동현
	//if (CInputMgr::GetInstance()->GetKey(VK_RIGHT, KEY_STATE::PRESSED))
	//	moveRight();
	//if (CInputMgr::GetInstance()->GetKey(VK_LEFT, KEY_STATE::PRESSED))
	//	moveLeft();
	//if (CInputMgr::GetInstance()->GetKey(VK_SPACE, KEY_STATE::DOWN))
	//	m_bIsJump = true;
	//동현
//#ifdef _DEBUG
//
//	if (CInputMgr::GetInstance()->GetKey('A', KEY_STATE::PRESSED)) //바닥충돌 테스트
//		m_bIsFloor = true;
//
//	if (CInputMgr::GetInstance()->GetKey('S', KEY_STATE::PRESSED)) //머리충돌 테스트
//		m_bIsFloor = true;
//
//#endif // _DEBUG
}


//지금문제 > 윤섭이코드에서 계속해서 Y증가 그라운드 체크따로 해야할듯
void CPlayer::YMove()
{
	gravity(m_bIsFloor);
	SubJump(m_bIsJump);
	SubHeading(m_bIsHeading);
	AddPosition(0.0f, m_fYSpeed * DeltaTime);
}


void CPlayer::RectUpdate()
{
	m_rcRect.left = (LONG)(m_tTransform.fX - (m_tTransform.fScale * 0.5f));
	m_rcRect.top = (LONG)(m_tTransform.fY - (m_tTransform.fScale * 0.5f));
	m_rcRect.right = (LONG)(m_tTransform.fX + (m_tTransform.fScale * 0.5f));
	m_rcRect.bottom = (LONG)(m_tTransform.fY + (m_tTransform.fScale * 0.5f));
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
	if (!_value)
	{
		m_fYSpeed += 3.f;
	}
	else
	{
		m_fYSpeed = 0;
	}
}

void CPlayer::SubJump(bool _value)
{
	if (_value)
	{
		m_fYSpeed = -400.f;
	}
}


void CPlayer::SubHeading(bool _value)
{
	if (_value)
	{
		m_fYSpeed = 0;
	}
	else
	{
	}
}

//맵끝에 닿았을때? 좌우로만 되게 수정
void CPlayer::Collide_MapEnd(int _Left, int _Top, int _Right, int _Bottom)
{
	if (m_rcRect.left < _Left)
	{
		m_tTransform.fX = _Left + m_tTransform.fScale * 0.5f;
	}
	if (m_rcRect.right > _Right)
	{
		m_tTransform.fX = _Right - m_tTransform.fScale * 0.5f;;
	}
	if (m_rcRect.top < _Top)
	{
		m_tTransform.fY = _Top + m_tTransform.fScale * 0.5f;
	}
	if (m_rcRect.bottom > _Bottom)
	{
		m_tTransform.fY = _Bottom - m_tTransform.fScale * 0.5f;
	}
}

