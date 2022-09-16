#pragma once

#include "CScene.h"

class CStageEdit : public CScene
{
public:
	explicit CStageEdit(wstring _szName);
	virtual ~CStageEdit();
	CStageEdit(const CStageEdit& rhs) = delete;
	CStageEdit(CStageEdit&& rhs) = delete;
	CStageEdit& operator=(const CStageEdit& rhs) = delete;
public:
	virtual void Enter() override;
	virtual void Exit() override;
	virtual void Update(float _fDeltaTime) override;
	virtual void Render(HDC _hdc) override;
private:
	int m_iMouseCount;
	POINT m_mousePos;
	bool m_bDraw;
};


