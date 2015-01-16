#pragma once

#include "Inspector.h"
#include "GtkChildPopulator.h"
#include <gtkmm/container.h>
#include "GtkInspectionField.h"
#include "Inspectable.h"
#include <Magnum/SceneGraph/AbstractObject.h>

namespace MagInspect {

class GtkAbstractInspector : public Inspector
{
public:
	
    virtual void editable(const char* name, std::string& s);
	virtual void readonly(const char* name, const std::string& s);
	
	virtual void editable(const char* name, bool& i);
	virtual void readonly(const char* name, bool i);
	
	virtual void editable(const char* name, int& i);
	virtual void readonly(const char* name, const int& i);
	
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
	
	void resetChildPopulator() { childPopulator.reset(); }
	
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
};

}