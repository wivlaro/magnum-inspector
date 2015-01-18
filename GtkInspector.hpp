
#pragma once

#include "GtkInspector.h"

#include <gtkmm/box.h>
#include <gtkmm/paned.h>
#include <gtkmm/frame.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/entry.h>
#include <gtkmm/grid.h>
#include <Magnum/SceneGraph/Scene.h>
#include <iostream>
#include <sstream>

#include "Inspectable.h"
#include <Magnum/Magnum.h>
#include <Magnum/SceneGraph/Object.h>
#include <Magnum/SceneGraph/Scene.h>
#include <Magnum/SceneGraph/MatrixTransformation3D.h>
#include "GtkChildPopulator.h"


namespace MagnumInspector {

template <class SceneGraphObject>
GtkInspector<SceneGraphObject>::GtkInspector()
:	refreshNextFrame(true)
,	gtkMain(nullptr)
,	window(nullptr)
,	refreshButton(nullptr)
,	autoRefreshToggle(nullptr)
,	detailNode(nullptr)
,	detailNodeLabel(nullptr)
{
	std::cout << "GtkInspector::GtkInspector\n";

}

template <class SceneGraphObject>
GtkInspector<SceneGraphObject>::~GtkInspector()
{
	std::cout << "GtkInspector::~GtkInspector\n";
	
	delete window;
	delete gtkMain;
}

template <class SceneGraphObject>
void GtkInspector<SceneGraphObject>::init()
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
		setupDetails(selectedIt->get_value(columns.pointer));
	});
	
	detailsPane = new Gtk::Box(Gtk::ORIENTATION_VERTICAL);
	
	auto paneSplit = Gtk::manage(new Gtk::Paned(Gtk::ORIENTATION_HORIZONTAL));
	auto scrollPane = Gtk::manage(new Gtk::ScrolledWindow());
	scrollPane->add(*treeView);
	paneSplit->add1(*scrollPane);
	scrollPane = Gtk::manage(new Gtk::ScrolledWindow());
	scrollPane->add(*detailsPane);
	paneSplit->add2(*scrollPane);
	
	mainBox->pack_end(*paneSplit);
	
	window->add(*mainBox);
	window->show_all();
}

template <class SceneGraphObject>
void GtkInspector<SceneGraphObject>::setupDetails(SceneGraphObject* node)
{
	
	childPopulator.setContainer(detailsPane);
	childPopulator.reset();
	if (detailNode != node) {
		childPopulator.pruneRemaining();
		detailNode = node;
	}
	if (node) {
		editable(*node);
	}
	else {
		for (auto& child : detailsPane->get_children()) {
			detailsPane->remove(*child);
		}
	}
	childPopulator.pruneRemaining();
// 	detailsPane->show_all();
}

template <class SceneGraphObject>
void GtkInspector<SceneGraphObject>::setRoot(SceneGraphObject* node)
{
	if (node) {
		updateChildren(*node, treeStore->children());
	}
	else {
		treeStore->clear();
	}
}

template <class SceneGraphObject>
void GtkInspector<SceneGraphObject>::updateChildren(SceneGraphObject& node, const Gtk::TreeNodeChildren& dstChildren) 
{
	auto dstIt = dstChildren.begin();
	for (auto srcChild = node.children().first(); srcChild; srcChild = srcChild->nextSibling()) {
		if (dstIt == dstChildren.end()) {
			dstIt = treeStore->append(dstChildren);
		}
		updateNode(*srcChild, *dstIt);
		++dstIt;
	}
	while (dstIt != dstChildren.end()) {
		dstIt = treeStore->erase(dstIt);
	}
}

template <class SceneGraphObject>
Glib::ustring GtkInspector<SceneGraphObject>::getNodeName(SceneGraphObject& node)
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


template <class SceneGraphObject>
void GtkInspector<SceneGraphObject>::updateNode(SceneGraphObject& node, const Gtk::TreeRow& row)
{
	if (row.get_value(columns.pointer) != &node || updateNamesToggle->get_active()) {
		row.set_value(columns.name, getNodeName(node));
		row.set_value(columns.pointer, &node);
	}
	
	if (&node == detailNode) {
		setupDetails(detailNode);
	}
	
	updateChildren(node, row.children());
}



template <class SceneGraphObject>
bool GtkInspector<SceneGraphObject>::update(SceneGraphObject* node)
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