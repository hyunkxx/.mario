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