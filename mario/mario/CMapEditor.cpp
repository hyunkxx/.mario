#include "pch.h"
#include "CMapEditor.h"

#include "CCore.h"
#include "CInputMgr.h"
#include "CBitmapMgr.h"
#include "CScrollMgr.h"

CMapEditor* CMapEditor::pInstance;

CMapEditor::CMapEditor()
	: m_bDraw(true)
	, m_bLineOrRope(false)
	, m_nCurSettingMap(1)
	, viewPosX(0)
	, viewPosY(0)
{
	for (auto* subDC : m_subDC)
		subDC = nullptr;
}

CMapEditor::~CMapEditor()
{
	for (int i = 0; i < (UINT)MAP::END; ++i)
	{
		for (auto line = m_vecLines[i].begin(); line != m_vecLines[i].end();)
		{
			delete* line;
			line = m_vecLines->erase(line);
		}
	}

	for (int i = 0; i < (UINT)MAP::END; ++i)
	{
		for (auto rect = m_vecRects[i].begin(); rect != m_vecRects[i].end();)
		{
			delete* rect;
			rect = m_vecRects->erase(rect);
		}
	}

	for (int i = 0; i < (UINT)MAP::END; ++i)
	{
		for (auto rect = m_vecRopes[i].begin(); rect != m_vecRopes[i].end();)
		{
			delete* rect;
			rect = m_vecRopes->erase(rect);
		}
	}
}

void CMapEditor::CreateRect(POINT& _pLPoint, POINT& _pRPoint, MAP _eType)
{
	RECT* pRect = new RECT;
	//마우스 클릭좌표 기준 렉트 생성
	pRect->left  = _pLPoint.x;
	pRect->top	 = _pLPoint.y;
	pRect->right = _pRPoint.x;
	pRect->bottom= _pRPoint.y;

	AddRect(pRect , _eType);
	//삭제?
	//delete pRect;
}


void CMapEditor::CreateLine(POINT& _pLPoint, POINT& _pRPoint, MAP _eType)
{
	LINE* pLine = new LINE;
	//마우스 클릭좌표 기준 라인 생성 <렉트와 겹칠때 위치 보정> 
	//라인은 왼쪽에서 오른쪽으로 그리기

	for (auto iter = m_vecRects[(UINT)_eType].begin(); iter != m_vecRects[(UINT)_eType].end(); ++iter)
	{
		if (PtInRect(*iter, _pLPoint))
		{
			_pLPoint.x = (*iter)->right;
			_pLPoint.y = (*iter)->top;
		}
		else if (PtInRect(*iter, _pRPoint))
		{
			_pRPoint.x = (*iter)->left;
			_pRPoint.y = (*iter)->top;
		}
	}

	pLine->tLPoint = _pLPoint;
	pLine->tRPoint = _pRPoint;

	AddLine(pLine, _eType);
	//삭제?
	//delete pLine;
}

void CMapEditor::CreateRope(POINT& _pLPoint, POINT& _pRPoint, MAP _eType)
{
	LINE* pLine = new LINE;
	//마우스 클릭좌표 기준 라인 생성 <렉트와 겹칠때 위치 보정> 
	//라인은 왼쪽에서 오른쪽으로 그리기

	pLine->tLPoint = _pLPoint;

	
	pLine->tRPoint.fX = pLine->tLPoint.fX;
	pLine->tRPoint.fY = (float)_pRPoint.y;

	AddRope(pLine, _eType);

	//삭제?
	//delete pLine;
}

void CMapEditor::CollisionRender(HDC _hdc , MAP _eType)
{
	if (!m_bDraw)
		return;

	HBRUSH myBrush, nullBrush;
	HPEN myPen, redPen, ropePen;

	nullBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	redPen = (HPEN)CreatePen(PS_SOLID, 2, RGB(255, 255, 0));
	ropePen = (HPEN)CreatePen(PS_SOLID, 3, RGB(255, 0 , 0));

	myBrush = (HBRUSH)SelectObject(_hdc, nullBrush);
	myPen = (HPEN)SelectObject(_hdc, redPen);

	int scX = (int)CScrollMgr::GetInst()->GetScrollX();
	int scY = (int)CScrollMgr::GetInst()->GetScrollY();

	for (auto line = m_vecLines[(UINT)_eType].begin(); line != m_vecLines[(UINT)_eType].end(); ++line)
	{
		MoveToEx(_hdc, (int)(*line)->tLPoint.fX + (int)scX, (int)(*line)->tLPoint.fY + (int)scY, nullptr);
		LineTo(_hdc, (int)(*line)->tRPoint.fX + (int)scX, (int)(*line)->tRPoint.fY + (int)scY);
	}

	for (int i = 0; i < (UINT)MAP::END; ++i)
	{
		for (auto rect = m_vecRects[(UINT)_eType].begin(); rect != m_vecRects[(UINT)_eType].end(); ++rect)
		{
			Rectangle(_hdc, (*rect)->left + scX, (*rect)->top + scY, (*rect)->right + scX, (*rect)->bottom + scY);
		}
	}

	(HPEN)SelectObject(_hdc, ropePen);

	for (auto line = m_vecRopes[(UINT)_eType].begin(); line != m_vecRopes[(UINT)_eType].end(); ++line)
	{
		MoveToEx(_hdc, (int)(*line)->tLPoint.fX + (int)scX, (int)(*line)->tLPoint.fY + (int)scY, nullptr);
		LineTo(_hdc, (int)(*line)->tRPoint.fX + (int)scX, (int)(*line)->tRPoint.fY + (int)scY);
	}

	SelectObject(_hdc, myBrush);
	SelectObject(_hdc, myPen);
	DeleteObject(nullBrush);
	DeleteObject(redPen);
	DeleteObject(ropePen);
}


void CMapEditor::Initalize()
{
	m_szMapName[(UINT)MAP::STAGE_START] = L"start";
	m_szMapName[(UINT)MAP::STAGE_1] = L"stage_1";
	m_szMapName[(UINT)MAP::STAGE_2] = L"stage_2";
	m_szMapName[(UINT)MAP::STAGE_3] = L"stage_3";
	m_szMapName[(UINT)MAP::STAGE_4] = L"stage_4";
	m_szMapName[(UINT)MAP::STAGE_ENDING] = L"stage_ending";
	
	m_tSize[(UINT)MAP::STAGE_START] = { 800.f, 600.f };
	m_tSize[(UINT)MAP::STAGE_1] = { 1106.f,618.f};
	m_tSize[(UINT)MAP::STAGE_2] = { 1920.f,681.f};
	m_tSize[(UINT)MAP::STAGE_3] = { 1767.f,660.f};
	// 삐져나온거 자름 원본 y 1371 > 1360
	m_tSize[(UINT)MAP::STAGE_4] = { 1355.f,1020.f};
	m_tSize[(UINT)MAP::STAGE_ENDING] = { 800.f,600.f};
	
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/intro.bmp", m_szMapName[(UINT)MAP::STAGE_START].c_str());
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/map/stage_1.bmp", m_szMapName[(UINT)MAP::STAGE_1].c_str());
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/map/stage_2.bmp", m_szMapName[(UINT)MAP::STAGE_2].c_str());
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/map/stage_3.bmp", m_szMapName[(UINT)MAP::STAGE_3].c_str());
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/map/stage_4.bmp", m_szMapName[(UINT)MAP::STAGE_4].c_str());
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Logo.bmp", m_szMapName[(UINT)MAP::STAGE_ENDING].c_str());
}

void CMapEditor::Update()
{
	static POINT first;
	static POINT second;
	static POINT m_mousePos;

	GetCursorPos(&m_mousePos);
	ScreenToClient(CCore::GetInstance()->GetWindowHandle(), &m_mousePos);

	float ScrollSpeed = 400.f;
	//스크롤 값
	float scX = CScrollMgr::GetInst()->GetScrollX();
	float scY = CScrollMgr::GetInst()->GetScrollY();

	
	//화면 스크롤
	if (CInputMgr::GetInstance()->GetKey(VK_RIGHT, KEY_STATE::PRESSED))
		viewPosX -= (int)(ScrollSpeed * DeltaTime);
	if (CInputMgr::GetInstance()->GetKey(VK_LEFT, KEY_STATE::PRESSED))
		viewPosX += (int)(ScrollSpeed * DeltaTime);
	if (CInputMgr::GetInstance()->GetKey(VK_UP, KEY_STATE::PRESSED))
		viewPosY += (int)(ScrollSpeed * DeltaTime);
	if (CInputMgr::GetInstance()->GetKey(VK_DOWN, KEY_STATE::PRESSED))
		viewPosY -= (int)(ScrollSpeed * DeltaTime);

	CScrollMgr::GetInst()->SetScrollX((float)viewPosX);
	CScrollMgr::GetInst()->SetScrollY((float)viewPosY);

	CScrollMgr::GetInst()->ScrollLock(m_tSize[m_nCurSettingMap].m_iWidth, m_tSize[m_nCurSettingMap].m_iHeight);

	//맵 변경
	if (CInputMgr::GetInstance()->GetKey('R', KEY_STATE::DOWN))
	{
		if (m_nCurSettingMap < (UINT)MAP::STAGE_ENDING)
			m_nCurSettingMap++;
		else
			m_nCurSettingMap = (UINT)MAP::STAGE_1;
	}

	//현제 맵 세이브
	if (CInputMgr::GetInstance()->GetKey('Q', KEY_STATE::DOWN))
		CMapEditor::GetInst()->SaveData((MAP)m_nCurSettingMap);

	//모든 맵 세이브
	if (CInputMgr::GetInstance()->GetKey('W', KEY_STATE::DOWN))
	{
		for(int i = 0 ; i < (UINT)MAP::END ; i ++)
			CMapEditor::GetInst()->SaveData((MAP)i);
	}
	
	//모두 로드
	if (CInputMgr::GetInstance()->GetKey('E', KEY_STATE::DOWN))
	{
		for (int i = 0; i < (UINT)MAP::END; i++)
			CMapEditor::GetInst()->LoadData((MAP)i);
	}

	//그리기 토글
	if (CInputMgr::GetInstance()->GetKey('T', KEY_STATE::DOWN))
		CMapEditor::GetInst()->DrawToggle();

	//선 토글(로프/라인)
	if (CInputMgr::GetInstance()->GetKey('Y', KEY_STATE::DOWN))
		CMapEditor::GetInst()->LineToggle();

	if (CInputMgr::GetInstance()->GetKey(VK_LBUTTON, KEY_STATE::DOWN))
	{
		GetCursorPos(&m_mousePos);
		ScreenToClient(CCore::GetInstance()->GetWindowHandle(), &m_mousePos);
		m_mousePos.x -= (LONG)CScrollMgr::GetInst()->GetScrollX();
		m_mousePos.y -= (LONG)CScrollMgr::GetInst()->GetScrollY();
		first = m_mousePos;
	}

	if (CInputMgr::GetInstance()->GetKey(VK_LBUTTON, KEY_STATE::UP))
	{
		GetCursorPos(&m_mousePos);
		ScreenToClient(CCore::GetInstance()->GetWindowHandle(), &m_mousePos);
		m_mousePos.x -= (LONG)CScrollMgr::GetInst()->GetScrollX();
		m_mousePos.y -= (LONG)CScrollMgr::GetInst()->GetScrollY();
		second = m_mousePos;

		CMapEditor::GetInst()->CreateRect(first, second, (MAP)m_nCurSettingMap);
	}

	if (CInputMgr::GetInstance()->GetKey(VK_RBUTTON, KEY_STATE::DOWN))
	{
		GetCursorPos(&m_mousePos);
		ScreenToClient(CCore::GetInstance()->GetWindowHandle(), &m_mousePos);
		m_mousePos.x -= (LONG)CScrollMgr::GetInst()->GetScrollX();
		m_mousePos.y -= (LONG)CScrollMgr::GetInst()->GetScrollY();
		first = m_mousePos;
	}

	if (CInputMgr::GetInstance()->GetKey(VK_RBUTTON, KEY_STATE::UP))
	{
		GetCursorPos(&m_mousePos);
		ScreenToClient(CCore::GetInstance()->GetWindowHandle(), &m_mousePos);
		m_mousePos.x -= (LONG)CScrollMgr::GetInst()->GetScrollX();
		m_mousePos.y -= (LONG)CScrollMgr::GetInst()->GetScrollY();
		second = m_mousePos;

		if(m_bLineOrRope)
			CMapEditor::GetInst()->CreateLine(first, second, (MAP)m_nCurSettingMap);
		else
			CMapEditor::GetInst()->CreateRope(first, second, (MAP)m_nCurSettingMap);
	}
}


void CMapEditor::Render(HDC _hdc)
{
	m_subDC[m_nCurSettingMap] = CBitmapMgr::GetInstance()->FindBmp(m_szMapName[m_nCurSettingMap].c_str());

	BitBlt(_hdc
		, (int)CScrollMgr::GetInst()->GetScrollX()
		, (int)CScrollMgr::GetInst()->GetScrollY()
		, (int)m_tSize[m_nCurSettingMap].m_iWidth
		, (int)m_tSize[m_nCurSettingMap].m_iHeight
		, m_subDC[m_nCurSettingMap], 0, 0, SRCCOPY);

	WCHAR szText[128];
	wsprintf(szText, L"[Q] 저장   [W] 모두저장   [E] 로드  [R] 맵 변경  [T] 콜리전 보이기/숨기기  [Y] 라인변경 라인/로프  [현재맵]  %s",m_szMapName[m_nCurSettingMap].c_str());

	CMapEditor::GetInst()->CollisionRender(_hdc, (MAP)m_nCurSettingMap);

	TextOut(_hdc, 10, 10, szText,lstrlen(szText));
}

void CMapEditor::SaveData(MAP _eType)
{
	HANDLE hFileLine = nullptr;
	HANDLE hFileRope = nullptr;
	HANDLE hFileRect = nullptr;
	//맵 이름의 인덱스로 enum값 사용
	//CMapData 클래스 만들것
	switch (_eType)
	{
	case MAP::STAGE_1:
		hFileLine = CreateFile(L"../data/stage1_line_colision.dat", GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		hFileRope = CreateFile(L"../data/stage1_rope_colision.dat", GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		hFileRect = CreateFile(L"../data/stage1_rect_colision.dat", GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		break;
	case MAP::STAGE_2:
		hFileLine = CreateFile(L"../data/stage2_line_colision.dat", GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		hFileRope = CreateFile(L"../data/stage1_rope_colision.dat", GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		hFileRect = CreateFile(L"../data/stage2_rect_colision.dat", GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		break;
	case MAP::STAGE_3:
		hFileLine = CreateFile(L"../data/stage3_line_colision.dat", GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		hFileRope = CreateFile(L"../data/stage1_rope_colision.dat", GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		hFileRect = CreateFile(L"../data/stage3_rect_colision.dat", GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		break;
	case MAP::STAGE_4:
		hFileLine = CreateFile(L"../data/stage4_line_colision.dat", GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		hFileRope = CreateFile(L"../data/stage1_rope_colision.dat", GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		hFileRect = CreateFile(L"../data/stage4_rect_colision.dat", GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		break;
	default:
		return;
	}

	if (hFileLine == INVALID_HANDLE_VALUE)
		return;
	
	vector<LINE*> pLine = m_vecLines[(UINT)_eType];
	vector<LINE*> pRope = m_vecRopes[(UINT)_eType];
	vector<RECT*> pRect = m_vecRects[(UINT)_eType];

	DWORD dwByte = 0;

	for (auto& line : pLine)
	{
		if (line != nullptr)
			WriteFile(hFileLine, line, sizeof(LINE), &dwByte, nullptr);
	}

	for (auto& rope : pRope)
	{
		if (rope != nullptr)
			WriteFile(hFileLine, rope, sizeof(LINE), &dwByte, nullptr);
	}

	for (auto& rect : pRect)
	{
		if (rect != nullptr)
			WriteFile(hFileRect, rect, sizeof(RECT), &dwByte, nullptr);
	}

	CloseHandle(hFileLine);
	CloseHandle(hFileRope);
	CloseHandle(hFileRect);

	MessageBox(CCore::GetInstance()->GetWindowHandle(), L"파일저장 성공", L"Result", MB_OK);
}

void CMapEditor::LoadData(MAP _eType)
{
	HANDLE hFileLine = nullptr;
	HANDLE hFileRope = nullptr;
	HANDLE hFileRect = nullptr;
	switch (_eType)
	{
	case MAP::STAGE_1:
		hFileLine = CreateFile(L"../data/stage1_line_colision.dat", GENERIC_READ, 0, nullptr, OPEN_EXISTING, OPEN_EXISTING, nullptr);
		hFileRope = CreateFile(L"../data/stage1_rope_colision.dat", GENERIC_READ, 0, nullptr, OPEN_EXISTING, OPEN_EXISTING, nullptr);
		hFileRect = CreateFile(L"../data/stage1_rect_colision.dat", GENERIC_READ, 0, nullptr, OPEN_EXISTING, OPEN_EXISTING, nullptr);
		break;
	case MAP::STAGE_2:
		hFileLine = CreateFile(L"../data/stage2_line_colision.dat", GENERIC_READ, 0, nullptr, OPEN_EXISTING, OPEN_EXISTING, nullptr);
		hFileRope = CreateFile(L"../data/stage1_rope_colision.dat", GENERIC_READ, 0, nullptr, OPEN_EXISTING, OPEN_EXISTING, nullptr);
		hFileRect = CreateFile(L"../data/stage2_rect_colision.dat", GENERIC_READ, 0, nullptr, OPEN_EXISTING, OPEN_EXISTING, nullptr);
		break;
	case MAP::STAGE_3:
		hFileLine = CreateFile(L"../data/stage3_line_colision.dat", GENERIC_READ, 0, nullptr, OPEN_EXISTING, OPEN_EXISTING, nullptr);
		hFileRope = CreateFile(L"../data/stage1_rope_colision.dat", GENERIC_READ, 0, nullptr, OPEN_EXISTING, OPEN_EXISTING, nullptr);
		hFileRect = CreateFile(L"../data/stage3_rect_colision.dat", GENERIC_READ, 0, nullptr, OPEN_EXISTING, OPEN_EXISTING, nullptr);
		break;;
	case MAP::STAGE_4:
		hFileLine = CreateFile(L"../data/stage4_line_colision.dat", GENERIC_READ, 0, nullptr, OPEN_EXISTING, OPEN_EXISTING, nullptr);
		hFileRope = CreateFile(L"../data/stage1_rope_colision.dat", GENERIC_READ, 0, nullptr, OPEN_EXISTING, OPEN_EXISTING, nullptr);
		hFileRect = CreateFile(L"../data/stage4_rect_colision.dat", GENERIC_READ, 0, nullptr, OPEN_EXISTING, OPEN_EXISTING, nullptr);
		break;
	default:
		return;
	}

	if (INVALID_HANDLE_VALUE == hFileLine)
		return;

	DWORD dwByte = 0;
	LINE lines{};
	LINE ropes{};
	RECT rects{};

	while (true)
	{
		ReadFile(hFileLine, &lines, sizeof(LINE), &dwByte, nullptr);
		if (dwByte == 0)
			break;

		m_vecLines[(UINT)_eType].push_back(new LINE(lines.tLPoint, lines.tRPoint));
	}

	while (true)
	{
		ReadFile(hFileRope, &ropes, sizeof(LINE), &dwByte, nullptr);
		if (dwByte == 0)
			break;

		m_vecRopes[(UINT)_eType].push_back(new LINE(lines.tLPoint, lines.tRPoint));
	}

	while (true)
	{
		ReadFile(hFileRect, &rects, sizeof(RECT), &dwByte, nullptr);
		if (dwByte == 0)
			break;

		m_vecRects[(UINT)_eType].push_back(new RECT(rects));
	}

	CloseHandle(hFileLine);
	CloseHandle(hFileRope);
	CloseHandle(hFileRect);

	MessageBox(CCore::GetInstance()->GetWindowHandle(), L"파일로드 성공", L"Result", MB_OK);
}
