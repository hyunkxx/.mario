#pragma once

class CCore
{
private:
	CCore();
	~CCore();
	CCore& operator=(const CCore& rhs) = delete;
	CCore(const CCore& rhs) = delete;
public:
	static CCore* pInstance;	static CCore* GetInstance() { if (!pInstance) { pInstance = new CCore; } return pInstance; }
	static void Destroy();
	static float fDeltaTime;
public:
	void Initalize(const HINSTANCE _hInstance , const HWND _hWnd , const RECT& _rcClient);
	void Process();
	void Release();
private:
	void update();
	void render();
public:
	BOOL IsExit() const { return m_bExit; }
	void SetExit(BOOL _value) { m_bExit = _value; }
	const HWND& GetWindowHandle() { return m_hWnd; }
private:
	void drawBackground(HDC _hDC);
	void setDeltaTime(bool _bShowWindow);
private://windows value
	HWND		m_hWnd;
	HINSTANCE	m_hInstance;
	RECT		m_rcClient;
	HDC			m_hDC, m_subDC;
	HBITMAP		m_hBit;
private://Core value
	WCHAR*			m_szTitle;
	LARGE_INTEGER	beginTime, endTime, tickCount;
	BOOL			m_bExit; //게임 종료코드
	float			m_fDeltaTime;
	float			m_fTimeScale;
public://테스트 코드 public>private
	size_t			m_nObjCount;
};

