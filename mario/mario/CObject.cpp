#include "pch.h"
#include "CObject.h"

#include "CCore.h"

CObject::CObject()
	: m_tTransform({})
	, m_eObjState(OBJ_STATE::DEFAULT)
	, m_rcRect({})
{
	CCore::GetInstance()->m_nObjCount++;
}

CObject::CObject(float _x, float _y, float _scale)
	: m_tTransform(_x, _y, _scale)
	, m_eObjState(OBJ_STATE::DEFAULT)
	, m_rcRect({})
{
	CCore::GetInstance()->m_nObjCount++;
}

CObject::CObject(Transform _transform)
	: m_tTransform(_transform)
	, m_eObjState(OBJ_STATE::DEFAULT)
	, m_rcRect({})
{
	CCore::GetInstance()->m_nObjCount++;
}

CObject::~CObject()
{
	CCore::GetInstance()->m_nObjCount--;
}

void CObject::Initalize()
{
}

int CObject::Update(float _fDeltaTime)
{
	//상속받은쪽에서 CObject::Update()를 Update문의 맨처음 실행 해줘야함
	setRect();

	

	return EVENT_SUCCEED;
}

void CObject::LateUpdate(float _fDeltaTime)
{

}

void CObject::Render(HDC _hdc)
{
	//테스트용 코드 실제 렌더링은 상속받은 쪽에서 구현
	//Rectangle(_hdc
	//	, m_rcRect.left 
	//	, m_rcRect.top 
	//	, m_rcRect.right 
	//	, m_rcRect.bottom );
}

void CObject::Release()
{

}

//오브젝트의 원점(중심)으로부터 스케일의 절반만큼 RECT를 생성
void CObject::setRect()
{
	m_rcRect.left    = (LONG)(m_tTransform.fX - (m_tTransform.fScale * 0.5f));
	m_rcRect.top     = (LONG)(m_tTransform.fY - (m_tTransform.fScale * 0.5f));
	m_rcRect.right   = (LONG)(m_tTransform.fX + (m_tTransform.fScale * 0.5f));
	m_rcRect.bottom  = (LONG)(m_tTransform.fY + (m_tTransform.fScale * 0.5f));
}
