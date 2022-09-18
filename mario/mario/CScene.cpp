#include "pch.h"
#include "CScene.h"

#include "CObject.h"
#include "CSceneMgr.h"

size_t CScene::m_nPlayerCount;

CScene::CScene(wstring _szName)
	: m_szName(_szName)
{
}

CScene::~CScene()
{
}


void CScene::AddObject(CObject* _pObj, OBJ_TYPE _eType)
{
	m_arrObject[(UINT)_eType].push_back(_pObj);
}

void CScene::ClearObject()
{
	for (int i = 0; i < (UINT)OBJ_TYPE::END; i++)
	{
		if (i == (UINT)OBJ_TYPE::TERRAIN)
			continue;

		for (auto iter = m_arrObject[i].begin(); iter != m_arrObject[i].end();)
		{
			(*iter)->Release();
			delete (*iter);
			iter = m_arrObject[i].erase(iter);
		}
	}
}

list<CObject*>* CScene::GetObjectList(OBJ_TYPE _eType)
{
	return &m_arrObject[(UINT)_eType];
}