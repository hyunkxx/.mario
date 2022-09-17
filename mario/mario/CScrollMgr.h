#pragma once
class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();
public:
	static CScrollMgr* pInstance;
	static CScrollMgr* GetInst() { if (!pInstance) { pInstance = new CScrollMgr; } return pInstance; }public:
	static void Destroy() { SAFE_DELETE(pInstance); }
public:
	float GetScrollX() { return m_fX; }
	float GetScrollY() { return m_fY; }
	void SetScrollX(float _value) { m_fX = _value; }
	void SetScrollY(float _value) { m_fY = _value; }
	void ScrollLock(float _Width, float _Height);
	void Reset() { m_fX = 0.f; m_fY = 0.f; }
private:
	float m_fX;
	float m_fY;
};

