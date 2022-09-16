#include "pch.h"
#include "CCamera.h"
#include "CObject.h"

CCamera* CCamera::pInstance;

CCamera::CCamera()
	: m_pTarget(nullptr)
{
	m_fLookAt.x = WIDTH * 0.5f;
	m_fLookAt.y = HEIGHT * 0.5f;
}

CCamera::~CCamera()
{
}

void CCamera::Update()
{
	if (!m_pTarget || m_pTarget->GetState() == OBJ_STATE::DISABLE)
		return;
	
	//�� �����Ӹ��� ī�޶� ��ġ�� Ÿ����ġ�� �̵�
	m_fLookAt.x = m_pTarget->GetX();
	m_fLookAt.y = m_pTarget->GetY();
}

//������Ʈ�� �����ġ(������ ��ġ) ���
Vec2 CCamera::CalcOffset(float _x, float _y)
{
	//�ٸ� ������Ʈ�� ī�޶� ������ ����
	m_fOffset.x = _x - WIDTH * 0.5f;
	m_fOffset.y = _y - HEIGHT * 0.5f;

	Vec2 vRenderPos;
	vRenderPos.x = _x - m_fOffset.x;
	vRenderPos.y = _y - m_fOffset.y;
	return vRenderPos;
}