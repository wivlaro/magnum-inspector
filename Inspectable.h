#pragma once

#include "forwarddeclarations.h"
#include <string>

namespace MagnumInspector {

class Inspectable
{
public:
	virtual std::string getName() const;
	
	virtual void onInspect(Inspector& inspector) = 0;
};

}