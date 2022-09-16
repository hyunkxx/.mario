#pragma once

#include "CBitmap.h"

class CBitmapMgr
{
private:
	CBitmapMgr();
	~CBitmapMgr();
public:
	void InsertBmp(const TCHAR* pFilePath, const TCHAR* pImgKey);
	HDC	FindBmp(const TCHAR* pImgKey);
	void Release(void);
public:
	static CBitmapMgr* GetInstance(void)
	{
		if (!m_pInstance)
			m_pInstance = new CBitmapMgr;
		return m_pInstance;
	}
	static void	Destroy()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static CBitmapMgr* m_pInstance;
	map<const TCHAR*, CBitmap*>		m_mapBit;
};

