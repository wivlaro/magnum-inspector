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
class InspectorNode;

class GtkInspector	: public GtkAbstractInspector
{
public:
    GtkInspector();
	~GtkInspector();
	
	void init();
	
	bool update(InspectorNode* node);
	
	bool refreshNextFrame;
	
protected:
    Glib::ustring getNodeName(InspectorNode& node);
	
private:
		
	class MyModelColumns : public Gtk::TreeModel::ColumnRecord
	{
	public:
		Gtk::TreeModelColumn<Glib::ustring> name;
		Gtk::TreeModelColumn<std::weak_ptr<InspectorNode>> pointer;
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
	std::weak_ptr<InspectorNode> detailNode;
    Gtk::Label* detailNodeLabel;
	
	void updateChildren(InspectorNode& node, const Gtk::TreeNodeChildren& children);
	void updateNode(InspectorNode& node, const Gtk::TreeRow& row);
	
	void setRoot(InspectorNode* node);
    void setupDetails(InspectorNode* node);
    void updateDetailNode();
    void addInspectableFields(Gtk::Box* box, MagnumInspector::Inspectable* arg2);
		
};


}
