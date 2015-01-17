
#include <gtkmm/spinbutton.h>
#include <gtkmm/checkbutton.h>
#include "GtkAbstractInspector.h"
#include "GtkInspectionField.h"
#include "GtkMatrixWidget.h"
#include "GtkObjectFrame.h"
#include "GtkAbstractInspector.hpp"
#include <numeric>

namespace MagnumInspector {

template<typename WidgetType, typename ValueType>
inline void ensure_range(WidgetType& w, ValueType min, ValueType max) {
	ValueType currentMin,currentMax;
	w.get_range(currentMin, currentMax);
	if (currentMin != min || currentMax != max) {
		w.set_range(min, max);
	}
}
template<typename WidgetType, typename ValueType>
inline void ensure_increments(WidgetType& w, ValueType a, ValueType b) {
	ValueType ca,cb;
	w.get_increments(ca, cb);
	if (ca != a || cb != b) {
		w.set_increments(a, b);
	}
}
	
template<typename WidgetType, typename ValueType>
inline void ensure_digits(WidgetType& w, ValueType v) {
	if (w.get_digits() != v) w.set_digits(v);
}
	
template<typename WidgetType, typename ValueType>
inline void ensure_width_chars(WidgetType& w, ValueType v) {
	if (w.get_width_chars() != v) w.set_width_chars(v);
}
	
template<typename WidgetType, typename ValueType>
inline void ensure_value(WidgetType& w, ValueType v) {
	if (w.get_value() != v) w.set_value(v);
}
	
template<typename WidgetType, typename ValueType>
inline void ensure_text(WidgetType& w, ValueType v) {
	if (w.get_text() != v) w.set_text(v);
}
	
template<typename WidgetType, typename ValueType>
inline void ensure_active(WidgetType& w, ValueType v) {
	if (w.get_active() != v) w.set_active(v);
}
	
void GtkAbstractInspector::readonly(const char* name, const float* f, uint n, uint m)
{
	auto& field = addField<GtkMatrixWidget>(name);
	field.update<Gtk::SpinButton,const float>(f, n, m, [](Gtk::SpinButton& field, const float& value) {
		ensure_range(field, double(std::numeric_limits<float>().lowest()), double(std::numeric_limits<float>().max()));
		ensure_increments(field, 0.01, 1.0);
		ensure_digits(field, 5u);
		ensure_width_chars(field, 10);
		ensure_value(field, double(value));
	});
}

void GtkAbstractInspector::editable(const char* name, float* f, uint n, uint m)
{
	auto& field = addField<GtkMatrixWidget>(name);
	field.update<Gtk::SpinButton,float>(f, n, m, [](Gtk::SpinButton& field, float& value) {
		ensure_range(field, double(std::numeric_limits<float>().lowest()), double(std::numeric_limits<float>().max()));
		ensure_digits(field, 5u);
		ensure_width_chars(field, 10);
		if (!field.has_focus()) ensure_value(field, double(value));
		field.signal_value_changed().connect([&] {
			value = float(field.get_value());
		});
	});
}


void GtkAbstractInspector::readonly(const char* name, const int& i)
{
	auto& field = addField<Gtk::SpinButton>(name);
	ensure_value(field, double(i));
}

void GtkAbstractInspector::editable(const char* name, int& i)
{
	auto& field = addField<Gtk::SpinButton>(name);
	ensure_digits(field, 0u);
	ensure_increments(field, 1.0, 10.0);
	if (!field.has_focus()) ensure_value(field, double(i));
	field.signal_value_changed().connect([&] {
		i = field.get_value_as_int();
	});
}

void GtkAbstractInspector::readonly(const char* name, const std::string& s)
{
	auto& field = addField<Gtk::Entry>(name);
	ensure_text(field, s);
}

void GtkAbstractInspector::editable(const char* name, std::string& s)
{
	auto& field = addField<Gtk::Entry>(name);
	if (!field.has_focus()) ensure_text(field, s);
	field.signal_changed().connect([&] {
		s = field.get_text();
	});
}

void GtkAbstractInspector::readonly(const char* name, const float& f)
{
	auto& field = addField<Gtk::SpinButton>(name);
	ensure_value(field, double(f));
}

void GtkAbstractInspector::editable(const char* name, float& f)
{
	auto& field = addField<Gtk::SpinButton>(name);
	if (!field.has_focus()) ensure_value(field, double(f));
	field.signal_value_changed().connect([&] {
		f = float(field.get_value());
	});
}

	
void GtkAbstractInspector::readonly(const char* name, bool f)
{
	auto& field = addField<Gtk::CheckButton>(name);
	ensure_active(field, f);
}

void GtkAbstractInspector::editable(const char* name, bool& f)
{
	auto& field = addField<Gtk::CheckButton>(name);
	if (!field.has_focus()) ensure_active(field, f);
	field.signal_toggled().connect([&] {
		f = float(field.get_active());
	});
}

	

}