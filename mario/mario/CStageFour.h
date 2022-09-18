#pragma once

#include "CScene.h"

class CStageFour : public CScene
{
public:
	explicit CStageFour(wstring _szName);
	virtual ~CStageFour();
	CStageFour(const CStageFour& rhs) = delete;
	CStageFour(CStageFour&& rhs) = delete;
	CStageFour& operator=(const CStageFour& rhs) = delete;
public:
	void Enter() override;
	void Exit() override;
	void Update(float _fDeltaTime) override;
	void Render(HDC _hDC) override;
private:
	void mapRender(HDC _hdc);
	void objectRedner(HDC _hdc);
private:
	HDC m_hSubDC;
	vector<LINE*>* m_vCopyLines;
	vector<RECT*>* m_vCopyRects;
};

