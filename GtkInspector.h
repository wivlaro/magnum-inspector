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
#include <Magnum/SceneGraph/AbstractObject.h>

namespace MagnumInspector {
	
class GtkInspectorNode;
	
template<class SceneGraphObject>
class GtkInspector	: public GtkAbstractInspector
{
public:
    GtkInspector();
	~GtkInspector();
	
	void init();
	
	bool update(SceneGraphObject* node);
	
	bool refreshNextFrame;
	
protected:
    Glib::ustring getNodeName(SceneGraphObject& node);
	
private:
		
	class MyModelColumns : public Gtk::TreeModel::ColumnRecord
	{
	public:
		Gtk::TreeModelColumn<Glib::ustring> name;
		Gtk::TreeModelColumn<SceneGraphObject*> pointer;
		MyModelColumns() { add(name); add(pointer); }
	};

	MyModelColumns columns;
	
	Gtk::Main* gtkMain;
	Gtk::Window* window;
	
	Gtk::Button* refreshButton;
	Gtk::ToggleButton* autoRefreshToggle;
	Gtk::ToggleButton* updateNamesToggle;
	
	Gtk::TreeView* treeView;
	Glib::RefPtr<Gtk::TreeStore> treeStore;
    Gtk::Box* detailsPane;
	SceneGraphObject* detailNode;
    Gtk::Label* detailNodeLabel;
	
	void updateChildren(SceneGraphObject& node, const Gtk::TreeNodeChildren& children);
	void updateNode(SceneGraphObject& node, const Gtk::TreeRow& row);
	
	void setRoot(SceneGraphObject* node);
    void setupDetails(SceneGraphObject* node);
    void updateDetailNode();
    void addInspectableFields(Gtk::Box* box, MagnumInspector::Inspectable* arg2);
		
};


}
