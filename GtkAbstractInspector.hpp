#pragma once 

#include <typeinfo>
#include "GtkAbstractInspector.h"
#include "GtkObjectFrame.h"
#include "Inspectable.h"
#include "GtkAbstractInspector.hpp"


namespace MagnumInspector {
	

template<typename WidgetType, typename ValueType>
inline void ensure_range(WidgetType& w, ValueType min, ValueType max) {
	ValueType currentMin,currentMax;
	w.get_range(currentMin, currentMax);
	if (currentMin != min || currentMax != max) {
// 		std::cout << "set_range\n";
		w.set_range(min, max);
	}
}
template<typename WidgetType, typename ValueType>
inline void ensure_increments(WidgetType& w, ValueType a, ValueType b) {
	ValueType ca,cb;
	w.get_increments(ca, cb);
	if (ca != a || cb != b) {
// 		std::cout << "set_incrementse\n";
		w.set_increments(a, b);
	}
}
	
template<typename WidgetType, typename ValueType>
inline void ensure_digits(WidgetType& w, ValueType v) {
	if (w.get_digits() != v) {
// 		std::cout << "set_digits\n";
		w.set_digits(v);
	}
}
	
template<typename WidgetType, typename ValueType>
inline void ensure_width_chars(WidgetType& w, ValueType v) {
	if (w.get_width_chars() != v) {
// 		std::cout << "set_width_chars\n";
		w.set_width_chars(v);
	}
}
	
template<typename WidgetType, typename ValueType>
inline void ensure_value(WidgetType& w, ValueType v) {
	if (ValueType(w.get_value()) != v) {
// 		std::cout << "set_value " << w.get_value() << "!=" << v << "\n";
		w.set_value(v);
	}
}
	
template<typename WidgetType, typename ValueType>
inline void ensure_text(WidgetType& w, ValueType v) {
	if (w.get_text() != v) {
// 		std::cout << "set_text “" << w.get_text() << "” != “" << v << "”\n";
		w.set_text(v);
	}
}
	
template<typename WidgetType, typename ValueType>
inline void ensure_active(WidgetType& w, ValueType v) {
	if (w.get_active() != v) {
// 		std::cout << "set_active\n";
		w.set_active(v);
	}
}
	
template<typename T>
inline std::string getNameAndType(T& object) {
	auto inspectable = dynamic_cast<Inspectable*>(&object);
	std::ostringstream name;
	if (inspectable) {
		name << inspectable->getName();
	}
	else {
		name << std::hex << intptr_t(&object) << " (" << Inspector::demangle(typeid(object).name()) << ")";
	}
	return name.str();
}

inline void GtkAbstractInspector::editable(const char* name, Inspectable* i) {
	if (!i) return;
	auto& frame = childPopulator.ensureChild<GtkObjectFrame>();
	frame.childPopulator.reset();
	std::string label = i->getName() + " (" + demangle(typeid(*i).name()) + ")";
	if (name && strlen(name)) label = std::string(name) + ": " + label;
	if (frame.get_label() != label) {
		frame.set_label(label);
	}
	i->onInspect(frame);
	frame.childPopulator.pruneRemaining();
}

inline void GtkAbstractInspector::readonly(const char* name, Inspectable* i) {
	if (!i) return;
	auto& frame = childPopulator.ensureChild<GtkObjectFrame>();
	frame.childPopulator.reset();
	std::string label = i->getName() + " (" + demangle(typeid(*i).name()) + ")";
	if (name && strlen(name)) label = std::string(name) + ": " + label;
	if (frame.get_label() != label) {
		frame.set_label(label);
	}
	i->onInspect(frame);
	frame.childPopulator.pruneRemaining();
}

template<typename ValueType>
inline void GtkAbstractInspector::readonlyInteger(const char* name, const ValueType& i)
{
	auto& field = addField<Gtk::Label>(name);
	ensure_text(field, std::to_string(i));
}

template<typename ValueType>
inline void GtkAbstractInspector::editableInteger(const char* name, ValueType& i)
{
	auto& field = addField<Gtk::SpinButton>(name);
	ensure_range(field, double(std::numeric_limits<ValueType>().lowest()), double(std::numeric_limits<ValueType>().max()));
	ensure_digits(field, 0u);
	ensure_increments(field, 1.0, 10.0);
	if (!field.has_focus()) ensure_value(field, i);
	field.signal_value_changed().connect([&] {
		i = ValueType(field.get_value());
	});
}

}