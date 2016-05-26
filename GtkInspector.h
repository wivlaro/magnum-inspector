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
	
class GtkInspector	: public GtkAbstractInspector, public Inspectable::DestroyListener
{
public:
    GtkInspector();
	~GtkInspector();
	
	void init();
	
	bool update(Inspectable* node);
	
	bool refreshNextFrame;
	
protected:
    Glib::ustring getNodeName(Inspectable& node);

	void onDestroy(Inspectable* ) override;
	
private:

	class InspectableWeakRef : InspectableDestroyListener {
	public:
		InspectableWeakRef() {
			target = nullptr;
		}
		InspectableWeakRef(Inspectable* newTarget) {
			justSet(newTarget);
		}

		InspectableWeakRef(const InspectableWeakRef& newTarget) {
			if (newTarget) {
				justSet(newTarget.target);
			}
			else {
				target = nullptr;
			}
		}
		virtual ~InspectableWeakRef() {
			unlisten();
		}

		void onDestroy(Inspectable* destroying) {
			assert(target == destroying);
			target = nullptr;
		}

		Inspectable* get() {
			return target;
		}

		void clear() {
			unlisten();
			target = nullptr;
		}

		void set(Inspectable* newTarget) {
			unlisten();
			justSet(newTarget);
		}
		bool operator!() const {
			return target == nullptr;
		}
		operator bool() const {
			return target != nullptr;
		}
	private:
		Inspectable* target;

		void unlisten() {
			if (target) {
				target->removeDestroyListener(this);
			}
		}

		void justSet(Inspectable *newTarget) {
			target = newTarget;
			target->addDestroyListener(this);
		}

	};
		
	class MyModelColumns : public Gtk::TreeModel::ColumnRecord
	{
	public:
		Gtk::TreeModelColumn<Glib::ustring> name;
		Gtk::TreeModelColumn<InspectableWeakRef> pointer;
		MyModelColumns() {
			add(name);
			add(pointer);
		}
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
	Inspectable* detailNode;
    Gtk::Label* detailNodeLabel;
	
	void updateChildren(Inspectable& node, const Gtk::TreeNodeChildren& children);
	void updateNode(Inspectable& node, const Gtk::TreeRow& row);
	
	void setRoot(Inspectable* node);
    void setupDetails(Inspectable* node);
    void updateDetailNode();
    void addInspectableFields(Gtk::Box* box, MagnumInspector::Inspectable* arg2);
	void clearWeakPointers(const Gtk::TreeNodeChildren&);
	void unsetDetailNode(Inspectable* node);
};


}
