#pragma once

class CObject;
class CPlayer;

class CScene
{
public:
	explicit CScene(wstring _szName);
	virtual ~CScene();
	CScene(const CScene& rhs) = delete;
	CScene(CScene&& rhs) = delete;
	CScene& operator=(const CScene& rhs) = delete;
public:
	virtual void Enter() = 0;
	virtual void Exit() = 0;
public:
	virtual void Update(float _fDeltaTime) = 0;
	virtual void Render(HDC _hdc) = 0;
public:
	static size_t m_nPlayerCount;
public:
	CObject* GetPlayer() { return m_arrObject[(UINT)::OBJ_TYPE::PLAYER].front(); }
	void AddObject(CObject* _pObj, OBJ_TYPE _eType);
	void ClearObject();
	list<CObject*>* GetObjectList(OBJ_TYPE _eType);
protected:
	wstring m_szName;
	list<CObject*> m_arrObject[(UINT)OBJ_TYPE::END];
};

