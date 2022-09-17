#pragma once

#include "CScene.h"

class CStageTwo : public CScene
{
public:
	explicit CStageTwo(wstring _szName);
	virtual ~CStageTwo();
	CStageTwo(const CStageTwo& rhs) = delete;
	CStageTwo(CStageTwo&& rhs) = delete;
	CStageTwo& operator=(const CStageTwo& rhs) = delete;
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

