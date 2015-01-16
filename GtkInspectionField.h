#pragma once

#include <gtkmm/box.h>
#include <gtkmm/widget.h>
#include <gtkmm/label.h>

namespace MagnumInspector {

class GtkInspectionField : public Gtk::Box
{
public:
    GtkInspectionField()
	:	valueWidget(nullptr)
	{
		add(labelWidget);
	}
	
	Gtk::Label& getLabel() {
		return labelWidget;
	}

	template<typename ChildWidget>
	ChildWidget& ensureChild() {
		ChildWidget* widget = dynamic_cast<ChildWidget*>(valueWidget);
		if (!widget) {
			if (valueWidget) {
				remove(*valueWidget);
			}
			widget = Gtk::manage(new ChildWidget());
			add(*widget);
			valueWidget = widget;
		}
		return *widget;
	}
private:
	Gtk::Label labelWidget;
    Gtk::Widget* valueWidget;
};

}