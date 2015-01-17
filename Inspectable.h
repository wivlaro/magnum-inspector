#pragma once

#include "Inspector.h"
#include <string>

namespace MagnumInspector {

class Inspectable
{
public:
	virtual std::string getName() const;
	
	virtual void onInspect(Inspector& inspector) = 0;
};

}