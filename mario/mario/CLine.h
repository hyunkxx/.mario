#pragma once

#include "CObject.h"

class CLine : public CObject
{
public:
	CLine();
	CLine(MYPOINT& _lPoint, MYPOINT& _rPoint);
	CLine(LINE& _line);
	virtual ~CLine();
public:
	const LINE& GetLine() const { return m_tLine; }
public:
	void Render(HDC _hdc) override;
private:
	LINE m_tLine;
};

