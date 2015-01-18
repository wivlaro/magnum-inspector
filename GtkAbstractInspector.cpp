
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
	field.update<Gtk::Label,const float>(f, n, m, [](Gtk::Label& field, const float& value) {
		ensure_text(field, std::to_string(value));
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

void GtkAbstractInspector::readonly(const char* name, const std::string& s)
{
	auto& field = addField<Gtk::Label>(name);
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
	auto& field = addField<Gtk::Label>(name);
	ensure_text(field, std::to_string(f));
}

void GtkAbstractInspector::editable(const char* name, float& f)
{
	auto& field = addField<Gtk::SpinButton>(name);
	ensure_range(field, double(std::numeric_limits<float>().lowest()), double(std::numeric_limits<float>().max()));
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