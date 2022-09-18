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

	static void	CollisionLine(list<CObject*> _lhs, vector<CLine*> _rhs);
	//static bool	CheckLine(CObject* _lhs, CLine* _rhs);

	static void	CollisionSphere(list<CObject*> _Dest, list<CObject*> _Src);
	static bool	CheckSphere(CObject* _pDest, CObject* _pSrc);
};

