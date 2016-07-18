#pragma once

#include "Inspector.h"
#include "GtkChildPopulator.h"
#include <gtkmm/container.h>
#include "GtkInspectionField.h"
#include "Inspectable.h"

namespace MagnumInspector {

class InspectorNode;

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

	virtual void editable(const char* name, int* f, uint n, uint m);
	virtual void readonly(const char* name, const int* f, uint n, uint m);

	virtual void editable(const char* name, float* f, uint n, uint m);
    virtual void readonly(const char* name, const float* f, uint n, uint m);
	
	virtual void editable(const char* name, Inspectable* i);
	virtual void readonly(const char* name, Inspectable* i);
	
	virtual void inspectAsMain(const char* name, Inspectable& i);

protected:
    GtkChildPopulator childPopulator;
	
	template<typename FieldValueWidget>
    FieldValueWidget& addField(const char* name)
	{
		GtkInspectionField& field = childPopulator.ensureChild<GtkInspectionField>();
		if (field.getLabel().get_text() != name) {
			field.getLabel().set_text(name);
		}
		return field.ensureChild<FieldValueWidget>();
	}
	
private:


	template<typename ValueType>
	void editableInteger(const char* name, ValueType& i);
	template<typename ValueType>
	void readonlyInteger(const char* name, const ValueType& i);
};

}