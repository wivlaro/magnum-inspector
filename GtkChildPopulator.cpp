#include "GtkChildPopulator.h"

namespace MagnumInspector {
	

GtkChildPopulator::GtkChildPopulator(Gtk::Container* container_in)
:	container(container_in)
{
	if (container) reset();
}

void GtkChildPopulator::reset() {
	childIndex = 0;
	childrenIterating = std::move(container->get_children());
}

void GtkChildPopulator::setContainer(Gtk::Container* container)
{
	this->container = container;
}

void GtkChildPopulator::pruneRemaining()
{
	for (; childIndex < childrenIterating.size(); childIndex++) {
		container->remove(*childrenIterating[childIndex]);
	}
}


}