#pragma once

#include "forwarddeclarations.h"
#include <string>
#include <vector>
#include <functional>
#include <forward_list>

namespace MagnumInspector {

class InspectableDestroyListener {
protected:
	virtual void onDestroy(Inspectable* ) = 0;
	friend class Inspectable;
};

class Inspectable
{
public:
	typedef InspectableDestroyListener DestroyListener;

	virtual ~Inspectable();
	virtual std::string getName() const;

	virtual void getChildren(std::vector<Inspectable*>& children) {}
	virtual void getComponents(std::vector<Inspectable*>& children) {}
	virtual void onInspect(Inspector& inspector) {}

	void addDestroyListener(DestroyListener* listener);
	void removeDestroyListener(DestroyListener* listener);

private:

	std::forward_list<DestroyListener*> onDestroy;
};

}