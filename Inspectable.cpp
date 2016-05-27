
#include "Inspectable.h"
#include "Inspector.h"
#include <sstream>
#include <iomanip>

namespace MagnumInspector {

Inspectable::~Inspectable() {
	for (auto listener : onDestroy) {
		listener->onDestroy(this);
	}
}
	
std::string Inspectable::getDemangledNameFor(const void *ptr, const char *typenam)	{
	std::ostringstream name;
	name << std::hex << intptr_t(ptr) << " (" << Inspector::demangle(typenam) << ")";
	return name.str();
}

void Inspectable::addDestroyListener(InspectableDestroyListener *listener) {
	onDestroy.push_front(listener);
}

void Inspectable::removeDestroyListener(InspectableDestroyListener *listener) {
	onDestroy.remove(listener);
}


}