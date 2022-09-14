#pragma once

class CLine;

class CLineMgr
{
private:
	CLineMgr();
	~CLineMgr();
	CLineMgr(const CLineMgr& rhs) = delete;
	CLineMgr& operator=(const CLineMgr& rhs) = delete;
public:
	static CLineMgr* pInstance;
	static CLineMgr* GetInstance() { if (!pInstance) { pInstance = new CLineMgr; }	return pInstance; }
	static void Destroy() { if (pInstance) { delete pInstance; pInstance = nullptr; } }
public:
	bool IsReady() { return m_bReady; };
	void CreateLine();
	void PushObjectList();
	vector<CLine*>* GetLines(SCENE_STATE _eType) { return &m_vecLines[(UINT)_eType]; };
private:
	void SetBeginPoint();
	void SetEndPoint();
private:
	//스테이지별 라인을 따로 보관
	vector<CLine*> m_vecLines[(UINT)SCENE_STATE::STAGE_COUNT];
	MYPOINT m_ptLeft;
	MYPOINT m_ptRight;
	bool m_bReady;
};