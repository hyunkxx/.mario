#include "pch.h"
#include "CEffect.h"

CEffect::CEffect(Transform _transform, float _fDuration,EffectType _eType)
	: CObject(_transform)
	, m_fDuraion(_fDuration)
	, m_bActive(false)
	, m_beginTimer(0)
	, m_eType(_eType)
{
}

CEffect::CEffect(float _xPos, float _yPos, float _fScale,float _fDuration,EffectType _eType)
	: CObject(_xPos,_yPos,_fScale)
	, m_fDuraion(_fDuration)
	, m_bActive(false)
	, m_beginTimer(0)
	, m_eType(_eType)
{
	SetEffect(_fDuration);
}

CEffect::~CEffect()
{
}

void CEffect::Initalize()
{
	srand((unsigned int)time(nullptr));
}

int CEffect::Update(float _fDeltaTiem)
{
	ResetTimer();

	return EVENT_SUCCEED;
}

void CEffect::Render(HDC _hdc)
{
	if (m_bActive == false)
		return;

	switch (m_eType)
	{
	case EffectType::HIT:
		HitEffect(_hdc);
		break;
	case EffectType::BOOST:
		BoostEffect(_hdc);
		break;
	case EffectType::END:
		break;
	}
}

//지속시간 세팅
void CEffect::SetDutaion(float _duration)
{
	m_fDuraion = _duration;
}

//매개변수로 받은 오브젝트의 좌표를 이펙트의 좌표로 지정
void CEffect::GetTargetXY(CObject& _pTarget)
{
	m_tTransform.fX = _pTarget.GetX();
	m_tTransform.fY = _pTarget.GetX();
}

void CEffect::SetEffect(float _duration)
{
	srand((unsigned int)time(nullptr));
	m_fDuraion = _duration;

	m_bActive = true;
	m_beginTimer = GetTickCount64();
}

void CEffect::ResetTimer()
{
	if (GetTickCount64() - m_beginTimer >= m_fDuraion)
	{
		m_bActive = false;
	}
}

void CEffect::HitEffect(HDC _hdc)
{
	HBRUSH myBrush;
	HBRUSH particleColor[4];

	//245,222,179 / 255,255,000 / 238 130 238

	particleColor[0] = (HBRUSH)CreateSolidBrush(RGB(245, 222, 179));
	particleColor[1] = (HBRUSH)CreateSolidBrush(RGB(255, 255, 000));
	particleColor[2] = (HBRUSH)CreateSolidBrush(RGB(238, 130, 238));
	particleColor[3] = (HBRUSH)CreateSolidBrush(RGB(255, 255, 255));

	myBrush = (HBRUSH)SelectObject(_hdc, particleColor[0]);

	for (int index = 0; index < 10; index++)
	{
		int randColor = rand() % 4;
		SelectObject(_hdc, particleColor[randColor]);
		Ellipse(_hdc
			, (int)(m_tTransform.fX - m_tTransform.fScale / 2 + rand() % 20)
			, (int)(m_tTransform.fY - m_tTransform.fScale / 2 + rand() % 20)
			, (int)(m_tTransform.fX + m_tTransform.fScale / 2 + rand() % 20)
			, (int)(m_tTransform.fY + m_tTransform.fScale / 2 + rand() % 20)
		);
	}
	SelectObject(_hdc, myBrush);
	for (auto& item : particleColor)
		DeleteObject(item);
}

void CEffect::BoostEffect(HDC _hdc)
{
	HBRUSH myBrush;
	HBRUSH particleColor[4];

	//255 0 0 red
	//255 255 0 yellow 
	//000 
	//30,144,255

	particleColor[0] = (HBRUSH)CreateSolidBrush(RGB(30, 144, 255));
	particleColor[1] = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	particleColor[2] = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	particleColor[3] = (HBRUSH)CreateSolidBrush(RGB(255, 255, 0));

	myBrush = (HBRUSH)SelectObject(_hdc, particleColor[0]);

	for (int index = 0; index < 10; index++)
	{
		int randColor = rand() % 4;
		SelectObject(_hdc, particleColor[randColor]);
		Ellipse(_hdc
			, (int)(m_tTransform.fX - m_tTransform.fScale / 2 + rand() %8)
			, (int)(m_tTransform.fY - m_tTransform.fScale / 2 + rand() %8)
			, (int)(m_tTransform.fX + m_tTransform.fScale / 2 + rand() %8)
			, (int)(m_tTransform.fY + m_tTransform.fScale / 2 + rand() %8)
		);
	}
	SelectObject(_hdc, myBrush);
	for (auto& item : particleColor)
		DeleteObject(item);
}