#include "pch.h"
#include "CCore.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CLineMgr.h"
#include "CLine.h"
#include "CInputMgr.h"
#include "CBitmapMgr.h"
#include "CScrollMgr.h"
#include "CMapEditor.h"

CCore* CCore::pInstance;
float CCore::fDeltaTime;

CCore::CCore()
	: m_hWnd(0)
	, m_hInstance(0)
	, m_rcClient({})
	, m_hDC(0) , m_subDC(0)
	, m_bExit(false)
	, m_fDeltaTime(0.f)
	, m_fTimeScale(1.f)
	, m_nObjCount(0)
{
	m_szTitle = new WCHAR[TEXT_LENGTH];

	QueryPerformanceCounter(&beginTime);
	QueryPerformanceFrequency(&tickCount);
	m_fTimeScale = 1.0f / tickCount.QuadPart;

	ZeroMemory(&endTime, sizeof(LARGE_INTEGER));
}

CCore::~CCore()
{
	Release();

	delete m_szTitle;
}

void CCore::Destroy()
{
	if (pInstance)
	{
		delete pInstance;
		pInstance = nullptr;
	}
}

void CCore::Initalize(const HINSTANCE _hInstance, const HWND _hWnd, const RECT& _rcClient)
{
	m_hInstance  = _hInstance;
	m_hWnd		 = _hWnd;
	m_rcClient	 = _rcClient;

	m_hDC   = GetDC(m_hWnd);
	m_hBit  = CreateCompatibleBitmap(m_hDC, WIDTH, HEIGHT);
	m_subDC = CreateCompatibleDC(m_hDC);
	HBITMAP hDefaultBitmap = (HBITMAP)SelectObject(m_subDC, m_hBit);
	DeleteObject(hDefaultBitmap);

	
	//맵 충돌 데이터 모두 로드
	for (int i = 0; i < (UINT)MAP::END; i++)
		CMapEditor::GetInst()->LoadData((MAP)i);

	CMapEditor::GetInst()->Initalize();

	//메뉴씬으로 진입
	CSceneMgr::GetInstance()->GetCurScene()->Enter();
}

void CCore::Process()
{
	//임시씬 이동 코드 >> 다음 씬 (PGUP) & 이전 씬 (PGDOWN)
	if (GetAsyncKeyState(VK_PRIOR) & 0x0001)
		CSceneMgr::GetInstance()->NextScene();
	if (GetAsyncKeyState(VK_NEXT) & 0x0001)
		CSceneMgr::GetInstance()->PrevScene();

<<<<<<< Updated upstream
=======
	if(CSceneMgr::GetInstance()->IsNext())
		CSceneMgr::GetInstance()->NextScene();

>>>>>>> Stashed changes
	update();
	render();
}

void CCore::update()
{
	setDeltaTime(true);
	CInputMgr::GetInstance()->Update();
	CSceneMgr::GetInstance()->GetCurScene()->Update(m_fDeltaTime);
}

void CCore::render()
{
	SetBkMode(m_subDC, TRANSPARENT);
	/* -------------- 임시 -------------------*/
	WCHAR* szObjCount = new WCHAR[TEXT_LENGTH];
	wsprintf(szObjCount, L"Object Count : %d", (int)m_nObjCount);
	TextOut(m_subDC, WIDTH / 2, 10, szObjCount, lstrlen(szObjCount));
	delete[] szObjCount;

	CSceneMgr::GetInstance()->GetCurScene()->Render(m_subDC);

	BitBlt(m_hDC, 0, 0, WIDTH, HEIGHT, m_subDC, 0, 0, SRCCOPY);
}

void CCore::Release()
{
	CBitmapMgr::GetInstance()->Release();

	//현재씬의 모든 오브젝트 해제
	CSceneMgr::GetInstance()->GetCurScene()->Exit();

	//각종 싱글톤 매니저 해제
	CSceneMgr::Destroy();
	CLineMgr::Destroy();
	CInputMgr::Destroy();
	CBitmapMgr::Destroy();
	CScrollMgr::Destroy();
	CMapEditor::Destroy();

	ReleaseDC(m_hWnd, m_hDC);
	ReleaseDC(m_hWnd, m_subDC);
}

//기본 흰색 사각형 배경 그리기
void CCore::drawBackground(HDC _hDC)
{
	Rectangle(_hDC, -1, -1, WIDTH + 1, HEIGHT + 1);
}

//true 일 경우 타이틀에 DT 표시 : update 초입부분 호출됨
void CCore::setDeltaTime(bool _bShowWindow)
{
	QueryPerformanceCounter(&endTime);
	m_fDeltaTime = (float)(endTime.QuadPart - beginTime.QuadPart) * m_fTimeScale;
	beginTime = endTime;
	CCore::fDeltaTime = m_fDeltaTime;

	if (_bShowWindow)
		swprintf_s(m_szTitle, TEXT_LENGTH, L"DeltaTime : %f", m_fDeltaTime);
	else
		swprintf_s(m_szTitle, TEXT_LENGTH, L"mario");

	SetWindowText(m_hWnd, m_szTitle);
}
