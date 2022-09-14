#pragma once


class CInputMgr
{
private:
	CInputMgr();
	~CInputMgr();
	CInputMgr(const CInputMgr& rhs) = delete;
	CInputMgr(CInputMgr&& rhs) = delete;
	CInputMgr& operator=(const CInputMgr& rhs) = delete;
	CInputMgr& operator=(CInputMgr&& rhs) = delete;
public:
	static CInputMgr* pInstance;
	static CInputMgr* GetInstance() { if (!pInstance) { pInstance = new CInputMgr; } return pInstance; }
	static void Destroy() { if (pInstance) { delete pInstance; pInstance = nullptr; } }
public:
	void Update();
	bool GetKey(int iKey, KEY_STATE _eType);
public:
	KeyState m_tKeyState[VK_MAX];
};


