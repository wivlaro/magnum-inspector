
#include "Inspectable.h"
#include "Inspector.h"


namespace MagnumInspector {

std::string Inspectable::getName() const {
	return std::to_string(intptr_t(this));
}
	
	
}