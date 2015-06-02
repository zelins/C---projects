#pragma once
#include "StorageDevice.h"

template <class Type>
class OutputManager
{
public:
	virtual void operator <<(Type& obj) const = 0;
	virtual ~OutputManager() {}
};