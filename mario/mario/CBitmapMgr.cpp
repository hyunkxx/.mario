#include "pch.h"
#include "CBitmapMgr.h"

CBitmapMgr* CBitmapMgr::m_pInstance = nullptr;

CBitmapMgr::CBitmapMgr()
{
}


CBitmapMgr::~CBitmapMgr()
{
	Release();
}

void CBitmapMgr::InsertBmp(const TCHAR* pFilePath, const TCHAR* pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTagFinder(pImgKey));

	if (iter == m_mapBit.end())
	{
		CBitmap* pBmp = new CBitmap;
		pBmp->LoadBmp(pFilePath);

		m_mapBit.insert({ pImgKey, pBmp });
	}
}

HDC CBitmapMgr::FindBmp(const TCHAR* pImgKey)
{
	auto	iter = find_if(m_mapBit.begin(), m_mapBit.end(), CTagFinder(pImgKey));

	if (iter == m_mapBit.end())
		return nullptr;

	return iter->second->GetMemDC();
}

void CBitmapMgr::Release(void)
{
	for_each(m_mapBit.begin(), m_mapBit.end(), CDeleteMap());
	m_mapBit.clear();
}
