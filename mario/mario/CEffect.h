#pragma once

#include "CObject.h"

enum class EffectType
{
	HIT,
	BOOST,
	BULLET,
	END
};

class CEffect : public CObject
{
public:
	CEffect(Transform _transform,float _fDuration, EffectType _eType);
	CEffect(float _xPos, float _yPos, float _fScale,float _fDuration, EffectType _eType);
	~CEffect();
public:
public:
	void Initalize() override;
	int  Update(float _fDeltaTiem) override;
	void Render(HDC _hdc) override;
public:
	void SetDutaion(float _duration);//지속시간
	void GetTargetXY(CObject& _pTarget);

	void SetEffect(float _duration);
	void ResetTimer();

	bool IsActive() { return m_bActive; }
	bool SetActive(bool _value) { return m_bActive = _value; }

	EffectType GetEffectType() { return m_eType; }
	void GetEffectType(EffectType _eValue) { m_eType = _eValue; }
	//void SetColorRGB(COLORREF* _colorArray, int _arrayLength)
	//{
	//	colorList = _colorArray;
	//	m_nColorLength = _arrayLength;
	//}
	//COLORREF* GetBaseParticleColor() { return _baseParticleColor; }
private:
	void HitEffect(HDC _hdc);
	void BoostEffect(HDC _hdc);
	void BulletSmoke(HDC _hdc);
public:
	EffectType m_eType;
	bool  m_bActive;
	float m_fDuraion;
	ULONGLONG m_beginTimer;

	/*  Unused values  */
	//CEffect* m_pInstance;
	//COLORREF* colorList;
	//int m_nColorLength;
	//COLORREF* _baseParticleColor; 
};