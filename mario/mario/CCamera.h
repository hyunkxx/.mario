#pragma once

class CObject;

class CCamera
{
private:
	CCamera();
	~CCamera();
public:
	static CCamera* pInstance;
	static CCamera* GetInst() { if (!pInstance) { pInstance = new CCamera; } return pInstance; }
	static void Destroy() { if (pInstance) { delete pInstance; pInstance = nullptr; } }
public:
	void SetTarget(CObject* _pObj) { m_pTarget = _pObj; }
	void SetLookAtPos(Vec2 _value) { m_fLookAt = _value; }
	void SetOffset(Vec2 _value) { m_fOffset = _value; }

	CObject* GetTarget() { return  m_pTarget; }
	Vec2 GetLookAtPos() { return m_fLookAt; }
	Vec2 GetOffset() { return m_fOffset; }
public:
	void Update();
	Vec2 CalcOffset(float _x, float _y);
private:
	Vec2 m_fLookAt;
	Vec2 m_fOffset;
	CObject* m_pTarget;
};


