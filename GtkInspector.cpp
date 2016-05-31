
#include "GtkInspector.h"

#include <gtkmm/paned.h>
#include <gtkmm/frame.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/grid.h>
#include <iostream>

#include "Inspectable.h"


namespace MagnumInspector {

GtkInspector::GtkInspector()
:	refreshNextFrame(true)
,	gtkMain(nullptr)
,	window(nullptr)
,	refreshButton(nullptr)
,	autoRefreshToggle(nullptr)
,	detailNode()
,	detailNodeLabel(nullptr)
{
	std::cout << "GtkInspector::GtkInspector\n";

}

GtkInspector::~GtkInspector()
{
	std::cout << "GtkInspector::~GtkInspector\n";

	clearWeakPointers(treeStore->children());
	
	delete window;
	delete gtkMain;
}
	
void GtkInspector::clearWeakPointers(const Gtk::TreeNodeChildren& children) {
	for (auto child : children) {
//		auto ptr = child.get_value(columns.pointer);
//		if (ptr) {
//			ptr->reset();
//		}
		clearWeakPointers(child->children());
	}
}

void GtkInspector::init()
{
	std::cout << "GtkInspector::init\n";
	gtkMain = new Gtk::Main();
	window = new Gtk::Window();
	window->set_default_size(640, 480);
	auto mainBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
	
	auto buttonBar = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL));
	mainBox->add(*buttonBar);
	
	refreshButton = new Gtk::Button("Refresh");
	refreshButton->signal_clicked().connect([&] {
		refreshNextFrame = true;
	});
	autoRefreshToggle = new Gtk::ToggleButton("Auto refresh");
	updateNamesToggle = new Gtk::ToggleButton("Names update");
	
	buttonBar->add(*refreshButton);
	buttonBar->add(*autoRefreshToggle);
	
	treeView = new Gtk::TreeView();
	treeStore = Gtk::TreeStore::create(columns);
	treeView->set_model(treeStore);
	treeView->append_column("Name", columns.name);
	treeView->get_selection()->signal_changed().connect([&] {
		auto selectedIt = treeView->get_selection()->get_selected();
		auto node = selectedIt->get_value(columns.pointer);
		if (node.get()) {
			setupDetails(node.get());
		}
	});
	
	detailsPane = new Gtk::Box(Gtk::ORIENTATION_VERTICAL);
	
	auto paneSplit = Gtk::manage(new Gtk::Paned(Gtk::ORIENTATION_HORIZONTAL));
	auto scrollPane = Gtk::manage(new Gtk::ScrolledWindow());
	scrollPane->add(*treeView);
	paneSplit->add1(*scrollPane);
	scrollPane = Gtk::manage(new Gtk::ScrolledWindow());
	scrollPane->add(*detailsPane);
	paneSplit->add2(*scrollPane);
	paneSplit->set_position(100);
	
	mainBox->pack_end(*paneSplit);
	
	window->add(*mainBox);
	window->show_all();
}

void GtkInspector::setupDetails(Inspectable *node)
{
	childPopulator.setContainer(detailsPane);
	childPopulator.reset();
	if (detailNode != node) {
		childPopulator.pruneRemaining();
		if (detailNode) {
			detailNode->removeDestroyListener(this);
		}
		detailNode = node;
		if (detailNode) {
			detailNode->addDestroyListener(this);
		}
	}
	if (node) {
		inspectAsMain("Node", *node);
	}
	else {
		for (auto& child : detailsPane->get_children()) {
			detailsPane->remove(*child);
		}
	}
	childPopulator.pruneRemaining();
}

void GtkInspector::onDestroy(Inspectable *node) {
	if (node == detailNode) {
		detailNode = nullptr;
	}
}

void GtkInspector::setRoot(Inspectable* node)
{
	if (node) {
		updateChildren(*node, treeStore->children());
	}
	else {
		treeStore->clear();
	}
}

void GtkInspector::updateChildren(Inspectable& node, const Gtk::TreeNodeChildren& dstChildren)
{
	auto dstIt = dstChildren.begin();
	std::vector<Inspectable*> children;
	node.getChildren(children);
	for (auto srcChild : children) {
		if (dstIt == dstChildren.end()) {
			dstIt = treeStore->append(dstChildren);
			dstIt->set_value(columns.pointer, InspectableWeakRef(&node));
		}
		updateNode(*srcChild, *dstIt);
		++dstIt;
	}
	while (dstIt != dstChildren.end()) {
		dstIt = treeStore->erase(dstIt);
	}
}

Glib::ustring GtkInspector::getNodeName(Inspectable& entity)
{
	std::string name = entity.getName();
	if (name.empty()) {
		name = std::to_string(intptr_t(&entity));
	}
	return name;
}


void GtkInspector::updateNode(Inspectable& node, const Gtk::TreeRow& row)
{
	auto weakRef = row.get_value(columns.pointer);
	auto shouldUpdate = updateNamesToggle->get_active() || weakRef.get() != &node;
	if (shouldUpdate) {
		row.set_value(columns.name, getNodeName(node));
		row.set_value(columns.pointer, InspectableWeakRef(&node));
	}
	if (detailNode == &node) {
		setupDetails(detailNode);
	}
	
	updateChildren(node, row.children());
}



bool GtkInspector::update(Inspectable* node)
{
// 	std::cout << "GtkInspector::update\n";
	if (autoRefreshToggle->get_active() || refreshNextFrame) {
		setRoot(node);
		refreshNextFrame = false;
	}
// 	bool finished = false;
	while (gtkMain->events_pending()) {
// 		finished = !
		gtkMain->iteration(false);
// 		std::cout << "GtkInspector::update iteration finished="<<finished<<"\n";
	}
// 	return finished;
	return false;
}


}

