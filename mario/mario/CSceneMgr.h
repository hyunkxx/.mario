#pragma once

class CScene;

class CSceneMgr
{
private:
	CSceneMgr();
	~CSceneMgr();
	CSceneMgr& operator=(const CSceneMgr& rhs) = delete;
	CSceneMgr(const CSceneMgr& rhs) = delete;
public:
	static CSceneMgr* pInstance;
	static CSceneMgr* GetInstance() { if (!pInstance) { pInstance = new CSceneMgr; } return pInstance; }
	static void Destroy();
public:
	CScene* GetCurScene() { return m_pCurScene; }
	size_t GetCurIndex() { return m_nCurIndex; }
	void  PrevScene();
	void  NextScene();
private:
	size_t m_nCurIndex;
	CScene* m_pCurScene;
	CScene* m_arrScene[(UINT)SCENE_STATE::STAGE_COUNT];
};

