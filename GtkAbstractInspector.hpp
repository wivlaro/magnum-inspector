#pragma once 

#include <typeinfo>
#include "GtkAbstractInspector.h"
#include "GtkObjectFrame.h"
#include "Inspectable.h"
#include "GtkAbstractInspector.hpp"

#ifdef __GNUG__
#include <cstdlib>
#include <memory>
#include <cxxabi.h>

std::string demangle(const char* name) {

    int status = -4; // some arbitrary value to eliminate the compiler warning

    // enable c++11 by passing the flag -std=c++11 to g++
    std::unique_ptr<char, void(*)(void*)> res {
        abi::__cxa_demangle(name, NULL, NULL, &status),
        std::free
    };

    return (status==0) ? res.get() : name ;
}

#else

// does nothing if not g++
std::string demangle(const char* name) {
    return name;
}

#endif


namespace MagnumInspector {

template<uint Dimensions, typename ValueType>
inline void GtkAbstractInspector::editableObject(Magnum::SceneGraph::AbstractObject<Dimensions, ValueType>& object) {
	typedef Magnum::SceneGraph::AbstractObject<Dimensions, ValueType> ObjectType;
	{
		auto& frame = childPopulator.ensureChild<GtkObjectFrame>();
		frame.set_label(std::to_string(intptr_t(&object)) + " (" + demangle(typeid(object).name()) + ")");
		frame.resetChildPopulator();
		frame.Inspector::readonly("Matrix", object.transformationMatrix());
		if (auto* inspectable = dynamic_cast<Inspectable*>(&object)) {
			inspectable->onInspect(frame);
		}
	}
	for (auto feature = object.features().first(); feature; feature = feature->nextFeature()) {
		if (dynamic_cast<ObjectType*>(feature) == &object) continue;
		auto& frame = childPopulator.ensureChild<GtkObjectFrame>();
		frame.set_label(std::to_string(intptr_t(feature)) + " (" + demangle(typeid(*feature).name()) + ")");
		frame.resetChildPopulator();
		if (auto* inspectable = dynamic_cast<Inspectable*>(feature)) {
			inspectable->onInspect(frame);
		}
	}
}
template<uint Dimensions, typename ValueType>
inline void GtkAbstractInspector::readonlyObject(Magnum::SceneGraph::AbstractObject<Dimensions, ValueType>& object) {
	typedef Magnum::SceneGraph::AbstractObject<Dimensions, ValueType> ObjectType;
	{
		auto& frame = childPopulator.ensureChild<GtkObjectFrame>();
		frame.set_label(std::to_string(intptr_t(&object)) + " (" + demangle(typeid(object).name()) + ")");
		frame.resetChildPopulator();
		frame.Inspector::readonly("Matrix", object.transformationMatrix());
		if (auto* inspectable = dynamic_cast<Inspectable*>(&object)) {
			inspectable->onInspect(frame);
		}
	}
	for (auto feature = object.features().first(); feature; feature = feature->nextFeature()) {
		if (dynamic_cast<ObjectType*>(feature) == &object) continue;
		auto& frame = childPopulator.ensureChild<GtkObjectFrame>();
		frame.set_label(std::to_string(intptr_t(feature)) + " (" + demangle(typeid(*feature).name()) + ")");
		frame.resetChildPopulator();
		if (auto* inspectable = dynamic_cast<Inspectable*>(feature)) {
			inspectable->onInspect(frame);
		}
	}
}

template<uint Dimensions, typename ValueType>
inline void GtkAbstractInspector::editableFeature(Magnum::SceneGraph::AbstractFeature<Dimensions, ValueType>& feature) {
	auto& frame = childPopulator.ensureChild<GtkObjectFrame>();
	frame.set_label(std::to_string(intptr_t(&feature)) + " (" + demangle(typeid(&feature).name()) + ")");
	frame.resetChildPopulator();
	if (auto* inspectable = dynamic_cast<Inspectable*>(&feature)) {
		inspectable->onInspect(frame);
	}
}

template<uint Dimensions, typename ValueType>
inline void GtkAbstractInspector::readonlyFeature(Magnum::SceneGraph::AbstractFeature<Dimensions, ValueType>& feature) {
	auto& frame = childPopulator.ensureChild<GtkObjectFrame>();
	frame.set_label(std::to_string(intptr_t(&feature)) + " (" + demangle(typeid(&feature).name()) + ")");
	frame.resetChildPopulator();
	if (auto* inspectable = dynamic_cast<Inspectable*>(&feature)) {
		inspectable->onInspect(frame);
	}
}

inline void GtkAbstractInspector::editable(Inspectable* i) {
	if (!i) return;
	auto& frame = childPopulator.ensureChild<GtkObjectFrame>();
	frame.resetChildPopulator();
	frame.set_label(i->getName());
	i->onInspect(frame);
}

inline void GtkAbstractInspector::readonly(Inspectable* i) {
	if (!i) return;
	auto& frame = childPopulator.ensureChild<GtkObjectFrame>();
	frame.resetChildPopulator();
	frame.set_label(i->getName());
	i->onInspect(frame);
}

}