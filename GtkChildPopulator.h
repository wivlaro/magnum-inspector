#pragma once

#include <gtkmm/container.h>

namespace MagnumInspector {

class GtkChildPopulator
{
public:
	
	GtkChildPopulator(Gtk::Container* container_in = nullptr);
	void reset();
	void setContainer(Gtk::Container* container);

	template<typename ChildWidget>
	ChildWidget& ensureChild() {
		ChildWidget* widget = nullptr;
		if (childIndex < childrenIterating.size()) {
			auto child = childrenIterating[childIndex];
			//TODO possibly we should compare G_OBJECT_TYPE(child->gobj()) and ChildWidget::get_type();
			widget = dynamic_cast<ChildWidget*>(child);
			if (!widget) {
				while (childIndex < childrenIterating.size()) {
					container->remove(*childrenIterating[childIndex++]);
				}
				childrenIterating.clear();
			}
			else {
				childIndex++;
			}
		}
		if (!widget) {
			widget = Gtk::manage(new ChildWidget());
			container->add(*widget);
			widget->show();
		}
		return *widget;
	}
    void pruneRemaining();
	
private:
	Gtk::Container* container;
	std::vector<Gtk::Widget*> childrenIterating;
	size_t childIndex;
};

}