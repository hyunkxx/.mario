#include "pch.h"
#include "CLineMgr.h"

#include "CCore.h"
#include "CScene.h"
#include "CSceneMgr.h"
#include "CObject.h"
#include "CLine.h"
#include "CInputMgr.h"

CLineMgr* CLineMgr::pInstance;


//ĸ��ȭ �ڻ쳪���� ����Ʈ �� + ���θŴ��� 
CLineMgr::CLineMgr()
	: m_ptLeft(0.f, 0.f)
	, m_ptRight(0.f, 0.f)
	, m_bFinish(false)
	, m_curMousePos({})
{
}

CLineMgr::~CLineMgr()
{
	for (int i = 0; i < (UINT)SCENE_STATE::STAGE_COUNT ; i++)
	{
		for (int j = 0; j < m_vecLines[i].size(); j++)
			delete m_vecLines[j][i];
	}
}

void CLineMgr::SetBeginPoint(float _x, float _y, SCENE_STATE _eType)
{
	if (m_vecLines[(UINT)_eType].size() == 0)
	{
		m_ptLeft.fX = _x;
		m_ptLeft.fY = _y;
	}
	else
	{
		m_ptLeft.fX = m_ptRight.fX;
		m_ptLeft.fY = m_ptRight.fY;
	}
}

void CLineMgr::SetEndPoint(float _x, float _y)
{
	m_ptRight.fX = _x;
	m_ptRight.fY = _y;
	m_bFinish = true;
}

void CLineMgr::SaveLine(SCENE_STATE _eType)
{
	HANDLE hFileLine = nullptr;

	switch (_eType)
	{
	case SCENE_STATE::STAGE_1:
		hFileLine = CreateFile(L"../data/stage_1_line.dat", GENERIC_WRITE , 0 , nullptr , CREATE_ALWAYS , FILE_ATTRIBUTE_NORMAL , nullptr);
		break;
	case SCENE_STATE::STAGE_2:
		hFileLine = CreateFile(L"../data/stage_2_line.dat", GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		break;
	case SCENE_STATE::STAGE_3:
		hFileLine = CreateFile(L"../data/stage_3_line.dat", GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		break;
	case SCENE_STATE::STAGE_4:
		hFileLine = CreateFile(L"../data/stage_4_line.dat", GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		break;
	case SCENE_STATE::STAGE_END:
		hFileLine = CreateFile(L"../data/stage_end_line.dat", GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
		break;
	}

	if (hFileLine == INVALID_HANDLE_VALUE)
		return;

	vector<CLine*> pLine = m_vecLines[(UINT)_eType];
	DWORD dwByte = 0;
	
	for (auto* line : pLine)
	{
		if(line != nullptr)
			WriteFile(hFileLine, &(line->GetLine()), sizeof(CLine), &dwByte, nullptr);
	}

	CloseHandle(hFileLine);

	MessageBox(CCore::GetInstance()->GetWindowHandle(), L"�������� ����", L"Result",MB_OK);
}

void CLineMgr::LoadLine(SCENE_STATE _eType)
{
	CLine line;
	HANDLE hFileLine = nullptr;

	switch (_eType)
	{
	case SCENE_STATE::STAGE_1:
		hFileLine = CreateFile(L"../data/stage_1_line.dat", GENERIC_READ, 0, nullptr, OPEN_EXISTING, OPEN_EXISTING, nullptr);
		break;
	case SCENE_STATE::STAGE_2:
		hFileLine = CreateFile(L"../data/stage_2_line.dat", GENERIC_READ, 0, nullptr, OPEN_EXISTING, OPEN_EXISTING, nullptr);
		break;
	case SCENE_STATE::STAGE_3:
		hFileLine = CreateFile(L"../data/stage_3_line.dat", GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		break;
	case SCENE_STATE::STAGE_4:
		hFileLine = CreateFile(L"../data/stage_4_line.dat", GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		break;
	case SCENE_STATE::STAGE_END:
		hFileLine = CreateFile(L"../data/stage_end_line.dat", GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
		break;
	}
	hFileLine = CreateFile(L"../data/stage_1_line.dat", GENERIC_READ, 0, nullptr, OPEN_EXISTING, OPEN_EXISTING, nullptr);
	if (INVALID_HANDLE_VALUE == hFileLine)
		return;

	DWORD		dwByte = 0;
	LINE		lines{};

	while (true)
	{
		ReadFile(hFileLine, &lines, sizeof(CLine), &dwByte, nullptr);
		if (dwByte == 0)
			break;

		m_vecLines[(UINT)_eType].push_back(new CLine(lines.tLPoint, lines.tRPoint));
	}
	CloseHandle(hFileLine);

	MessageBox(CCore::GetInstance()->GetWindowHandle(), L"���Ϸε� ����", L"Result", MB_OK);
}

void CLineMgr::PushObjectList()
{
	//�Լ��� ȣ��� ���������� ������ ���Ŵ��� ������Ʈ�� Ǫ����
	size_t index = CSceneMgr::GetInstance()->GetCurIndex();

	for (auto iter = m_vecLines[(UINT)index].begin(); iter != m_vecLines[(UINT)index].end(); ++iter)
	{
		CSceneMgr::GetInstance()->GetCurScene()->AddObject(*iter, OBJ_TYPE::TERRAIN);
	}
}
