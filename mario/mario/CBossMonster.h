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
	// 이미지 세팅
	void SettingCenterHead();
	void SettingLeftBody();
	void SettingRightBody();
	void SettingDownBody();
	void SettingLeftHead();
	void SettingRightHead();
	// 날개, 꼬리
	void SettingWing();
	void SettingTail();
	

public:
	// 이미지 출력
	void RenderCenterHead(HDC _hDC);
	void RenderLeftHead(HDC _hDC);
	void RenderRightHead(HDC _hDC);
	// 머리

	void RenderLeftBody(HDC _hDC);
	void RenderRightBody(HDC _hDC);
	void RenderDownBody(HDC _hDC);
	// 몸통

	// 날개, 꼬리
	void RenderWing(HDC _hDC);
	void RenderTail(HDC _hDC);

	void RenderEffect(HDC _hDC);
public:
	// 현재 움직임 세팅
	void CenterHeadMotion();
	void RightHeadMotion();
	void LeftHeadMotion();
	// 머리

	void LeftBodyMotion();
	void RightBodyMotion();
	void DownBodyMotion();
	// 몸통

	// 날개, 꼬리
	void WingMotion();
	void TailMotion();

public:
	// 프레임

	void CenterHeadFrame();
	void LeftHeadFrame();
	void RightHeadFrame();

	void LeftBodyFrame();
	void RightBodyFrame();
	void DownBodyFrame();

	void WingFrame();
	void TailFrame();


private:
	// RECT 정보
	RECT	m_tBossRect[8];

	// 몸통 프레임
	FRAME	m_tCenterHeadFrame;
	FRAME	m_tLeftHeadFrame;
	FRAME	m_tRightHeadFrame;

	FRAME	m_tLeftBodyFrame;
	FRAME	m_tRightBodyFrame;
	FRAME	m_tDownBodyFrame;
	FRAME	m_tWingFrame;
	FRAME	m_tTailFrame;

	// 이펙트 프레임

	//FRAME	m_tWingFrame;
	//FRAME	m_tTailFrame;

	// 시간값
	DWORD	m_dwBossTimer;
	// 스킬 
	DWORD	m_dwSkillTimer;

	// 보스 현재, 이전 상태
	BOSS_STATE m_eBossCurState[BOSS_PART_SIZE];
	BOSS_STATE m_eBossPrevState[BOSS_PART_SIZE];
	// 이펙트 상태
	EFFECT_STATE m_eEffectCurState[BOSS_PART_SIZE];
	EFFECT_STATE m_eEffectPrevState[BOSS_PART_SIZE];
	 
	// 스크롤 값
	int iScrollX;
	int iScrollY;

	// 플레이어 위치
	float m_fTargetY;
	float m_fTargetX;

	vector<FRAME>	m_vecEffectFrame[BOSS_PART_SIZE];

	// 플레이어
	CObject* m_pTarget;

	bool m_bIsTarGetOn = false;
	bool m_bIsLightning = false;
	bool m_bIsCurse = false;
};

