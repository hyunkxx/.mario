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
	int  Update(float _fDeltaTime) override;
	void LateUpdate(float _fDeltaTime) override;
	void Render(HDC _hdc) override;
	void Release() override;
public:
	bool IsGround() const { return m_bIsGround; }
	void SetGround(bool _value) { m_bIsGround = _value; }

	bool IsJump() const { return m_bIsJump; }
	float GetMoveSpeed() const { return m_fMoveSpeed; }
	void SetMoveSpeed(float _value) { m_fMoveSpeed = _value; }
	void AddMoveSpeed(float _value) { m_fMoveSpeed += _value; }

	bool IsHeading() const { return m_bIsHeading; }
public:
	void gravity(bool _value);
	void Scroll();
private:
	//윤섭
	void KeyInput(); //키보드입력 모아두기 위한 함수
	void YMove(); //Y축이동 모아두기위한 함수
	void RectUpdate(); //Obj의 setRect()같은 함수

	void SubJump(bool _value); // 스페이스바 눌렀을때
	void SubHeading(bool _value); //머리가 천장에 닿았을때
	void Collide_MapEnd(int _Left, int _Top, int _Right, int _Bottom); //맵끝에 닿았을때
private:
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
	void scrollOffset();
	void onLine();
private:
//동현
	float m_fMoveSpeed;
	bool m_bIsJump;
	bool m_bIsGround;

//윤섭
	float m_fYSpeed; //Y축 속도 저장하기 위한 변수
	bool m_bIsFloor; //바닥에 충돌했는지 확인하기 위한 변수
	bool m_bIsHeading; //머리가 천장(오브젝트)에 닿았는지 확인하기 위한 변수

	ULONGLONG beginTime;
};

