#pragma once

#include <gtkmm/frame.h>
#include "GtkAbstractInspector.h"

namespace MagnumInspector {

class GtkObjectFrame : public Gtk::Frame, public GtkAbstractInspector
{
public:
	
	GtkObjectFrame()
	:	box(Gtk::ORIENTATION_VERTICAL)
	{
		add(box);
		childPopulator.setContainer(&box);
	}
	
    virtual ~GtkObjectFrame() { }
	
 	
private:
    Gtk::Box box;
};

}