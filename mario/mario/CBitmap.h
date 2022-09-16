#pragma once
class CBitmap
{
public:
	CBitmap();
	~CBitmap();
public:
	HDC			GetMemDC() { return m_hMemDC; }
public:
	void		LoadBmp(const TCHAR* pFilePath);
	void		Release(void);
private:
	HDC			m_hMemDC;
	HBITMAP		m_hBitmap;
	HBITMAP		m_hOldbmp;
};

