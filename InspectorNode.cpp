//
// Created by bill on 25/05/16.
//

#include <ios>
#include <sstream>
#include "InspectorNode.h"
#include "Inspector.h"

namespace MagnumInspector {
void InspectorNode::getName(std::string &nameResult) {
	std::ostringstream name;
	name << std::hex << intptr_t(this) << " (" << Inspector::demangle(typeid(*this).name()) << ")";
	nameResult = name.str();
}
}
