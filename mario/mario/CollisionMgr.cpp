#include "pch.h"
#include "CollisionMgr.h"

#include "CCore.h"
#include "CObject.h"
#include "CLine.h"
#include "CPlayer.h"
#include "CScrollMgr.h"

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

	for (auto& rect : _rhs)
	{
		//충돌했을 경우는?
		//if (IntersectRect(&rc, &(_lhs->GetRect()),rect))
		if (CheckTop(_lhs, rect))
		{
			if ((_lhs->GetRect().bottom) + CScrollMgr::GetInst()->GetScrollY(), rect->top + CScrollMgr::GetInst()->GetScrollY())
			{
				_lhs->SetY(rect->top - _lhs->GetScale() * 0.5f);
				static_cast<CPlayer*>(_lhs)->gravity(false);
				static_cast<CPlayer*>(_lhs)->SetGround(true);
			}
			else
			{
				static_cast<CPlayer*>(_lhs)->gravity(true);
				static_cast<CPlayer*>(_lhs)->SetGround(false);
			}
		}
	}
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