#include "pch.h"
#include "CollisionMgr.h"

#include "CCore.h"
#include "CObject.h"
#include "CLine.h"
#include "CPlayer.h"
#include "CScrollMgr.h"
#include "CPotal.h"
#include "CSceneMgr.h"
#include "CInputMgr.h"

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::CollisionRect(list<CObject*> _Dest, list<CObject*> _Src)
{
	RECT rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &(Dest->GetRect()), &(Src->GetRect())))
			{
				Dest->SetState(OBJ_STATE::DISABLE);
				Src->SetState(OBJ_STATE::DISABLE);
			}
		}
	}
}


//플레이어와 사각형의 충돌 >
void CCollisionMgr::CollisionRect_Map(CObject* _lhs, vector<RECT*> _rhs)
{
	RECT rc{};

	bool bCheckColl = false;
	for (auto& rect : _rhs)
	{
		if (CheckTop(_lhs, rect))
		{
			if (!static_cast<CPlayer*>(_lhs)->IsJump())
			{
				//_lhs->SetY(rect->top - _lhs->GetScale() * 0.5f); //충돌후 Y좌표보정
				if (_lhs->GetRect().bottom - 3 < rect->top)
				{
					_lhs->SetY(rect->top - _lhs->GetScale() * 0.5f);
					bCheckColl = true;
					static_cast<CPlayer*>(_lhs)->SetFloor(true);
				}
			}
		}
	}
	if (!bCheckColl)
		static_cast<CPlayer*>(_lhs)->SetFloor(false);
}

bool CCollisionMgr::CheckTop(CObject* _pPlayer, RECT* pRect)
{
	if (_pPlayer->GetRect().right > pRect->left && _pPlayer->GetRect().left < pRect->right)
	{
		if (_pPlayer->GetRect().bottom > pRect->top && pRect->top > _pPlayer->GetY())
		{
			return true;
		}
	}
	return false;
}

void CCollisionMgr::CollisionPotal(CObject* _pPlayer, CObject* _pPotal)
{
	if (RectTrigger(_pPlayer, _pPotal))
	{
		if (static_cast<CPlayer*>(_pPlayer)->IsUse())
		{
			CSceneMgr::GetInstance()->SetNext(true);
		}
	}
}

bool CCollisionMgr::RectTrigger(CObject* _pPlayer, CObject* _pPotal)
{
	RECT rc{};
	if (IntersectRect(&rc, &(_pPlayer->GetRect()), &(_pPotal->GetRect())))
	{
		return true;
	}
	
	return false;
}


void CCollisionMgr::CheckLR(CObject* _pPlayer, RECT* pRect)
{
	if (_pPlayer->GetRect().right > pRect->left)
		_pPlayer->SetX(pRect->left - _pPlayer->GetScale() * 0.5f);
	
	if(_pPlayer->GetRect().left > pRect->right)
		_pPlayer->SetX(pRect->right + _pPlayer->GetScale() * 0.5f);
}

//void CCollisionMgr::CollisionPlayerToRect(list<CObject*> _Dest, list<CObject*> _Src)
//{
//	RECT rc{};
//
//	for (auto& Dest : _Dest)
//	{
//		for (auto& Src : _Src)
//		{
//			if (IntersectRect(&rc, &(Dest->GetRect()), &(Src->GetRect())))
//			{
//				Dest->SetState(OBJ_STATE::DISABLE);
//				Src->SetState(OBJ_STATE::DISABLE);
//			}
//		}
//	}
//}

void CCollisionMgr::CollisionRope(CObject* _pPlayer, vector<LINE*> _vRope)
{
	for (auto& rope : _vRope)
	{

	}
}

void CCollisionMgr::CollisionSphere(list<CObject*> _Dest, list<CObject*> _Src)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			if (CheckSphere(Dest, Src))
			{
				Dest->SetState(OBJ_STATE::DISABLE);
				Src->SetState(OBJ_STATE::DISABLE);
			}
		}
	}
}

bool CCollisionMgr::CheckSphere(CObject* _pDest, CObject* _pSrc)
{
	float	fWidth = fabs(_pDest->GetX() - _pSrc->GetX());
	float	fHeight = fabs(_pDest->GetY() - _pSrc->GetY());
	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (_pDest->GetScale() + _pSrc->GetScale()) * 0.5f;

	return fRadius >= fDiagonal;
}