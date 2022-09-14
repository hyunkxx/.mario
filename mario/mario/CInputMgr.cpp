#include "pch.h"
#include "CInputMgr.h"

CInputMgr* CInputMgr::pInstance;

CInputMgr::CInputMgr()
{
	for (auto& iter : m_tKeyState)
	{
		iter.m_bPrevPressed = false;
		iter.m_eState = KEY_STATE::NONE;
	}
}

CInputMgr::~CInputMgr()
{
}

void CInputMgr::Update()
{
	//모든키 순회
	for (int i = 0; i < VK_MAX; i++)
	{
		//Down
		if (!m_tKeyState[i].m_bPrevPressed && GetAsyncKeyState(i) & 0x8000)
		{
			m_tKeyState[i].m_bPrevPressed = true;
			m_tKeyState[i].m_eState = KEY_STATE::DOWN;
			continue;
		}
		//Press
		else if (m_tKeyState[i].m_bPrevPressed && GetAsyncKeyState(i) & 0x8000)
		{
			m_tKeyState[i].m_eState = KEY_STATE::PRESSED;
			continue;
		}
		//Up
		else if (m_tKeyState[i].m_bPrevPressed && !(GetAsyncKeyState(i) & 0x8000))
		{
			m_tKeyState[i].m_bPrevPressed = false;
			m_tKeyState[i].m_eState = KEY_STATE::UP;
			continue;
		}
		else if (!m_tKeyState[i].m_bPrevPressed && !(GetAsyncKeyState(i) & 0x8000))
		{
			m_tKeyState[i].m_eState = KEY_STATE::NONE;
		}
	}
}

bool CInputMgr::GetKey(int iKey, KEY_STATE _eType)
{
	return (m_tKeyState[iKey].m_eState == _eType);
}
