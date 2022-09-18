#include "pch.h"
#include "CBossMonster.h"
#include "CBitmapMgr.h"
#include "CScrollMgr.h"

CBossMonster::CBossMonster() : m_dwBossTimer(GetTickCount()), m_pTarget(nullptr),
m_fTargetY(0.f), m_fTargetX(0.f), m_dwSkillTimer(GetTickCount())
{
	BossRectSetting();
	BossImageSetting();

	for (int i = 0; i < BOSS_PART_SIZE; ++i)
	{
		m_eBossCurState[i] = BOSS_IDLE;
		m_eBossPrevState[i] = BOSS_END;
	}

	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Boss/Stone/Stone.bmp", L"Stone");


}


CBossMonster::~CBossMonster()
{

}

void CBossMonster::Initalize()
{

}

int CBossMonster::Update(float _fDeltaTime)
{

	if (m_dwSkillTimer + 800 < GetTickCount())
	{
		int iRandValue = rand() % 8;
		if (m_eBossCurState[iRandValue] == BOSS_IDLE)
			m_eBossCurState[iRandValue] = BOSS_ATTACK;

		m_dwSkillTimer = GetTickCount();
	}

	if (m_pTarget && !m_bIsTarGetOn)
	{
		m_fTargetX = m_pTarget->GetX();
		m_fTargetY = m_pTarget->GetY();
		m_bIsTarGetOn = true;
	}


	iScrollX = CScrollMgr::GetInst()->GetScrollX();
	iScrollY = CScrollMgr::GetInst()->GetScrollY();

	BossMotionSetting();
	BossFrameSetting();

	BossEffectFrame();

	return 0;
}

void CBossMonster::LateUpdate(float _fDeltaTime)
{
	
}

void CBossMonster::Render(HDC _hDC)
{


	RenderBoss(_hDC);
}

void CBossMonster::Release()
{
}

void CBossMonster::BossRectSetting()
{

	m_tBossRect[LEFT_HEAD] = { 425, 505, 0, 0 };
	m_tBossRect[CENTER_HEAD] = { 596, 387, 757, 330 };
	m_tBossRect[RIGHT_HEAD] = { 660, 505, 0, 0 };

	m_tBossRect[LEFT_BODY] = { 462, 681, 677, 825 };
	m_tBossRect[RIGHT_BODY] = { 677, 681, 892, 825 };

	m_tBossRect[WING] = { 382, 650, 0, 0 };
	m_tBossRect[DOWN_BODY] = { 419, 815, 767, 1371 };
	m_tBossRect[TAIL] = { 698, 850, 0, 0 };

}

void CBossMonster::BossImageSetting()
{
	SettingWing();
	SettingTail();

	SettingLeftHead();
	SettingRightHead();
	SettingCenterHead();

	SettingLeftBody();
	SettingRightBody();
	SettingDownBody();

}

void CBossMonster::BossFrameSetting()
{

	WingFrame();
	TailFrame();

	LeftHeadFrame();
	RightHeadFrame();
	CenterHeadFrame();

	LeftBodyFrame();
	RightBodyFrame();
	DownBodyFrame();

}

void CBossMonster::BossMotionSetting()
{
	//if (m_dwBossTimer + 1000 < GetTickCount())
	//{
	//	int iRandValue = rand() % 8;

	//	//m_eBossCurState[iRandValue] = BOSS_ATTACK;
	//	
	//	m_dwBossTimer = GetTickCount();
	//}

	WingMotion();
	TailMotion();

	LeftHeadMotion();
	RightHeadMotion();
	CenterHeadMotion();

	LeftBodyMotion();
	RightBodyMotion();
	DownBodyMotion();

}

void CBossMonster::RenderBoss(HDC _hDC)
{
	//m_eBossCurState;

	RenderWing(_hDC);
	RenderTail(_hDC);

	RenderLeftHead(_hDC);
	RenderRightHead(_hDC);

	RenderLeftBody(_hDC);
	RenderDownBody(_hDC);

	RenderRightBody(_hDC);

	RenderCenterHead(_hDC);

	RenderEffect(_hDC);

}

void CBossMonster::SettingCenterHead()
{
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Boss/Head/CenterHead/CenterHeadStand.bmp", L"CenterHeadStand");

	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Boss/Head/CenterHead/CenterHeadFire.bmp", L"CenterHeadFire");
}

void CBossMonster::SettingLeftBody()
{
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Boss/Body/LeftBody/LeftBodyStand.bmp", L"LeftBodyStand");

	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Boss/Body/LeftBody/LeftBodyAttack.bmp", L"LeftBodyAttack");
}

void CBossMonster::SettingRightBody()
{
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Boss/Body/RightBody/RightBodyStand.bmp", L"RightBodyStand");

	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Boss/Body/RightBody/RightBodyAttack.bmp", L"RightBodyAttack");
	
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Boss/Body/BlackMeteo.bmp", L"BlackMeteo");

}

void CBossMonster::SettingDownBody()
{
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Boss/Body/DownBody/DownBodyStand.bmp", L"DownBodyStand");

	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Boss/Body/DownBody/DownBodyAttack.bmp", L"DownBodyAttack");
}

void CBossMonster::SettingLeftHead()
{
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Boss/Head/LeftHead/LeftHeadStand.bmp", L"LeftHeadStand");

	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Boss/Head/LeftHead/LeftHeadAttack.bmp", L"LeftHeadAttack")
		;
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Boss/Head/LeftHead/Curse.bmp", L"Curse");

}

void CBossMonster::SettingRightHead()
{
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Boss/Head/RightHead/RightHeadStand.bmp", L"RightHeadStand");

	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Boss/Head/RightHead/RightHeadAttack.bmp", L"RightHeadAttack");
	
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Boss/Head/RightHead/Lightning.bmp", L"Lightning");
}

void CBossMonster::SettingWing()
{
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Boss/Wing/WingStand.bmp", L"WingStand");
}

void CBossMonster::SettingTail()
{
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Boss/Tail/TailStand.bmp", L"TailStand");
	
	CBitmapMgr::GetInstance()->InsertBmp(L"../Image/Monster/Boss/Tail/TailAttack.bmp", L"TailAttack");

}

void CBossMonster::RenderCenterHead(HDC _hDC)
{

	if (m_eBossCurState[CENTER_HEAD] == BOSS_IDLE)
	{
		HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"CenterHeadStand");

		GdiTransparentBlt(_hDC,
			(int)m_tBossRect[CENTER_HEAD].left + iScrollX,
			(int)20 + m_tBossRect[CENTER_HEAD].top + iScrollY,
			161,
			322,
			hMemDC,
			(int)161 * m_tCenterHeadFrame.iStart,
			(int)330 * m_tCenterHeadFrame.iMotion,
			(int)161,
			(int)330,
			RGB(0, 0, 0));
	}
	else if (m_eBossCurState[CENTER_HEAD] == BOSS_ATTACK)
	{
		HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"CenterHeadFire");

		GdiTransparentBlt(_hDC,
			(int)400 + iScrollX, 
			(int)305 + iScrollY,
			552,
			777,
			hMemDC,
			(int)552 * m_tCenterHeadFrame.iStart,
			(int)777 * m_tCenterHeadFrame.iMotion,
			(int)552,
			(int)777,
			RGB(255, 255, 255));

	}
}

void CBossMonster::RenderLeftHead(HDC _hDC)
{
	if (m_eBossCurState[LEFT_HEAD] == BOSS_IDLE)
	{
		HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"LeftHeadStand");

		GdiTransparentBlt(_hDC,
			(int)m_tBossRect[LEFT_HEAD].left + iScrollX,
			(int)20 + m_tBossRect[LEFT_HEAD].top + iScrollY,
			261,
			209,
			hMemDC,
			(int)261 * m_tLeftHeadFrame.iStart,
			(int)209 * m_tLeftHeadFrame.iMotion,
			(int)261,
			(int)209,
			RGB(0, 0, 0));
	}
	else if (m_eBossCurState[LEFT_HEAD] == BOSS_ATTACK)
	{
		// 얼음 브레스
		HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"LeftHeadAttack");

		GdiTransparentBlt(_hDC,
			(int)405 + iScrollX,
			(int)505 + iScrollY,
			285,
			268,
			hMemDC,
			(int)285 * m_tLeftHeadFrame.iStart,
			(int)268 * m_tLeftHeadFrame.iMotion,
			(int)285,
			(int)268,
			RGB(0, 0, 0));
	}
}

void CBossMonster::RenderRightHead(HDC _hDC)
{
	if (m_eBossCurState[RIGHT_HEAD] == BOSS_IDLE)
	{
		HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"RightHeadStand");

		GdiTransparentBlt(_hDC,
			(int)m_tBossRect[RIGHT_HEAD].left + iScrollX,
			(int)20 + m_tBossRect[RIGHT_HEAD].top + iScrollY,
			261,
			209,
			hMemDC,
			(int)261 * m_tRightHeadFrame.iStart,
			(int)209 * m_tRightHeadFrame.iMotion,
			(int)261,
			(int)209,
			RGB(0, 0, 0));
	}
	else if (m_eBossCurState[RIGHT_HEAD] == BOSS_ATTACK)
	{
		HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"RightHeadAttack");

		GdiTransparentBlt(_hDC,
			(int)660 + iScrollX,
			(int)525 + iScrollY,
			349,
			353,
			hMemDC,
			(int)349 * m_tRightHeadFrame.iStart,
			(int)353 * m_tRightHeadFrame.iMotion,
			(int)349,
			(int)353,
			RGB(0, 0, 0));
	}
}

void CBossMonster::RenderLeftBody(HDC _hDC)
{
	if (m_eBossCurState[LEFT_BODY] == BOSS_IDLE)
	{
		HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"LeftBodyStand");

		GdiTransparentBlt(_hDC,
			(int)m_tBossRect[LEFT_BODY].left + iScrollX,
			(int)20 + m_tBossRect[LEFT_BODY].top + iScrollY,
			215,
			144,
			hMemDC,
			(int)215 * m_tLeftBodyFrame.iStart,
			(int)144 * m_tLeftBodyFrame.iMotion,
			(int)215,
			(int)144,
			RGB(0, 0, 0));
	}
	else if (m_eBossCurState[LEFT_BODY] == BOSS_ATTACK)
	{
		HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"LeftBodyAttack");
		GdiTransparentBlt(_hDC,
			(int)375 + iScrollX,
			(int)630 + iScrollY,
			302,
			215,
			hMemDC,
			(int)302 * m_tLeftBodyFrame.iStart,
			(int)215 * m_tLeftBodyFrame.iMotion,
			(int)302,
			(int)215,
			RGB(0, 0, 0));
	}
}

void CBossMonster::RenderRightBody(HDC _hDC)
{
	if (m_eBossCurState[RIGHT_BODY] == BOSS_IDLE)
	{

		HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"RightBodyStand");

		GdiTransparentBlt(_hDC,
			(int)m_tBossRect[RIGHT_BODY].left + iScrollX,
			(int)20 + m_tBossRect[RIGHT_BODY].top + iScrollY,
			215,
			144,
			hMemDC,
			(int)215 * m_tRightBodyFrame.iStart,
			(int)144 * m_tRightBodyFrame.iMotion,
			(int)215,
			(int)144,
			RGB(0, 0, 0));
	}
	else if (m_eBossCurState[RIGHT_BODY] == BOSS_ATTACK)
	{
		HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"RightBodyAttack");

		GdiTransparentBlt(_hDC,
			(int)675 + iScrollX,
			(int)689 + iScrollY,
			373,
			229,
			hMemDC,
			(int)373 * m_tRightBodyFrame.iStart,
			(int)229 * m_tRightBodyFrame.iMotion,
			(int)373,
			(int)229,
			RGB(0, 0, 0));
	}

	
}

void CBossMonster::RenderDownBody(HDC _hDC)
{
	if (m_eBossCurState[DOWN_BODY] == BOSS_IDLE)
	{
		HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"DownBodyStand");

		GdiTransparentBlt(_hDC,
			(int)m_tBossRect[DOWN_BODY].left + iScrollX,
			(int)20 + m_tBossRect[DOWN_BODY].top + iScrollY,
			514,
			192,
			hMemDC,
			(int)514 * m_tDownBodyFrame.iStart,
			(int)192 * m_tDownBodyFrame.iMotion,
			(int)514,
			(int)192,
			RGB(0, 0, 0));
	}
	else if (m_eBossCurState[DOWN_BODY] == BOSS_ATTACK)
	{
		HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"DownBodyAttack");

		GdiTransparentBlt(_hDC,
			(int)345 + iScrollX,
			(int)797 + iScrollY,
			590,
			257,
			hMemDC,
			(int)590 * m_tDownBodyFrame.iStart,
			(int)257 * m_tDownBodyFrame.iMotion,
			(int)590,
			(int)257,
			RGB(0, 0, 0));
	}
}

void CBossMonster::RenderWing(HDC _hDC)
{
	HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"WingStand");

	GdiTransparentBlt(_hDC,
		(int)m_tBossRect[WING].left + iScrollX,
		(int)20 + m_tBossRect[WING].top + iScrollY,
		590,
		296,
		hMemDC,
		(int)590 * m_tWingFrame.iStart,
		(int)296 * m_tWingFrame.iMotion,
		(int)590,
		(int)296,
		RGB(255, 255, 255));
}

void CBossMonster::RenderTail(HDC _hDC)
{
	if (m_eBossCurState[TAIL] == BOSS_IDLE)
	{
		HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"TailStand");

		GdiTransparentBlt(_hDC,
			(int)m_tBossRect[TAIL].left + iScrollX,
			(int)20 + m_tBossRect[TAIL].top + iScrollY,
			406,
			146,
			hMemDC,
			(int)406 * m_tTailFrame.iStart,
			(int)146 * m_tTailFrame.iMotion,
			(int)406,
			(int)146,
			RGB(0, 0, 0));
	}
	else if (m_eBossCurState[TAIL] == BOSS_ATTACK)
	{
		HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"TailAttack");

		GdiTransparentBlt(_hDC,
			(int)675 + iScrollX,
			(int)622 + iScrollY,
			552,
			426,
			hMemDC,
			(int)552 * m_tTailFrame.iStart,
			(int)426 * m_tTailFrame.iMotion,
			(int)552,
			(int)426,
			RGB(0, 0, 0));
	}
}

void CBossMonster::RenderEffect(HDC _hDC)
{
	if (m_eEffectCurState[RIGHT_BODY] == BLACKMETEO_ON)
	{
		HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"BlackMeteo");

		GdiTransparentBlt(_hDC,
			(int)(m_fTargetX - 150) + iScrollX,
			(int)(m_fTargetY - 550) + iScrollY,
			306,
			644,
			hMemDC,
			(int)306 * m_vecEffectFrame[RIGHT_BODY].front().iStart,
			(int)644 * m_vecEffectFrame[RIGHT_BODY].front().iMotion,
			(int)306,
			(int)644,
			RGB(0, 0, 0));
	}

	if (m_eEffectCurState[RIGHT_HEAD] == LIGHTNING_ON && m_bIsLightning)
	{
		HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"Lightning");

		GdiTransparentBlt(_hDC,
			(int)m_fTargetX + iScrollX,
			(int)250 + iScrollY,
			180,
			845,
			hMemDC,
			(int)180 * m_vecEffectFrame[RIGHT_HEAD].front().iStart,
			(int)845 * m_vecEffectFrame[RIGHT_HEAD].front().iMotion,
			(int)180,
			(int)845,
			RGB(0, 0, 0));
	}

	if (m_eEffectCurState[LEFT_HEAD] == CURSE_ON && m_bIsCurse)
	{
		HDC	hMemDC = CBitmapMgr::GetInstance()->FindBmp(L"Curse");

		GdiTransparentBlt(_hDC,
			(int)(m_fTargetX - 250)+ iScrollX,
			(int)(m_fTargetY - 200)+ iScrollY,
			465,
			369,
			hMemDC,
			(int)465 * m_vecEffectFrame[LEFT_HEAD].front().iStart,
			(int)369 * m_vecEffectFrame[LEFT_HEAD].front().iMotion,
			(int)465,
			(int)369,
			RGB(255, 0, 255));
	}
}

void CBossMonster::CenterHeadMotion()
{
	if (m_eBossCurState[CENTER_HEAD] != m_eBossPrevState[CENTER_HEAD])
	{
		switch (m_eBossCurState[CENTER_HEAD])
		{
		case BOSS_STATE::BOSS_IDLE:
			m_tCenterHeadFrame.iStart = 0;
			m_tCenterHeadFrame.iEnd = 9;
			m_tCenterHeadFrame.iMotion = 0;
			m_tCenterHeadFrame.dwSpeed = (DWORD)100.f;
			m_tCenterHeadFrame.dwTime = GetTickCount();
			break;

		case BOSS_STATE::BOSS_ATTACK:
			// 아래로 불쏘는 공격
			m_tCenterHeadFrame.iStart = 0;
			m_tCenterHeadFrame.iEnd = 26;
			m_tCenterHeadFrame.iMotion = 0;
			m_tCenterHeadFrame.dwSpeed = (DWORD)80.f;
			m_tCenterHeadFrame.dwTime = GetTickCount();
			break;
		default:
			break;
		}

		m_eBossPrevState[CENTER_HEAD] = m_eBossCurState[CENTER_HEAD];
	}
}

void CBossMonster::RightHeadMotion()
{
	if (m_eBossCurState[RIGHT_HEAD] != m_eBossPrevState[RIGHT_HEAD])
	{
		switch (m_eBossCurState[RIGHT_HEAD])
		{
		case BOSS_STATE::BOSS_IDLE:
			m_tRightHeadFrame.iStart = 0;
			m_tRightHeadFrame.iEnd = 9;
			m_tRightHeadFrame.iMotion = 0;
			m_tRightHeadFrame.dwSpeed = (DWORD)100.f;
			m_tRightHeadFrame.dwTime = GetTickCount();
			break;
			// 349 353
		case BOSS_STATE::BOSS_ATTACK:
			// 번개 쏘는 공격
			m_tRightHeadFrame.iStart = 0;
			m_tRightHeadFrame.iEnd = 17;
			m_tRightHeadFrame.iMotion = 0;
			m_tRightHeadFrame.dwSpeed = (DWORD)110.f;
			m_tRightHeadFrame.dwTime = GetTickCount();
			break;
		default:
			break;
		}

		m_eBossPrevState[RIGHT_HEAD] = m_eBossCurState[RIGHT_HEAD];
	}
}

void CBossMonster::LeftHeadMotion()
{
	if (m_eBossCurState[LEFT_HEAD] != m_eBossPrevState[LEFT_HEAD])
	{
		switch (m_eBossCurState[LEFT_HEAD])
		{
		case BOSS_STATE::BOSS_IDLE:
			m_tLeftHeadFrame.iStart = 0;
			m_tLeftHeadFrame.iEnd = 9;
			m_tLeftHeadFrame.iMotion = 0;
			m_tLeftHeadFrame.dwSpeed = (DWORD)120.f;
			m_tLeftHeadFrame.dwTime = GetTickCount();
			break;

		case BOSS_STATE::BOSS_ATTACK:
			// 
			m_tLeftHeadFrame.iStart = 0;
			m_tLeftHeadFrame.iEnd = 14;
			m_tLeftHeadFrame.iMotion = 0;
			m_tLeftHeadFrame.dwSpeed = (DWORD)110.f;
			m_tLeftHeadFrame.dwTime = GetTickCount();
			break;
		default:
			break;
		}

		m_eBossPrevState[LEFT_HEAD] = m_eBossCurState[LEFT_HEAD];
	}
}

void CBossMonster::LeftBodyMotion()
{
	if (m_eBossCurState[LEFT_BODY] != m_eBossPrevState[LEFT_BODY])
	{
		switch (m_eBossCurState[LEFT_BODY])
		{
		case BOSS_STATE::BOSS_IDLE:
			m_tLeftBodyFrame.iStart = 0;
			m_tLeftBodyFrame.iEnd = 6;
			m_tLeftBodyFrame.iMotion = 0;
			m_tLeftBodyFrame.dwSpeed = (DWORD)120.f;
			m_tLeftBodyFrame.dwTime = GetTickCount();
			break;

		case BOSS_STATE::BOSS_ATTACK:
			m_tLeftBodyFrame.iStart = 0;
			m_tLeftBodyFrame.iEnd = 16;
			m_tLeftBodyFrame.iMotion = 0;
			m_tLeftBodyFrame.dwSpeed = (DWORD)110.f;
			m_tLeftBodyFrame.dwTime = GetTickCount();
			break;

		default:
			break;
		}

		m_eBossPrevState[LEFT_BODY] = m_eBossCurState[LEFT_BODY];
	}
}

void CBossMonster::RightBodyMotion()
{
	if (m_eBossCurState[RIGHT_BODY] != m_eBossPrevState[RIGHT_BODY])
	{
		switch (m_eBossCurState[RIGHT_BODY])
		{
		case BOSS_STATE::BOSS_IDLE:
			m_tRightBodyFrame.iStart = 0;
			m_tRightBodyFrame.iEnd = 6;
			m_tRightBodyFrame.iMotion = 0;
			m_tRightBodyFrame.dwSpeed = (DWORD)120.f;
			m_tRightBodyFrame.dwTime = GetTickCount();
			break;

		case BOSS_STATE::BOSS_ATTACK:
			m_tRightBodyFrame.iStart = 0;
			m_tRightBodyFrame.iEnd = 17;
			m_tRightBodyFrame.iMotion = 0;
			m_tRightBodyFrame.dwSpeed = (DWORD)110.f;
			m_tRightBodyFrame.dwTime = GetTickCount();
			break;
		default:
			break;
		}

		m_eBossPrevState[RIGHT_BODY] = m_eBossCurState[RIGHT_BODY];
	}
}

void CBossMonster::DownBodyMotion()
{
	if (m_eBossCurState[DOWN_BODY] != m_eBossPrevState[DOWN_BODY])
	{
		switch (m_eBossCurState[DOWN_BODY])
		{
		case BOSS_STATE::BOSS_IDLE:
			m_tDownBodyFrame.iStart = 0;
			m_tDownBodyFrame.iEnd = 3;
			m_tDownBodyFrame.iMotion = 0;
			m_tDownBodyFrame.dwSpeed = (DWORD)(DWORD)200.f;
			m_tDownBodyFrame.dwTime = GetTickCount();
			break;

		case BOSS_STATE::BOSS_ATTACK:
			m_tDownBodyFrame.iStart = 0;
			m_tDownBodyFrame.iEnd = 17;
			m_tDownBodyFrame.iMotion = 0;
			m_tDownBodyFrame.dwSpeed = (DWORD)120.f;
			m_tDownBodyFrame.dwTime = GetTickCount();
			break;

		default:
			break;
		}

		m_eBossPrevState[DOWN_BODY] = m_eBossCurState[DOWN_BODY];
	}
}

void CBossMonster::WingMotion()
{
	if (m_eBossCurState[WING] != m_eBossPrevState[WING])
	{
		switch (m_eBossCurState[WING])
		{
		case BOSS_STATE::BOSS_IDLE:
			m_tWingFrame.iStart = 0;
			m_tWingFrame.iEnd = 6;
			m_tWingFrame.iMotion = 0;
			m_tWingFrame.dwSpeed = (DWORD)200.f;
			m_tWingFrame.dwTime = GetTickCount();
			break;

		case BOSS_STATE::BOSS_ATTACK:

			break;

		default:
			break;
		}

		m_eBossPrevState[WING] = m_eBossCurState[WING];
	}
}

void CBossMonster::TailMotion()
{
	if (m_eBossCurState[TAIL] != m_eBossPrevState[TAIL])
	{
		switch (m_eBossCurState[TAIL])
		{
		case BOSS_STATE::BOSS_IDLE:
			m_tTailFrame.iStart = 0;
			m_tTailFrame.iEnd = 4;
			m_tTailFrame.iMotion = 0;
			m_tTailFrame.dwSpeed = (DWORD)160.f;
			m_tTailFrame.dwTime = GetTickCount();
			break;

		case BOSS_STATE::BOSS_ATTACK:
			m_tTailFrame.iStart = 0;
			m_tTailFrame.iEnd = 20;
			m_tTailFrame.iMotion = 0;
			m_tTailFrame.dwSpeed = (DWORD)90.f;
			m_tTailFrame.dwTime = GetTickCount();
			break;
			break;

		default:
			break;
		}

		m_eBossPrevState[TAIL] = m_eBossCurState[TAIL];
	}
}


void CBossMonster::CenterHeadFrame()
{
	// 가운데 머리
	if (m_tCenterHeadFrame.dwTime + m_tCenterHeadFrame.dwSpeed < GetTickCount())
	{
		++m_tCenterHeadFrame.iStart;
		m_tCenterHeadFrame.dwTime = GetTickCount();
	}

	if (m_tCenterHeadFrame.iStart >= m_tCenterHeadFrame.iEnd /*&& abs(m_tMonFrame.iStart - m_tMonFrame.iEnd) > 2*/)
	{
		m_tCenterHeadFrame.iStart = 0;
		
		if (m_eBossCurState[CENTER_HEAD])
			m_eBossCurState[CENTER_HEAD] = BOSS_IDLE;
	}
}

void CBossMonster::LeftHeadFrame()
{
	if (m_tLeftHeadFrame.dwTime + m_tLeftHeadFrame.dwSpeed < GetTickCount())
	{
		++m_tLeftHeadFrame.iStart;
		m_tLeftHeadFrame.dwTime = GetTickCount();
	}

	if (m_tLeftHeadFrame.iStart >= m_tLeftHeadFrame.iEnd /*&& abs(m_tMonFrame.iStart - m_tMonFrame.iEnd) > 2*/)
	{
		m_tLeftHeadFrame.iStart = 0;

		FRAME EffectFrame = { 0, 11, 0, (DWORD)130.f, GetTickCount() };
		m_vecEffectFrame[LEFT_HEAD].push_back(EffectFrame);
		//m_vecEffectFrame[LEFT_HEAD].clear();
		m_eEffectCurState[LEFT_HEAD] = CURSE_ON;
		m_bIsCurse = true;

		if (m_eBossCurState[LEFT_HEAD])
			m_eBossCurState[LEFT_HEAD] = BOSS_IDLE;
	}
}

void CBossMonster::RightHeadFrame()
{
	if (m_tRightHeadFrame.dwTime + m_tRightHeadFrame.dwSpeed < GetTickCount())
	{
		++m_tRightHeadFrame.iStart;
		m_tRightHeadFrame.dwTime = GetTickCount();
	}

	if (m_tRightHeadFrame.iStart >= m_tRightHeadFrame.iEnd /*&& abs(m_tMonFrame.iStart - m_tMonFrame.iEnd) > 2*/)
	{
		m_tRightHeadFrame.iStart = 0;

		FRAME EffectFrame = { 0, 10, 0, (DWORD)120.f, GetTickCount() };
		m_vecEffectFrame[RIGHT_HEAD].push_back(EffectFrame);
		m_eEffectCurState[RIGHT_HEAD] = LIGHTNING_ON;
		m_bIsLightning = true;

		if (m_eBossCurState[RIGHT_HEAD])
			m_eBossCurState[RIGHT_HEAD] = BOSS_IDLE;

	}
}

void CBossMonster::LeftBodyFrame()
{
	// 왼쪽 몸
	if (m_tLeftBodyFrame.dwTime + m_tLeftBodyFrame.dwSpeed < GetTickCount())
	{
		++m_tLeftBodyFrame.iStart;
		m_tLeftBodyFrame.dwTime = GetTickCount();
	}

	if (m_tLeftBodyFrame.iStart >= m_tLeftBodyFrame.iEnd /*&& abs(m_tMonFrame.iStart - m_tMonFrame.iEnd) > 2*/)
	{
		m_tLeftBodyFrame.iStart = 0;
		
		if (m_eBossCurState[LEFT_BODY])
			m_eBossCurState[LEFT_BODY] = BOSS_IDLE;
	}
}

void CBossMonster::RightBodyFrame()
{
	// 오른쪽 몸
	if (m_tRightBodyFrame.dwTime + m_tRightBodyFrame.dwSpeed < GetTickCount())
	{
		++m_tRightBodyFrame.iStart;
		m_tRightBodyFrame.dwTime = GetTickCount();
	}

	if (m_tRightBodyFrame.iStart >= m_tRightBodyFrame.iEnd /*&& abs(m_tMonFrame.iStart - m_tMonFrame.iEnd) > 2*/)
	{
		m_tRightBodyFrame.iStart = 0;

		FRAME EffectFrame = { 0, 11, 0, (DWORD)130.f, GetTickCount() };
		m_vecEffectFrame[RIGHT_BODY].push_back(EffectFrame);
		m_eEffectCurState[RIGHT_BODY] = BLACKMETEO_ON;

		if (m_eBossCurState[RIGHT_BODY])
		{
			 m_eEffectCurState[RIGHT_BODY] = BLACKMETEO_ON;
			 m_eBossCurState[RIGHT_BODY] = BOSS_IDLE;
		}
	}
}

void CBossMonster::DownBodyFrame()
{
	// 아래 몸통
	if (m_tDownBodyFrame.dwTime + m_tDownBodyFrame.dwSpeed < GetTickCount())
	{
		++m_tDownBodyFrame.iStart;
		m_tDownBodyFrame.dwTime = GetTickCount();
	}

	if (m_tDownBodyFrame.iStart >= m_tDownBodyFrame.iEnd /*&& abs(m_tMonFrame.iStart - m_tMonFrame.iEnd) > 2*/)
	{
		m_tDownBodyFrame.iStart = 0;
	
		if (m_eBossCurState[DOWN_BODY])
			m_eBossCurState[DOWN_BODY] = BOSS_IDLE;

	}
}

void CBossMonster::WingFrame()
{
	// 날개
	if (m_tWingFrame.dwTime + m_tWingFrame.dwSpeed < GetTickCount())
	{
		++m_tWingFrame.iStart;
		m_tWingFrame.dwTime = GetTickCount();
	}

	if (m_tWingFrame.iStart >= m_tWingFrame.iEnd /*&& abs(m_tMonFrame.iStart - m_tMonFrame.iEnd) > 2*/)
	{
		m_tWingFrame.iStart = 0;

		if (m_eBossCurState[WING])
			m_eBossCurState[WING] = BOSS_IDLE;
	}
}

void CBossMonster::TailFrame()
{
	// 꼬리
	if (m_tTailFrame.dwTime + m_tTailFrame.dwSpeed < GetTickCount())
	{
		++m_tTailFrame.iStart;
		m_tTailFrame.dwTime = GetTickCount();
	}

	if (m_tTailFrame.iStart >= m_tTailFrame.iEnd /*&& abs(m_tMonFrame.iStart - m_tMonFrame.iEnd) > 2*/)
	{
		m_tTailFrame.iStart = 0;

		if (m_eBossCurState[TAIL])
			m_eBossCurState[TAIL] = BOSS_IDLE;
	}
}

void CBossMonster::BossEffectFrame()
{
	
	if (!m_vecEffectFrame[RIGHT_BODY].empty())
	{
		if (m_vecEffectFrame[RIGHT_BODY].front().dwTime + m_vecEffectFrame[RIGHT_BODY].front().dwSpeed < GetTickCount())
		{
			++m_vecEffectFrame[RIGHT_BODY].front().iStart;
			++m_vecEffectFrame[RIGHT_BODY].front().dwTime = GetTickCount();
		}

		if (m_vecEffectFrame[RIGHT_BODY].front().iStart >= m_vecEffectFrame[RIGHT_BODY].front().iEnd)
		{
			m_vecEffectFrame[RIGHT_BODY].front().iStart = 0;
			m_vecEffectFrame[RIGHT_BODY].clear();
			m_eEffectCurState[RIGHT_BODY] = EFFECT_STATE_OFF;
			m_bIsTarGetOn = false;
		}
	}

	if (!m_vecEffectFrame[RIGHT_HEAD].empty())
	{
		if (m_vecEffectFrame[RIGHT_HEAD].front().dwTime + m_vecEffectFrame[RIGHT_HEAD].front().dwSpeed < GetTickCount())
		{
			++m_vecEffectFrame[RIGHT_HEAD].front().iStart;
			++m_vecEffectFrame[RIGHT_HEAD].front().dwTime = GetTickCount();
		}

		if (m_vecEffectFrame[RIGHT_HEAD].front().iStart >= m_vecEffectFrame[RIGHT_HEAD].front().iEnd)
		{
			m_vecEffectFrame[RIGHT_HEAD].front().iStart = 0;
			m_vecEffectFrame[RIGHT_HEAD].clear();
			m_bIsLightning = false;
			m_eEffectCurState[RIGHT_HEAD] = EFFECT_STATE_OFF;
		}
	}

	if (!m_vecEffectFrame[LEFT_HEAD].empty())
	{
		if (m_vecEffectFrame[LEFT_HEAD].front().dwTime + m_vecEffectFrame[LEFT_HEAD].front().dwSpeed < GetTickCount())
		{
			++m_vecEffectFrame[LEFT_HEAD].front().iStart;
			++m_vecEffectFrame[LEFT_HEAD].front().dwTime = GetTickCount();
		}

		if (m_vecEffectFrame[LEFT_HEAD].front().iStart >= m_vecEffectFrame[LEFT_HEAD].front().iEnd)
		{
			m_vecEffectFrame[LEFT_HEAD].front().iStart = 0;
			m_vecEffectFrame[LEFT_HEAD].clear();
			m_bIsCurse = false;
			m_eEffectCurState[LEFT_HEAD] = EFFECT_STATE_OFF;
		}
	}
}

// CenterHead 9개