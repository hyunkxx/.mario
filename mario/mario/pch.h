#pragma once

#include "framework.h"
#include "define.h"

#include <Windows.h>
#include <cassert>
#include <cstring>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <ctime>
#include <cmath>

using std::wstring;
using std::string;
using std::vector;
using std::list;
using std::map;
using std::set;
using std::unordered_set;
using std::unordered_map;

/* 각종 typedef struct 정의 */
struct Vec2
{
	float x;
	float y;
public:
	Vec2() :x(0.f), y(0.f) {}
	Vec2(float _x, float _y) :x(_x), y(_y) {}
	Vec2(const POINT& _point) :x((float)_point.x), y((float)_point.y) {}
public:
	Vec2 operator+(const Vec2& _rhs) {	return Vec2(x+_rhs.x, y+_rhs.y); }
	Vec2 operator-(const Vec2& _rhs) {	return Vec2(x - _rhs.x, y - _rhs.y); }
	Vec2 operator*(const Vec2& _rhs) {	return Vec2(x * _rhs.x, y * _rhs.y); }
	Vec2 operator/(const Vec2& _rhs) {	return Vec2(x / _rhs.x, y / _rhs.y); }
	Vec2 operator*(float _value) { return Vec2(x * _value, y * _value); }
	Vec2 operator/(float _value) { return Vec2(x / _value, y / _value); }
};


struct Transform
{
	float fX;
	float fY;
	float fScale;
public:
	Transform() :fX(0.f), fY(0.f), fScale(0.f) {};
	Transform(float _x, float _y, float _scale)
		:fX(_x), fY(_y), fScale(_scale) {};
};

typedef struct tagLinePoint
{
	float fX;
	float fY;
public:
	tagLinePoint() { ZeroMemory(this, sizeof(tagLinePoint)); }
	tagLinePoint(float _x, float _y) : fX(_x), fY(_y) {}
	tagLinePoint(POINT point) { fX = (float)point.x;	fY = (float)point.y; }
}MYPOINT;

typedef	struct tagLine
{
	MYPOINT	tLPoint;
	MYPOINT	tRPoint;

	tagLine(void) { ZeroMemory(this, sizeof(tagLine)); }
	tagLine(MYPOINT& tLeft, MYPOINT& tRight) : tLPoint(tLeft), tRPoint(tRight) {}
}LINE;

typedef struct tagKeyState
{
	KEY_STATE m_eState;
	bool m_bPrevPressed;

	tagKeyState() :m_eState(KEY_STATE::NONE), m_bPrevPressed(false) {}
}KeyState;


class CDeleteObj
{
public:
	template<typename T>
	void operator()(T& Temp)
	{
		if (Temp)
		{
			delete Temp;
			Temp = nullptr;
		}
	}
};

class CDeleteMap
{
public:
	template<typename T>
	void operator()(T& Pair)
	{
		if (Pair.second)
		{
			delete Pair.second;
			Pair.second = nullptr;
		}
	}
};


typedef struct tagInfo
{
	float		fX;
	float		fY;
	float		fCX;
	float		fCY;
}MON_INFO;

typedef struct tagFrame
{
	int		iStart;		// 몇 번 인덱스부터 출력할 것인가
	int		iEnd;		// 몇 번 인덱스까지 출력할 것인가
	int		iMotion;	// 몇 번 모션을 출력할 것인가
	DWORD	dwSpeed;	// 어떤 속도로 애니메이션을 재생할 것인가
	DWORD	dwTime;		// 시간 값에 따른 애니메이션 재생 속도 제어용

}FRAME;

class CTagFinder
{
public:
	CTagFinder(const TCHAR* pKey) : m_pKey(pKey) {	}
public:
	template<typename T>
	bool operator()(T& Pair)
	{
		if (!lstrcmp(m_pKey, Pair.first))
			return true;

		return false;
	}
private:
	const TCHAR* m_pKey;
};

typedef struct tMapSize
{
	float m_iWidth;
	float m_iHeight;
}MapSize;

#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif
#endif