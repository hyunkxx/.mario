#pragma once
#include "CObject.h"

template<typename T>
class AbstractFactory
{
public:
	static CObject* Shot(float _fX, float _fY)
	{
		CObject* pObject = new T;
		pObject->Initalize();
		pObject->SetX(_fX);
		pObject->SetY(_fY);
		return pObject;
	}

};