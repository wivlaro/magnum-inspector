#include "GtkObjectFrame.h"

namespace MagnumInspector {
	

GtkObjectFrame::GtkObjectFrame()
:	box(Gtk::ORIENTATION_VERTICAL)
{
	add(box);
	childPopulator.setContainer(&box);
	show_all();
}

GtkObjectFrame::~GtkObjectFrame()
{

}


}