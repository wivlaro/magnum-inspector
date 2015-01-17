#pragma once 

#include <typeinfo>
#include "GtkAbstractInspector.h"
#include "GtkObjectFrame.h"
#include "Inspectable.h"
#include "GtkAbstractInspector.hpp"


namespace MagnumInspector {
	
	
template<typename T>
inline std::string getNameAndType(T& object) {
	auto inspectable = dynamic_cast<Inspectable*>(&object);
	std::string name;
	if (inspectable) {
		name = inspectable->getName();
	}
	else {
		name = std::to_string(intptr_t(&object));
	}
	return name + " (" + Inspector::demangle(typeid(object).name()) + ")";
}

template<uint Dimensions, typename ValueType>
inline void GtkAbstractInspector::editableObject(Magnum::SceneGraph::AbstractObject<Dimensions, ValueType>& object) {
	typedef Magnum::SceneGraph::AbstractObject<Dimensions, ValueType> ObjectType;
	{
		auto& frame = childPopulator.ensureChild<GtkObjectFrame>();
		frame.set_label(getNameAndType(object));
		frame.childPopulator.reset();
		frame.Inspector::readonly("Matrix", object.transformationMatrix());
		if (auto* inspectable = dynamic_cast<Inspectable*>(&object)) {
			inspectable->onInspect(frame);
		}
		frame.childPopulator.pruneRemaining();
	}
	for (auto feature = object.features().first(); feature; feature = feature->nextFeature()) {
		if (dynamic_cast<ObjectType*>(feature) == &object) continue;
		auto& frame = childPopulator.ensureChild<GtkObjectFrame>();
		frame.set_label(getNameAndType(*feature));
		frame.childPopulator.reset();
		if (auto* inspectable = dynamic_cast<Inspectable*>(feature)) {
			inspectable->onInspect(frame);
		}
		frame.childPopulator.pruneRemaining();
	}
}
template<uint Dimensions, typename ValueType>
inline void GtkAbstractInspector::readonlyObject(Magnum::SceneGraph::AbstractObject<Dimensions, ValueType>& object) {
	typedef Magnum::SceneGraph::AbstractObject<Dimensions, ValueType> ObjectType;
	{
		auto& frame = childPopulator.ensureChild<GtkObjectFrame>();
		frame.set_label(getNameAndType(object));
		frame.childPopulator.reset();
		frame.Inspector::readonly("Matrix", object.transformationMatrix());
		if (auto* inspectable = dynamic_cast<Inspectable*>(&object)) {
			inspectable->onInspect(frame);
		}
		frame.childPopulator.pruneRemaining();
	}
	for (auto feature = object.features().first(); feature; feature = feature->nextFeature()) {
		if (dynamic_cast<ObjectType*>(feature) == &object) continue;
		auto& frame = childPopulator.ensureChild<GtkObjectFrame>();
		frame.set_label(getNameAndType(*feature));
		frame.childPopulator.reset();
		if (auto* inspectable = dynamic_cast<Inspectable*>(feature)) {
			inspectable->onInspect(frame);
		}
		frame.childPopulator.pruneRemaining();
	}
}

template<uint Dimensions, typename ValueType>
inline void GtkAbstractInspector::editableFeature(Magnum::SceneGraph::AbstractFeature<Dimensions, ValueType>& feature) {
	auto& frame = childPopulator.ensureChild<GtkObjectFrame>();
	frame.set_label(getNameAndType(feature));
	frame.childPopulator.reset();
	if (auto* inspectable = dynamic_cast<Inspectable*>(&feature)) {
		inspectable->onInspect(frame);
	}
	frame.childPopulator.pruneRemaining();
}

template<uint Dimensions, typename ValueType>
inline void GtkAbstractInspector::readonlyFeature(Magnum::SceneGraph::AbstractFeature<Dimensions, ValueType>& feature) {
	auto& frame = childPopulator.ensureChild<GtkObjectFrame>();
	frame.set_label(getNameAndType(feature));
	frame.childPopulator.reset();
	if (auto* inspectable = dynamic_cast<Inspectable*>(&feature)) {
		inspectable->onInspect(frame);
	}
	frame.childPopulator.pruneRemaining();
}

inline void GtkAbstractInspector::editable(Inspectable* i) {
	if (!i) return;
	auto& frame = childPopulator.ensureChild<GtkObjectFrame>();
	frame.childPopulator.reset();
	frame.set_label(i->getName() + " (" + demangle(typeid(*i).name()) + ")");
	i->onInspect(frame);
	frame.childPopulator.pruneRemaining();
}

inline void GtkAbstractInspector::readonly(Inspectable* i) {
	if (!i) return;
	auto& frame = childPopulator.ensureChild<GtkObjectFrame>();
	frame.childPopulator.reset();
	frame.set_label(i->getName() + " (" + demangle(typeid(*i).name()) + ")");
	i->onInspect(frame);
	frame.childPopulator.pruneRemaining();
}

}