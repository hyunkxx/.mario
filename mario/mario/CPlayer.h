#pragma once

#include "CObject.h"

class CPlayer : public CObject
{
public:
	explicit CPlayer();
	explicit CPlayer(float _x, float _y, float _scale);
	explicit CPlayer(Transform _transform);
	virtual ~CPlayer();
public:
	void Initalize() override;
	int Update(float _fDeltaTime) override;
	void LateUpdate(float _fDeltaTime) override;
	void Render(HDC _hdc) override;
	void Release() override;
public:
	bool IsGround() const { return m_bIsGround; }
	bool IsJump() const { return m_bIsJump; }
	float GetMoveSpeed() const { return m_fMoveSpeed; }

	void SetMoveSpeed(float _value) { m_fMoveSpeed = _value; }
	void AddMoveSpeed(float _value) { m_fMoveSpeed += _value; }
private:
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
	void scrollOffset();
	void onLine();
	void gravity(bool _value);
private:
	float m_fMoveSpeed;
	bool m_bIsJump;
	bool m_bIsGround;

	ULONGLONG beginTime;
};

