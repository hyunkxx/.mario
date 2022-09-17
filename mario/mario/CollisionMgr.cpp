#include "pch.h"
#include "CollisionMgr.h"

#include "CCore.h"
#include "CObject.h"
#include "CLine.h"
#include "CPlayer.h"

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

void CCollisionMgr::CollisionLine(list<CObject*> _lhs, vector<CLine*> _rhs)
{
	
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

bool CCollisionMgr::CheckSphere(CObject * _pDest, CObject * _pSrc)
{
	float	fWidth = fabs(_pDest->GetX()- _pSrc->GetX());
	float	fHeight = fabs(_pDest->GetY() - _pSrc->GetY());
	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float	fRadius = (_pDest->GetScale() + _pSrc->GetScale()) * 0.5f;

	return fRadius >= fDiagonal;
}