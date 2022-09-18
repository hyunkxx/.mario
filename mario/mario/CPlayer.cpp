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
#include "CBitmapMgr.h"
#include "CAnimClip.h"



#include "AbstractFactory.h"
//#include "CShot.h"
#include "CScene.h"
#include "CScrollMgr.h"
#include "CBitmapMgr.h"

CPlayer::CPlayer()
	: CObject()
	, m_fMoveSpeed(200.f)
	, m_bIsJump(false)
	, m_bIsGround(true)
	, m_pClipIdle_r(nullptr)
	, m_pClipWalk_r(nullptr)
	, m_eState(ANIM::IDLE_R)
{
	m_bIsJump = false;
	m_bIsFloor = false;
	m_bIsHeading = false;
	m_fYSpeed = 0;

	Initalize();
}

CPlayer::CPlayer(float _x, float _y, float _scale)
	: CObject(_x, _y, _scale)
	, m_fMoveSpeed(200.f)
	, m_bIsJump(false)
	, m_bIsGround(true)
	, m_pClipIdle_r(nullptr)
	, m_pClipWalk_r(nullptr)
	, m_eState(ANIM::IDLE_R)
{
	m_bIsJump = false;
	m_bIsFloor = false;
	m_bIsHeading = false;
	m_fYSpeed = 0;

	Initalize();
}

CPlayer::CPlayer(Transform _transform)
	: CObject(_transform)
	, m_fMoveSpeed(200.f)
	, m_bIsJump(false)
	, m_bIsGround(true)
	, m_pClipIdle_r(nullptr)
	, m_pClipWalk_r(nullptr)
	, m_eState(ANIM::IDLE_R)
{
	m_bIsJump = false;
	m_bIsFloor = false;
	m_bIsHeading = false;
	m_fYSpeed = 0;
	m_iJumpCount = 0;

	Initalize();
}

CPlayer::~CPlayer()
{
}

void CPlayer::Initalize()
{
	m_fMoveSpeed=200.f;
	SetScale(62.f);
	m_eState = ANIM::IDLE_R;
	m_bUse   = false;

	//의존성 주입 
	m_pClipIdle_r = new CAnimClip(this);
	m_pClipWalk_r = new CAnimClip(this);
	m_pClipIdle_l = new CAnimClip(this);
	m_pClipWalk_l = new CAnimClip(this);

	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/player_res/right/stand_0.bmp", L"stand0_r");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/player_res/right/stand_1.bmp", L"stand1_r");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/player_res/right/stand_2.bmp", L"stand2_r");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/player_res/right/stand_3.bmp", L"stand3_r");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/player_res/right/stand_4.bmp", L"stand4_r");

	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/player_res/right/walk_0.bmp", L"walk0_r");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/player_res/right/walk_1.bmp", L"walk1_r");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/player_res/right/walk_2.bmp", L"walk2_r");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/player_res/right/walk_3.bmp", L"walk3_r");

	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/player_res/left/stand_0.bmp", L"stand0_l");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/player_res/left/stand_1.bmp", L"stand1_l");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/player_res/left/stand_2.bmp", L"stand2_l");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/player_res/left/stand_3.bmp", L"stand3_l");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/player_res/left/stand_4.bmp", L"stand4_l");
															  
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/player_res/left/walk_0.bmp", L"walk0_l");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/player_res/left/walk_1.bmp", L"walk1_l");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/player_res/left/walk_2.bmp", L"walk2_l");
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/player_res/left/walk_3.bmp", L"walk3_l");

	m_pClipIdle_r->AddClip(CBitmapMgr::GetInstance()->FindBmp(L"stand0_r"), { 50,70 });
	m_pClipIdle_r->AddClip(CBitmapMgr::GetInstance()->FindBmp(L"stand1_r"), { 50,70 });
	m_pClipIdle_r->AddClip(CBitmapMgr::GetInstance()->FindBmp(L"stand2_r"), { 50,70 });
	m_pClipIdle_r->AddClip(CBitmapMgr::GetInstance()->FindBmp(L"stand3_r"), { 50,70 });
	m_pClipIdle_r->AddClip(CBitmapMgr::GetInstance()->FindBmp(L"stand4_r"), { 50,70 });

	m_pClipWalk_r->AddClip(CBitmapMgr::GetInstance()->FindBmp(L"walk0_r"), { 66,70 });
	m_pClipWalk_r->AddClip(CBitmapMgr::GetInstance()->FindBmp(L"walk1_r"), { 66,70 });
	m_pClipWalk_r->AddClip(CBitmapMgr::GetInstance()->FindBmp(L"walk2_r"), { 66,70 });
	m_pClipWalk_r->AddClip(CBitmapMgr::GetInstance()->FindBmp(L"walk3_r"), { 66,70 });

	m_pClipIdle_l->AddClip(CBitmapMgr::GetInstance()->FindBmp(L"stand0_l"), { 50,70 });
	m_pClipIdle_l->AddClip(CBitmapMgr::GetInstance()->FindBmp(L"stand1_l"), { 50,70 });
	m_pClipIdle_l->AddClip(CBitmapMgr::GetInstance()->FindBmp(L"stand2_l"), { 50,70 });
	m_pClipIdle_l->AddClip(CBitmapMgr::GetInstance()->FindBmp(L"stand3_l"), { 50,70 });
	m_pClipIdle_l->AddClip(CBitmapMgr::GetInstance()->FindBmp(L"stand4_l"), { 50,70 });

	m_pClipWalk_l->AddClip(CBitmapMgr::GetInstance()->FindBmp(L"walk0_l"), { 66,70 });
	m_pClipWalk_l->AddClip(CBitmapMgr::GetInstance()->FindBmp(L"walk1_l"), { 66,70 });
	m_pClipWalk_l->AddClip(CBitmapMgr::GetInstance()->FindBmp(L"walk2_l"), { 66,70 });
	m_pClipWalk_l->AddClip(CBitmapMgr::GetInstance()->FindBmp(L"walk3_l"), { 66,70 });
}

int CPlayer::Update(float _fDeltaTime)
{
	CObject::Update(_fDeltaTime);

	beginTime = GetTickCount64();

	m_bIsJump   = false;
	m_bIsHeading = false;

	Scroll();
	KeyInput();
	YMove(); //Y축 이동은 여기서
	
	
	stateCheck();
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
	vector<LINE*> ropes = CMapEditor::GetInst()->GetRopeList((MAP)curMap);

	CObject* pPlayer = CSceneMgr::GetInstance()->GetPlayer();

	CCollisionMgr::CollisionRect_Map(pPlayer, rects);
	CCollisionMgr::CollisionRope(pPlayer, ropes);

	Collide_MapEnd(size);
}

void CPlayer::Render(HDC _hdc)
{

	//충돌 체크 임시 start
	size_t curMap = CSceneMgr::GetInstance()->GetCurIndex();
	vector<LINE*> lines = CMapEditor::GetInst()->GetLineList((MAP)curMap);
	vector<RECT*> rects = CMapEditor::GetInst()->GetRectList((MAP)curMap);

	const RECT& rcRect = GetRect();
	//Rectangle(_hdc
	//	, rcRect.left + (int)CScrollMgr::GetInst()->GetScrollX()
	//	, rcRect.top    + (int)CScrollMgr::GetInst()->GetScrollY()
	//	, rcRect.right  + (int)CScrollMgr::GetInst()->GetScrollX()
	//	, rcRect.bottom + (int)CScrollMgr::GetInst()->GetScrollY());

#ifdef _DEBUG
	//지형 충돌체크 임시 그리기 Rect
	if (bDebug)
	{
		int scX = (int)CScrollMgr::GetInst()->GetScrollX();
		int scY = (int)CScrollMgr::GetInst()->GetScrollY();

		for (auto rect = rects.begin(); rect != rects.end(); ++rect)
		{
			Rectangle(_hdc, (*rect)->left + scX, (*rect)->top + scY, (*rect)->right + scX, (*rect)->bottom + scY);
		}

		TCHAR	szBuf[128] = L"";
		wsprintf(szBuf, L"Player posX  [ %d ]   posY  [ %d ]", (int)GetX(), (int)GetY());
		TextOut(_hdc, 500, 10, szBuf, lstrlen(szBuf));


		wsprintf(szBuf, L"Scroll  posX [ %d ]   posY  [ %d ]", (int)CScrollMgr::GetInst()->GetScrollX(), (int)CScrollMgr::GetInst()->GetScrollY());
		TextOut(_hdc, 500, 30, szBuf, lstrlen(szBuf));
	}
#endif // _DEBUG

	animPlay(_hdc);
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


void CPlayer::RopeRide(float _x)
{
	if(CInputMgr::GetInstance()->GetKey(VK_DOWN, KEY_STATE::PRESSED))
		SetY(GetY() + 10.f);
	if (CInputMgr::GetInstance()->GetKey(VK_UP, KEY_STATE::PRESSED))
		SetY(GetY() - 10.f);
}

void CPlayer::KeyInput()
{
	if (CInputMgr::GetInstance()->GetKey(VK_F12, KEY_STATE::DOWN))
		bDebug = !bDebug;

	//아래점프
	if (CInputMgr::GetInstance()->GetKey(VK_DOWN, KEY_STATE::PRESSED) && CInputMgr::GetInstance()->GetKey(VK_SPACE, KEY_STATE::DOWN))
	{
		SetY(GetY() + 5.f);
		return;
	}

	/*if(CInputMgr::GetInstance()->GetKey(VK_RIGHT, KEY_STATE::DOWN)
		CSceneMgr::GetIns*/


	if (CInputMgr::GetInstance()->GetKey(VK_RIGHT, KEY_STATE::PRESSED))
		moveRight();
	if (CInputMgr::GetInstance()->GetKey(VK_LEFT, KEY_STATE::PRESSED))
		moveLeft();

	if (CInputMgr::GetInstance()->GetKey(VK_SPACE, KEY_STATE::DOWN))
		m_bIsJump = true;


	if (CInputMgr::GetInstance()->GetKey(VK_UP, KEY_STATE::DOWN))
		m_bUse = true;
	else
		m_bUse = false;
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
	m_rcRect.left    = (LONG)(m_tTransform.fX - (m_tTransform.fScale * 0.5f));
	m_rcRect.top     = (LONG)(m_tTransform.fY - (m_tTransform.fScale * 0.5f));
	m_rcRect.right   = (LONG)(m_tTransform.fX + (m_tTransform.fScale * 0.5f));
	m_rcRect.bottom  = (LONG)(m_tTransform.fY + (m_tTransform.fScale * 0.5f));
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
	/*if(m_bOnRope)*/
		AddPosition(m_fMoveSpeed * CCore::fDeltaTime, 0.0f);
}

void CPlayer::moveLeft()
{
	/*if (m_bOnRope)*/
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

void CPlayer::animPlay(HDC _hdc)
{
	switch (m_eState)
	{
	case CPlayer::ANIM::IDLE_L:
		m_pClipIdle_l->Play(_hdc, 100.f);
		break;
	case CPlayer::ANIM::IDLE_R:
		m_pClipIdle_r->Play(_hdc, 100.f);
		break;
	case CPlayer::ANIM::WALK_R:
		m_pClipWalk_r->Play(_hdc, 100.f);
		break;
	case CPlayer::ANIM::WALK_L:
		m_pClipWalk_l->Play(_hdc, 100.f);
		break;
	}
}

void CPlayer::stateCheck()
{
	
	if (CInputMgr::GetInstance()->GetKey(VK_LEFT, KEY_STATE::PRESSED))
	{
		m_eState = ANIM::WALK_L;
	}
	else if(CInputMgr::GetInstance()->GetKey(VK_RIGHT, KEY_STATE::PRESSED))
	{
		m_eState = ANIM::WALK_R;
	}
	else if (CInputMgr::GetInstance()->GetKey(VK_LEFT, KEY_STATE::UP))
	{
		m_eState = ANIM::IDLE_L;
	}
	else if (CInputMgr::GetInstance()->GetKey(VK_RIGHT, KEY_STATE::UP))
	{
		m_eState = ANIM::IDLE_R;
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
		m_iJumpCount = 0;
	}
}

void CPlayer::SubJump(bool _value)
{
	if (_value)
	{
		if (m_iJumpCount < 1) //1이면 1단점프 2면 2단점프
		{
			++m_iJumpCount;
			m_fYSpeed = -300.f;
		}
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
void CPlayer::Collide_MapEnd(MapSize _size)
{
	if (m_rcRect.left < 0)
	{
		m_tTransform.fX = 0 + m_tTransform.fScale * 0.5f;
	}
	if (m_rcRect.right > _size.m_iWidth)
	{
		m_tTransform.fX = _size.m_iWidth - m_tTransform.fScale * 0.5f;;
	}
	if (m_rcRect.bottom > _size.m_iHeight)
	{
		m_tTransform.fY = _size.m_iHeight - m_tTransform.fScale * 0.5f;
	}
}


