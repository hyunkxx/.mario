#include "pch.h"
#include "CStartScene.h"

#include "CObject.h"
#include "CSceneMgr.h"
#include "CBitmapMgr.h"
#include "CCore.h"
#include "CMapEditor.h"
#include "CInputMgr.h"

CStartScene::CStartScene(wstring _szName)
	: CScene(_szName)
	, m_hSubDC(0)
	, m_bMenuOn(false)
{
	m_rcMenuLine.left = 155;
	m_rcMenuLine.right = 620;
	m_rcMenuLine.top = 392;
	m_rcMenuLine.bottom = 446;
}

CStartScene::~CStartScene()
{
}

void CStartScene::Enter()
{

}

void CStartScene::Exit()
{
	ClearObject();
}

void CStartScene::Update(float _fDeltaTime)
{

	if (CInputMgr::GetInstance()->GetKey(VK_RETURN, KEY_STATE::DOWN) || m_bMenuOn && CInputMgr::GetInstance()->GetKey(VK_LBUTTON, KEY_STATE::DOWN))
		CSceneMgr::GetInstance()->NextScene();

	POINT mouse;
	GetCursorPos(&mouse);
	ScreenToClient(CCore::GetInstance()->GetWindowHandle(), &mouse);
	
	if (PtInRect(&m_rcMenuLine, mouse))
		m_bMenuOn = true;
	else
		m_bMenuOn = false;
}

void CStartScene::Render(HDC _hdc)
{
	HBRUSH nBrush, myBrush;
	HPEN myPen, onPen , offPen;
	nBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	onPen = (HPEN)CreatePen(PS_SOLID, 3, RGB(255, 180, 0));
	offPen = (HPEN)CreatePen(PS_SOLID, 3, RGB(255, 255, 255));

	myBrush = (HBRUSH)SelectObject(m_hSubDC, nBrush);

	if (m_bMenuOn)
		myPen = (HPEN)SelectObject(m_hSubDC, onPen);
	else
		myPen = (HPEN)SelectObject(m_hSubDC, offPen);

	Rectangle(m_hSubDC
		, m_rcMenuLine.left
		, m_rcMenuLine.top
		, m_rcMenuLine.right
		, m_rcMenuLine.bottom);


	SelectObject(m_hSubDC, myBrush);
	SelectObject(m_hSubDC, myPen);
	DeleteObject(onPen);
	DeleteObject(offPen);


	wstring mapName = CMapEditor::GetInst()->GetMapName(MAP::STAGE_START);
	m_hSubDC = CBitmapMgr::GetInstance()->FindBmp(mapName.c_str());
	MapSize mapSize = CMapEditor::GetInst()->GetMapSize(MAP::STAGE_START);
	BitBlt(_hdc, 0, 0, mapSize.m_iWidth, mapSize.m_iHeight, m_hSubDC, 0, 0, SRCCOPY);

	TextOut(_hdc, 10, 10, m_szName.c_str(), lstrlen(m_szName.c_str()));
}
