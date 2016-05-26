
#include "Inspectable.h"
#include "Inspector.h"
#include <sstream>
#include <iomanip>

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

Inspectable::~Inspectable() {
	for (auto listener : onDestroy) {
		listener->onDestroy(this);
	}
}

std::string Inspectable::getName() const {

	std::ostringstream name;
	name << std::hex << intptr_t(this) << " (" << Inspector::demangle(typeid(*this).name()) << ")";
	return name.str();
}

void Inspectable::addDestroyListener(InspectableDestroyListener *listener) {
	onDestroy.push_front(listener);
}

void Inspectable::removeDestroyListener(InspectableDestroyListener *listener) {
	onDestroy.remove(listener);
}


}