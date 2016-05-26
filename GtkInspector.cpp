
#include "GtkInspector.h"

#include <gtkmm/paned.h>
#include <gtkmm/frame.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/grid.h>
#include <iostream>

#include "InspectorNode.h"


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
		auto ptr = child.get_value(columns.pointer);
		if (ptr) {
			ptr->reset();
		}
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
		auto weakRefPointer = selectedIt->get_value(columns.pointer);
		if (weakRefPointer) {
			if (auto details = weakRefPointer->lock()) {
				setupDetails(details.get());
			}
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

void GtkInspector::setupDetails(InspectorNode* node)
{
	childPopulator.setContainer(detailsPane);
	childPopulator.reset();
	auto detailNode = this->detailNode.lock();
	if (detailNode != node->shared_from_this()) {
		childPopulator.pruneRemaining();
		this->detailNode = node->shared_from_this();
	}
	if (node) {
		editable("Node", *node);
	}
	else {
		for (auto& child : detailsPane->get_children()) {
			detailsPane->remove(*child);
		}
	}
	childPopulator.pruneRemaining();
// 	detailsPane->show_all();
}

void GtkInspector::setRoot(InspectorNode* node)
{
	if (node) {
		updateChildren(*node, treeStore->children());
	}
	else {
		treeStore->clear();
	}
}

void GtkInspector::updateChildren(InspectorNode& node, const Gtk::TreeNodeChildren& dstChildren)
{
	auto dstIt = dstChildren.begin();
	static std::vector<InspectorNode*> children;
	node.getChildren(children);
	for (auto srcChild : children) {
		if (dstIt == dstChildren.end()) {
			dstIt = treeStore->append(dstChildren);
			dstIt->set_value(columns.pointer, std::weak_ptr<InspectorNode>());
		}
		updateNode(*srcChild, *dstIt);
		++dstIt;
	}
	while (dstIt != dstChildren.end()) {
		dstIt = treeStore->erase(dstIt);
	}
	children.clear();
}

Glib::ustring GtkInspector::getNodeName(InspectorNode& node)
{
	std::string name;
	auto entity = dynamic_cast<Inspectable*>(&node);
	if (entity) {
		name = entity->getName();
	}
	if (name.empty()) {
		name = std::to_string(intptr_t(&node));
	}
	return name;
}


void GtkInspector::updateNode(InspectorNode& node, const Gtk::TreeRow& row)
{
	auto weakRefPointer = row.get_value(columns.pointer);
	auto shouldUpdate = updateNamesToggle->get_active() || !weakRefPointer || weakRefPointer->lock() != node.shared_from_this();
	if (shouldUpdate) {
		row.set_value(columns.name, getNodeName(node));
		row.set_value(columns.pointer, new std::weak_ptr<InspectorNode>(node.shared_from_this()));
	}
	auto detailNode = this->detailNode.lock();
	if (detailNode == node.shared_from_this()) {
		setupDetails(&node);
	}
	
	updateChildren(node, row.children());
}



bool GtkInspector::update(InspectorNode* node)
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