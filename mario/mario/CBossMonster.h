#pragma once
#include "CMonster.h"

class CObject;

enum BOSS_STATE
{
	BOSS_IDLE,
	BOSS_ATTACK,

	BOSS_END
};

enum EFFECT_STATE
{
	BLACKMETEO_ON,
	CURSE_ON,
	LIGHTNING_ON,

	EFFECT_STATE_OFF
};

enum BOSS_SKILL_EFFECT
{
	EFFECT_BLACKMETEO,
	EFFECT_FIREMETEO,

	EFFECT_END
};

enum BOSS_BODY_PART
{
	WING,
	TAIL,
	LEFT_HEAD,
	RIGHT_HEAD,
	LEFT_BODY,
	RIGHT_BODY,
	DOWN_BODY,
	CENTER_HEAD,

	BOSS_PART_SIZE
};

class CBossMonster : public CMonster
{
public:
	CBossMonster();
	~CBossMonster();

public:
	virtual void Initalize();
	virtual int  Update(float _fDeltaTime);
	virtual void LateUpdate(float _fDeltaTime);
	virtual void Render(HDC _hDC);
	virtual void Release();

	void		 RenderBoss(HDC _hDC);
	void		 SetTarget(CObject* _pTarget) { m_pTarget = _pTarget; }

public:
	void BossRectSetting();
	void BossImageSetting();
	void BossFrameSetting();
	void BossMotionSetting();

	void BossEffectFrame();

public:
	//vector<RECT> GetBossRect() { return *m_vecBossRect; }

private:
	// �̹��� ����
	void SettingCenterHead();
	void SettingLeftBody();
	void SettingRightBody();
	void SettingDownBody();
	void SettingLeftHead();
	void SettingRightHead();
	// ����, ����
	void SettingWing();
	void SettingTail();
	

public:
	// �̹��� ���
	void RenderCenterHead(HDC _hDC);
	void RenderLeftHead(HDC _hDC);
	void RenderRightHead(HDC _hDC);
	// �Ӹ�

	void RenderLeftBody(HDC _hDC);
	void RenderRightBody(HDC _hDC);
	void RenderDownBody(HDC _hDC);
	// ����

	// ����, ����
	void RenderWing(HDC _hDC);
	void RenderTail(HDC _hDC);

	void RenderEffect(HDC _hDC);
public:
	// ���� ������ ����
	void CenterHeadMotion();
	void RightHeadMotion();
	void LeftHeadMotion();
	// �Ӹ�

	void LeftBodyMotion();
	void RightBodyMotion();
	void DownBodyMotion();
	// ����

	// ����, ����
	void WingMotion();
	void TailMotion();

public:
	// ������

	void CenterHeadFrame();
	void LeftHeadFrame();
	void RightHeadFrame();

	void LeftBodyFrame();
	void RightBodyFrame();
	void DownBodyFrame();

	void WingFrame();
	void TailFrame();


private:
	// RECT ����
	RECT	m_tBossRect[8];

	// ���� ������
	FRAME	m_tCenterHeadFrame;
	FRAME	m_tLeftHeadFrame;
	FRAME	m_tRightHeadFrame;

	FRAME	m_tLeftBodyFrame;
	FRAME	m_tRightBodyFrame;
	FRAME	m_tDownBodyFrame;
	FRAME	m_tWingFrame;
	FRAME	m_tTailFrame;

	// ����Ʈ ������

	//FRAME	m_tWingFrame;
	//FRAME	m_tTailFrame;

	// �ð���
	DWORD	m_dwBossTimer;
	// ��ų 
	DWORD	m_dwSkillTimer;

	// ���� ����, ���� ����
	BOSS_STATE m_eBossCurState[BOSS_PART_SIZE];
	BOSS_STATE m_eBossPrevState[BOSS_PART_SIZE];
	// ����Ʈ ����
	EFFECT_STATE m_eEffectCurState[BOSS_PART_SIZE];
	EFFECT_STATE m_eEffectPrevState[BOSS_PART_SIZE];
	 
	// ��ũ�� ��
	int iScrollX;
	int iScrollY;

	// �÷��̾� ��ġ
	float m_fTargetY;
	float m_fTargetX;

	vector<FRAME>	m_vecEffectFrame[BOSS_PART_SIZE];

	// �÷��̾�
	CObject* m_pTarget;

	bool m_bIsTarGetOn = false;
	bool m_bIsLightning = false;
	bool m_bIsCurse = false;
};

