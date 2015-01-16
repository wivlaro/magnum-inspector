
#include <gtkmm/spinbutton.h>
#include <gtkmm/checkbutton.h>
#include "GtkAbstractInspector.h"
#include "GtkInspectionField.h"
#include "GtkMatrixWidget.h"
#include "GtkObjectFrame.h"
#include "GtkAbstractInspector.hpp"
#include <numeric>

namespace MagnumInspector {

void GtkAbstractInspector::readonly(const char* name, const float* f, uint n, uint m)
{
	auto& field = addField<GtkMatrixWidget>(name);
	field.update<Gtk::SpinButton,const float>(f, n, m, [](Gtk::SpinButton& field, const float& value) {
		field.set_range(std::numeric_limits<float>().lowest(),std::numeric_limits<float>().max());
		field.set_increments(0.01, 1.0);
		field.set_digits(5);
		field.set_width_chars(10);
		field.set_value(value);
	});
}

void GtkAbstractInspector::editable(const char* name, float* f, uint n, uint m)
{
	auto& field = addField<GtkMatrixWidget>(name);
	field.update<Gtk::SpinButton,float>(f, n, m, [](Gtk::SpinButton& field, float& value) {
		field.set_range(std::numeric_limits<float>().lowest(),std::numeric_limits<float>().max());
		field.set_width_chars(10);
		if (!field.has_focus()) field.set_value(value);
		field.signal_value_changed().connect([&] {
			value = float(field.get_value());
		});
	});
}


void GtkAbstractInspector::readonly(const char* name, const int& i)
{
	auto& field = addField<Gtk::SpinButton>(name);
	field.set_value(i);
}

void GtkAbstractInspector::editable(const char* name, int& i)
{
	auto& field = addField<Gtk::SpinButton>(name);
	field.set_digits(0);
	field.set_increments(1, 10);
	if (!field.has_focus()) field.set_value(i);
	field.signal_value_changed().connect([&] {
		i = field.get_value_as_int();
	});
}

void GtkAbstractInspector::readonly(const char* name, const std::string& s)
{
	auto& field = addField<Gtk::Entry>(name);
	field.set_text(s);
}

void GtkAbstractInspector::editable(const char* name, std::string& s)
{
	auto& field = addField<Gtk::Entry>(name);
	if (!field.has_focus()) field.set_text(s);
	field.signal_changed().connect([&] {
		s = field.get_text();
	});
}

void GtkAbstractInspector::readonly(const char* name, const float& f)
{
	auto& field = addField<Gtk::SpinButton>(name);
	field.set_value(f);
}

void GtkAbstractInspector::editable(const char* name, float& f)
{
	auto& field = addField<Gtk::SpinButton>(name);
	if (!field.has_focus()) field.set_value(f);
	field.signal_value_changed().connect([&] {
		f = float(field.get_value());
	});
}

	
void GtkAbstractInspector::readonly(const char* name, bool f)
{
	auto& field = addField<Gtk::CheckButton>(name);
	field.set_active(f);
}

void GtkAbstractInspector::editable(const char* name, bool& f)
{
	auto& field = addField<Gtk::CheckButton>(name);
	if (!field.has_focus()) field.set_active(f);
	field.signal_toggled().connect([&] {
		f = float(field.get_active());
	});
}

	

}