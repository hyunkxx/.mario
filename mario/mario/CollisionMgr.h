#pragma once

class CObject;
class CLine;

class CCollisionMgr
{
public:
	CCollisionMgr();
	~CCollisionMgr();

public:
	static void	CollisionRect(list<CObject*> _Dest, list<CObject*> _Src);
	static void CollisionRect_Map(CObject* _lhs, vector<RECT*> _rhs);
	
	static bool CheckTop(CObject* _lhs, RECT* _rhs);

	static void CollisionPotal(CObject* _pPlayer, CObject* _pPotal);
	static bool RectTrigger(CObject* _pPlayer, CObject* _pPotal);

	static void CheckLR(CObject* _pPlayer, RECT* pRect);
	static void	CollisionRope(CObject* _pPlayer, vector<LINE*> _vRope);
	//static bool	CheckLine(CObject* _lhs, CLine* _rhs);

	static void	CollisionSphere(list<CObject*> _Dest, list<CObject*> _Src);
	static bool	CheckSphere(CObject* _pDest, CObject* _pSrc);
};

