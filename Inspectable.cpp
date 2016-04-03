
#include "Inspectable.h"
#include "Inspector.h"

#if defined(__GNUG__)
#define HAS_RTTI
#elif defined(__has_feature)
#if __has_feature(cxx_rtti)
#define HAS_RTTI
#endif
#endif

#ifdef HAS_RTTI
#include <typeinfo>
#endif

namespace MagnumInspector {

std::string Inspectable::getName() const {
	std::string name = std::to_string(intptr_t(this));
#ifdef HAS_RTTI
	name = std::string(typeid(this).name()) + "@" + name;
#endif
	return name;
}
	
	
}