#include "pch.h"
#include "CStageEdit.h"

#include "CCore.h"
#include "CInputMgr.h"
#include "CLineMgr.h"
#include "CLine.h"
#include "CMapEditor.h"

CStageEdit::CStageEdit(wstring _szName)
	: CScene(_szName)
	, m_iMouseCount(0)
{
	ZeroMemory(&m_mousePos, sizeof(POINT));
}

CStageEdit::~CStageEdit()
{
}

void CStageEdit::Enter()
{
	m_iMouseCount = 0;
}

void CStageEdit::Exit()
{
}

void CStageEdit::Update(float _fDeltaTime)
{
	CMapEditor::GetInst()->Update();
}

void CStageEdit::Render(HDC _hdc)
{
	CMapEditor::GetInst()->Render(_hdc);
}