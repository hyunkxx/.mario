#pragma once
class CMapEditor
{
private:
	CMapEditor();
	~CMapEditor();
public:
	static CMapEditor* pInstance;
	static CMapEditor* GetInst() { if (!pInstance) { pInstance = new CMapEditor; } return pInstance; }
	static void Destroy() { SAFE_DELETE(pInstance); }
public:
	void AddRect(RECT* _pRect, MAP _eType) { m_vecRects[(UINT)_eType].push_back(_pRect); }
	void AddLine(LINE* _pLine, MAP _eType) { m_vecLines[(UINT)_eType].push_back(_pLine); }
public:
	void CreateRect(POINT& _pLPoint, POINT& _pRPoint , MAP _eType);
	void CreateLine(POINT& _pLPoint, POINT& _pRPoint , MAP _eType);
	void CollisionRender(HDC _hdc, MAP _eType);
	void DrawToggle() { m_bDraw = !m_bDraw; }
	HDC& GetMap(MAP _eType) { return m_subDC[(UINT)_eType]; }
	vector<LINE*> GetLineList(MAP _eType) { return m_vecLines[(UINT)_eType]; }
	vector<RECT*> GetRectList(MAP _eType) { return m_vecRects[(UINT)_eType]; }
	
	UINT GetCurMap() { return m_nCurSettingMap; }
	wstring GetMapName(MAP _eType) { return m_szMapName[(UINT)_eType]; }
	MapSize GetMapSize(MAP _eType) { return m_tSize[(UINT)_eType]; }

public:
	void Initalize();
	void Update();
	void Render(HDC _hdc);
public:
	void SaveData(MAP _eType);
	void LoadData(MAP _eType);
private:
	bool m_bDraw;
	vector<LINE*> m_vecLines[(UINT)MAP::END];
	vector<RECT*> m_vecRects[(UINT)MAP::END];
private:
	UINT m_nCurSettingMap;
	HDC m_subDC[(UINT)MAP::END];
	wstring m_szMapName[(UINT)MAP::END];
	MapSize m_tSize[(UINT)MAP::END];
	
	int viewPosX;
	int viewPosY;
};

