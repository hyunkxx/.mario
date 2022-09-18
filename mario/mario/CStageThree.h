#pragma once

#include "CScene.h"

class CStageThree : public CScene
{
public:
	explicit CStageThree(wstring _szName);
	virtual ~CStageThree();
	CStageThree(const CStageThree& rhs) = delete;
	CStageThree(CStageThree&& rhs) = delete;
	CStageThree& operator=(const CStageThree& rhs) = delete;
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

