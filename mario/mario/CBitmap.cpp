#include "pch.h"
#include "CBitmap.h"
#include "CCore.h"

CBitmap::CBitmap()
{
}


CBitmap::~CBitmap()
{
}

void CBitmap::LoadBmp(const TCHAR* pFilePath)
{
	HDC		hDC = GetDC(CCore::GetInstance()->GetWindowHandle());

	// CreateCompatibleDC : 호돤되는 DC정보를 토대로 복사해주는 함수

	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(CCore::GetInstance()->GetWindowHandle(), hDC);

	m_hBitmap = (HBITMAP)LoadImage(NULL,			// 프로그램 인스턴스 핸들, 이미지는 프로그램에서 얻어오지 않고 파일로 부터 직접 읽어들일 것이기 때문에 NULL
		pFilePath,		// 파일의 경로
		IMAGE_BITMAP,	// 어떤 타입을 읽어올지 결정
		0,				// 가로 크기
		0,				// 세로 크기
		LR_LOADFROMFILE | LR_CREATEDIBSECTION); // LR_LOADFROMFILE : 파일로부터 이미지를 로드하겠다는 옵션, LR_CREATEDIBSECTION : 읽어온 파일을 DIB 형식으로 변환하겠다는 옵션


// SelectObject : GDI 오브젝트를 선택하기 전에 기존에 가지고 있던 오브젝트를 반환한다.
	m_hOldbmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

}

void CBitmap::Release(void)
{
	SelectObject(m_hMemDC, m_hOldbmp);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}