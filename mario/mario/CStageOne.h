#pragma once

#include "CScene.h"

class CStageOne : public CScene
{
public:
	explicit CStageOne(wstring _szName);
	virtual ~CStageOne();
	CStageOne(const CStageOne& rhs) = delete;
	CStageOne(CStageOne&& rhs) = delete;
	CStageOne& operator=(const CStageOne& rhs) = delete;
public:
	void Enter() override;
	void Exit() override;
	void Update(float _fDeltaTime) override;
	void Render(HDC _hDC) override;
private:
	HDC m_hSubDC;
	vector<LINE*>* m_vCopyLines;
	vector<RECT*>* m_vCopyRects;
};

