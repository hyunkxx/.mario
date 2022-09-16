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

	// CreateCompatibleDC : ȣ�õǴ� DC������ ���� �������ִ� �Լ�

	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(CCore::GetInstance()->GetWindowHandle(), hDC);

	m_hBitmap = (HBITMAP)LoadImage(NULL,			// ���α׷� �ν��Ͻ� �ڵ�, �̹����� ���α׷����� ������ �ʰ� ���Ϸ� ���� ���� �о���� ���̱� ������ NULL
		pFilePath,		// ������ ���
		IMAGE_BITMAP,	// � Ÿ���� �о���� ����
		0,				// ���� ũ��
		0,				// ���� ũ��
		LR_LOADFROMFILE | LR_CREATEDIBSECTION); // LR_LOADFROMFILE : ���Ϸκ��� �̹����� �ε��ϰڴٴ� �ɼ�, LR_CREATEDIBSECTION : �о�� ������ DIB �������� ��ȯ�ϰڴٴ� �ɼ�


// SelectObject : GDI ������Ʈ�� �����ϱ� ���� ������ ������ �ִ� ������Ʈ�� ��ȯ�Ѵ�.
	m_hOldbmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

}

void CBitmap::Release(void)
{
	SelectObject(m_hMemDC, m_hOldbmp);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}