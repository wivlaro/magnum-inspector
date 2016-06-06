#pragma once

#include "forwarddeclarations.h"
#include <string>
#include <vector>
#include <functional>
#include <forward_list>

#if defined(__GNUG__)
#define HAS_RTTI
#elif defined(__has_feature)
#if __has_feature(cxx_rtti)
#define HAS_RTTI
#endif
#endif

#ifdef HAS_RTTI
#include <typeinfo>
#endif

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
	
	
	static std::string getDemangledNameFor(const void* ptr, const char* typenam);
	
	template<typename T>
	static std::string getNameFor(const T* ptr) {
		return getDemangledNameFor(ptr, ptr ? typeid(*ptr).name() : typeid(T*).name());
	}
	
	virtual std::string getName() const {
		return getNameFor<Inspectable>(this);
	}

	virtual void getChildren(std::function<void(Inspectable&)> iterator) {}
	virtual void getComponents(std::function<void(Inspectable&)> iterator) {}
	virtual void onInspect(Inspector& inspector) {};

	void addDestroyListener(DestroyListener* listener);
	void removeDestroyListener(DestroyListener* listener);

private:

	std::forward_list<DestroyListener*> onDestroy;
};

}