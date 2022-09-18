#pragma once

#include "CObject.h"

class CAnimClip;

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
	//����
	void KeyInput(); //Ű�����Է� ��Ƶα� ���� �Լ�
	void YMove(); //Y���̵� ��Ƶα����� �Լ�
	void RectUpdate(); //Obj�� setRect()���� �Լ�

	void SubJump(bool _value); // �����̽��� ��������
	void SubHeading(bool _value); //�Ӹ��� õ�忡 �������
	void Collide_MapEnd(int _Left, int _Top, int _Right, int _Bottom); //�ʳ��� �������
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

<<<<<<< Updated upstream
//����
	float m_fYSpeed; //Y�� �ӵ� �����ϱ� ���� ����
	bool m_bIsFloor; //�ٴڿ� �浹�ߴ��� Ȯ���ϱ� ���� ����
	bool m_bIsHeading; //�Ӹ��� õ��(������Ʈ)�� ��Ҵ��� Ȯ���ϱ� ���� ����

	ULONGLONG beginTime;
=======
	//����
	float m_fPLine;
	float m_fYSpeed; //Y�� �ӵ� �����ϱ� ���� ����
	bool m_bIsFloor; //�ٴڿ� �浹�ߴ��� Ȯ���ϱ� ���� ����
	bool m_bIsHeading; //�Ӹ��� õ��(������Ʈ)�� ��Ҵ��� Ȯ���ϱ� ���� ����
	UINT m_iJumpCount;
	bool m_bIsonLine;
//����
	ULONGLONG beginTime;
	bool bDebug;
public:
	enum class ANIM { IDLE_L, IDLE_R, WALK_R, WALK_L, ROPE, END };
	void SetAnimState(ANIM _eState) { m_eState = _eState; };
	bool IsUse() { return m_bUse; }
private:
	void animPlay(HDC _hdc);
	void stateCheck();
public:
	bool m_bUse;

	ANIM m_eState;

	CAnimClip* m_pClipIdle_r;
	CAnimClip* m_pClipWalk_r;
	CAnimClip* m_pClipIdle_l;
	CAnimClip* m_pClipWalk_l;
	CAnimClip* m_pClipJump_l;
	CAnimClip* m_pClipJump_r;
	CAnimClip* m_pClipRope;
>>>>>>> Stashed changes
};

