//
// Created by bill on 25/05/16.
//

#pragma once

#include <vector>
#include <string>
#include <memory>

namespace MagnumInspector {

class Inspectable;

class InspectorNode : public std::enable_shared_from_this<InspectorNode> {
public:
	virtual void getChildren(std::vector<InspectorNode*>& children) = 0;
	virtual void getComponents(std::vector<Inspectable*>& children) = 0;
	virtual void getName(std::string& name);
};

}


