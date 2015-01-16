#pragma once

#include <gtkmm/container.h>

namespace MagnumInspector {

class GtkChildPopulator
{
public:
	
	GtkChildPopulator(Gtk::Container* container_in = nullptr)
	:	container(container_in)
	{
		if (container) reset();
	}
	
	void reset() {
		childIndex = 0;
		childrenIterating = std::move(container->get_children());
	}
	
	void setContainer(Gtk::Container* container)
	{
		this->container = container;
	}

	template<typename ChildWidget>
	ChildWidget& ensureChild() {
		ChildWidget* widget = nullptr;
		if (childIndex < childrenIterating.size()) {
			auto child = childrenIterating[childIndex];
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
		}
		return *widget;
	}
	
private:
	Gtk::Container* container;
	std::vector<Gtk::Widget*> childrenIterating;
	size_t childIndex;
};

}