#pragma once

#include "Inspector.h"
#include <string>

namespace MagInspect {

class Inspectable
{
public:
	virtual std::string getName() const { return std::to_string(intptr_t(this)); }
	
	virtual void onInspect(Inspector& inspector) = 0;
};

}