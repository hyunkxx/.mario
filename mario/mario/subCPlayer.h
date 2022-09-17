#pragma once
#include "CObject.h"
class subCPlayer :
	public CObject
{
public:
	friend class CStageTwo;
	subCPlayer() = delete;
	subCPlayer(float _x, float _y, float _scale);
	virtual ~subCPlayer();

public:
	virtual void Initalize() override;
	virtual int  Update(float _fDeltaTime) override;
	virtual void LateUpdate(float _fDeltaTime) override;
	virtual void Render(HDC _hdc) override;
	virtual void Release() override;

private:
	void		Key_Input(void);
	void		Jump(void);
	void		Dash(void);
	void		Gravity(void);
	void		setRect(void);
	void		Offset(void);
	void		Move(void);

	const RECT& GetRect(void) { return m_rcRect; }

private:
	float		m_fXAccel;
	float		m_fYAccel;
	float		m_fXSpeed;
	float		m_fYSpeed;
	bool		m_bJump;
	bool		m_bJumping;
	short		m_iJump_Count;
	bool		m_bDash;
	bool		m_bDashing;
	bool        m_Ground_Reaction;

};

