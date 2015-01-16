#pragma once

#include <gtkmm/main.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/treeview.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/treestore.h>
#include <gtkmm/box.h>
#include <map>
#include <memory>
#include "Inspector.h"
#include "Inspectable.h"
#include "GtkAbstractInspector.h"

namespace MagInspect {

typedef Magnum::SceneGraph::Object<Magnum::SceneGraph::MatrixTransformation3D> Object3D;
typedef Magnum::SceneGraph::Object<Magnum::SceneGraph::MatrixTransformation2D> Object2D;
	
class GtkInspectorNode;
	
class GtkInspector	: public GtkAbstractInspector
{
public:
    GtkInspector();
	~GtkInspector();
	
	void init();
	
	bool update(Object3D* node);
	
	bool refreshNextFrame;
	
protected:
    Glib::ustring getNodeName(Object3D& node);
	
private:
	Gtk::Main* gtkMain;
	Gtk::Window* window;
	
	Gtk::Button* refreshButton;
	Gtk::ToggleButton* autoRefreshToggle;
	Gtk::ToggleButton* updateNamesToggle;
	
	Gtk::TreeView* treeView;
	Glib::RefPtr<Gtk::TreeStore> treeStore;
    Gtk::Box* detailsPane;
	Object3D* detailNode;
    Gtk::Label* detailNodeLabel;
	
	void updateChildren(Object3D& node, const Gtk::TreeNodeChildren& children);
	void updateNode(Object3D& node, const Gtk::TreeRow& row);
	
	void setRoot(Object3D* node);
    void setupDetails(Object3D* node);
    void updateDetailNode();
    void addInspectableFields(Gtk::Box* box, MagInspect::Inspectable* arg2);
		
};


}
