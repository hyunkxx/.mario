#pragma once

#include "CScene.h"

class CPlayer;
class CObject;

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
	CObject* GetPlayer() { return m_pCurScene->GetPlayer(); }
	CScene* GetCurScene() { return m_pCurScene; }
	size_t GetCurIndex() { return m_nCurIndex; }
	void  SetNext(bool _value) { m_bNext = _value; }
	bool  IsNext() { return m_bNext; }
	void  PrevScene();
	void  NextScene();
private:
	bool m_bNext;
	size_t m_nCurIndex;
	CScene* m_pCurScene;
	CScene* m_arrScene[(UINT)SCENE_STATE::STAGE_COUNT];
};

