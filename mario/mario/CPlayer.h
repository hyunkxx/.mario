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
	//����
	bool IsFloor() const { return m_bIsFloor; } 
	void SetFloor(bool _value) { m_bIsFloor = _value; } //
	//
	void SetGround(bool _value) { m_bIsGround = _value; }

	bool IsJump() const { return m_bIsJump; }
	float GetMoveSpeed() const { return m_fMoveSpeed; }
	void SetMoveSpeed(float _value) { m_fMoveSpeed = _value; }
	void AddMoveSpeed(float _value) { m_fMoveSpeed += _value; }

	bool IsHeading() const { return m_bIsHeading; }
public:
	void gravity(bool _value);
	void Scroll();
	void RopeRide(float _x);
private:
	//����
	void KeyInput(); //Ű�����Է� ��Ƶα� ���� �Լ�
	void YMove(); //Y���̵� ��Ƶα����� �Լ�
	void RectUpdate(); //Obj�� setRect()���� �Լ�

	void SubJump(bool _value); // �����̽��� ��������
	void SubHeading(bool _value); //�Ӹ��� õ�忡 �������
	void Collide_MapEnd(MapSize _size); //�ʳ��� �������
	
private:
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
	void scrollOffset();
	void onLine();
private:
	//����
	float m_fMoveSpeed;
	bool m_bIsJump;
	bool m_bIsGround;

	//����
	float m_fYSpeed; //Y�� �ӵ� �����ϱ� ���� ����
	bool m_bIsFloor; //�ٴڿ� �浹�ߴ��� Ȯ���ϱ� ���� ����
	bool m_bIsHeading; //�Ӹ��� õ��(������Ʈ)�� ��Ҵ��� Ȯ���ϱ� ���� ����
	UINT m_iJumpCount;

//����
	ULONGLONG beginTime;
	bool bDebug;
public:
	enum class ANIM { IDLE_L , IDLE_R , WALK_R , WALK_L , END };
	void SetAnimState(ANIM _eState) { m_eState = _eState; };
	bool IsUse() { return m_bUse; }
private:
	void animPlay(HDC _hdc);
	void stateCheck();
public:
	bool m_bUse;

	ANIM m_eState;

	class CAnimClip* m_pClipIdle_r;
	class CAnimClip* m_pClipWalk_r;
	class CAnimClip* m_pClipIdle_l;
	class CAnimClip* m_pClipWalk_l;
};

