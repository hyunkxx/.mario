#pragma once

struct tClipSize
{
	int width;
	int height;
public:
	tClipSize() : width(0), height(0) {}
	tClipSize(int _x, int _y) :width(_x), height(_y) {}
};

struct Clip
{
	HDC image;
	tClipSize size;

};

class CAnimClip
{
public:
	CAnimClip(class CPlayer* _pOwner);
	virtual ~CAnimClip();
	CAnimClip(const CAnimClip& _rhs) = delete;
	CAnimClip& operator=(const CAnimClip& _rhs) = delete;
	CAnimClip(CAnimClip&& _rhs) = delete;
	CAnimClip& operator=(CAnimClip&& _rhs) = delete;
public:
	void AddClip(HDC _hDC, tClipSize _size);
	void Play(HDC _hdc);
	void Play(HDC _hdc,float _fAnimSpeed);
	void SetAnimSpeed(float _value) { m_fAnimSpeed = _value; }
private:
	bool animTick(float _fAnimSpeed);
private:
	vector<Clip> m_vecAnim;
	int m_iCurFrame;
	float m_fAnimSpeed;
	ULONGLONG begin;
	class CPlayer* m_pOwner;
};

