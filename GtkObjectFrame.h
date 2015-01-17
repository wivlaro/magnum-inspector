#pragma once

#include <gtkmm/frame.h>
#include "GtkAbstractInspector.h"

namespace MagnumInspector {

class GtkObjectFrame : public Gtk::Frame, public GtkAbstractInspector
{
public:
	
	GtkObjectFrame();
	
    virtual ~GtkObjectFrame();
	
 	
private:
    Gtk::Box box;
};

}