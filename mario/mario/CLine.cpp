#include "pch.h"
#include "CLine.h"


CLine::CLine()
	: m_tLine()
{
}

CLine::CLine(MYPOINT& _lPoint, MYPOINT& _rPoint)
	: CObject()
	, m_tLine(_lPoint,_rPoint)
{

}

CLine::CLine(LINE& _line)
	: CObject()
	, m_tLine(_line)
{
	memcpy(&m_tLine, &_line, sizeof(LINE));
}

CLine::~CLine()
{

}
void CLine::Render(HDC _hdc)
{
	MoveToEx(_hdc, (int)m_tLine.tLPoint.fX, (int)m_tLine.tLPoint.fY, nullptr);
	LineTo(_hdc, (int)m_tLine.tRPoint.fX, (int)m_tLine.tRPoint.fY);
}

