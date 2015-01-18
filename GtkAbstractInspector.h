#pragma once

#include "Inspector.h"
#include "GtkChildPopulator.h"
#include <gtkmm/container.h>
#include "GtkInspectionField.h"
#include "Inspectable.h"
#include <Magnum/SceneGraph/AbstractObject.h>

namespace MagnumInspector {

class GtkAbstractInspector : public Inspector
{
public:
	
    virtual void editable(const char* name, std::string& s);
	virtual void readonly(const char* name, const std::string& s);
	
	virtual void editable(const char* name, bool& i);
	virtual void readonly(const char* name, bool i);
	
	virtual void editable(const char* name, char& i) { editableInteger(name, i); }
	virtual void readonly(const char* name, const char& i) { readonlyInteger(name, i); }
	
	virtual void editable(const char* name, unsigned char& i) { editableInteger(name, i); }
	virtual void readonly(const char* name, const unsigned char& i) { readonlyInteger(name, i); }
	
	virtual void editable(const char* name, short& i) { editableInteger(name, i); }
	virtual void readonly(const char* name, const short& i) { readonlyInteger(name, i); }
	
	virtual void editable(const char* name, unsigned short& i) { editableInteger(name, i); }
	virtual void readonly(const char* name, const unsigned short& i) { readonlyInteger(name, i); }
	
	virtual void editable(const char* name, int& i) { editableInteger(name, i); }
	virtual void readonly(const char* name, const int& i) { readonlyInteger(name, i); }
	
	virtual void editable(const char* name, unsigned& i) { editableInteger(name, i); }
	virtual void readonly(const char* name, const unsigned& i) { readonlyInteger(name, i); }
	
	virtual void editable(const char* name, long& i) { editableInteger(name, i); }
	virtual void readonly(const char* name, const long& i) { readonlyInteger(name, i); }
	
	virtual void editable(const char* name, unsigned long& i) { editableInteger(name, i); }
	virtual void readonly(const char* name, const unsigned long& i) { readonlyInteger(name, i); }
	
    virtual void editable(const char* name, float& f);
    virtual void readonly(const char* name, const float& f);
	
    virtual void editable(const char* name, float* f, uint n, uint m);
    virtual void readonly(const char* name, const float* f, uint n, uint m);
	
	virtual void editable(Inspectable* i);
	virtual void readonly(Inspectable* i);
	
	virtual void editable(Magnum::SceneGraph::AbstractObject2D& i) { editableObject(i); }
	virtual void readonly(Magnum::SceneGraph::AbstractObject2D& i) { readonlyObject(i); }
	virtual void editable(Magnum::SceneGraph::AbstractObject3D& i) { editableObject(i); }
	virtual void readonly(Magnum::SceneGraph::AbstractObject3D& i) { readonlyObject(i); }
	
	virtual void editable(Magnum::SceneGraph::AbstractFeature2D& i) { editableFeature(i); }
	virtual void readonly(Magnum::SceneGraph::AbstractFeature2D& i) { readonlyFeature(i); }
	virtual void editable(Magnum::SceneGraph::AbstractFeature3D& i) { editableFeature(i); }
	virtual void readonly(Magnum::SceneGraph::AbstractFeature3D& i) { readonlyFeature(i); }
	
protected:
    GtkChildPopulator childPopulator;
	
	template<typename FieldValueWidget>
    FieldValueWidget& addField(const char* name)
	{
		GtkInspectionField& field = childPopulator.ensureChild<GtkInspectionField>();
		field.getLabel().set_text(name);
		return field.ensureChild<FieldValueWidget>();
	}
	
private:
	template<uint Dimensions, typename ValueType>
	void editableObject(Magnum::SceneGraph::AbstractObject<Dimensions, ValueType>& object);
	template<uint Dimensions, typename ValueType>
	void readonlyObject(Magnum::SceneGraph::AbstractObject<Dimensions, ValueType>& object);
	
	template<uint Dimensions, typename ValueType>
	void editableFeature(Magnum::SceneGraph::AbstractFeature<Dimensions, ValueType>& feature);
	
	template<uint Dimensions, typename ValueType>
	void readonlyFeature(Magnum::SceneGraph::AbstractFeature<Dimensions, ValueType>& feature);
	

	template<typename ValueType>
	void editableInteger(const char* name, ValueType& i);
	template<typename ValueType>
	void readonlyInteger(const char* name, const ValueType& i);
};

}