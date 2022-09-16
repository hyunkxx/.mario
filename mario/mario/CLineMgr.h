#pragma once

#include "CLine.h"

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
	bool IsFinish() { return m_bFinish; };
	void AddLine(SCENE_STATE _eType)
	{
		if (m_bFinish)
		{
			m_vecLines[(UINT)_eType].emplace_back(new CLine(m_ptLeft, m_ptRight));
			m_bFinish = false;
			PushObjectList();
		}
	}
	void SaveLine(SCENE_STATE _eType);
	void LoadLine(SCENE_STATE _eType);
	void PushObjectList();
	vector<CLine*>* GetLines(SCENE_STATE _eType) { return &m_vecLines[(UINT)_eType]; };
	void SetBeginPoint(float _x, float _y, SCENE_STATE _eType);
	void SetEndPoint(float _x, float _y);
	const MYPOINT& GetEndPoint() { return m_ptRight; }
	//void DeleteLine(SCENE_STATE _eState);
private:
	//스테이지별 라인을 따로 보관
	vector<CLine*> m_vecLines[(UINT)SCENE_STATE::STAGE_COUNT];
	MYPOINT m_ptLeft;
	MYPOINT m_ptRight;
	POINT m_curMousePos;
	bool m_bFinish;
};