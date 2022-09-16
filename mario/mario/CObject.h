#pragma once

class CObject
{
public:
	explicit CObject();
	explicit CObject(float _x, float _y, float _scale);
	explicit CObject(Transform _transform);
	virtual ~CObject();
private: // 오브젝트간 대입,복사,이동 불가능
	CObject(const CObject& rhs) = delete;
	//CObject(CObject&& rhs) = delete;
	CObject& operator=(const CObject& rhs) = delete;
	//CObject& operator=(CObject&& rhs) = delete;
public:
	virtual void Initalize();
	virtual int  Update(float _fDeltaTime);
	virtual void LateUpdate(float _fDeltaTime);
	virtual void Render(HDC _hdc);
	virtual void Release();
public:
	const Transform& GetTransform() const { return m_tTransform; }
	const float GetX() const { return m_tTransform.fX; }
	const float GetY() const { return m_tTransform.fY; }
	const float GetScale() const { return m_tTransform.fScale; }
	const OBJ_STATE& GetState() const { return m_eObjState; }
	const RECT& GetRect() const { return m_rcRect; }

	void SetTransform(Transform& _transform) { m_tTransform = _transform; }
	void SetX(float _value) { m_tTransform.fX = _value; }
	void SetY(float _value) { m_tTransform.fY = _value; }
	void SetScale(float _value) { m_tTransform.fScale = _value; }
	void SetState(const OBJ_STATE& _eState) { m_eObjState = _eState; }

	bool IsDisable() { return m_eObjState == OBJ_STATE::DISABLE; }

	void AddPosition(float _fX, float _fY) { m_tTransform.fX += _fX; m_tTransform.fY += _fY; }
	void AddScale(float _fScale) { m_tTransform.fScale += _fScale; }
public:

private:
	void setRect();
private:
	OBJ_STATE m_eObjState;
	Transform m_tTransform;
	RECT	  m_rcRect;
};

