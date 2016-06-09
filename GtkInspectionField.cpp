#include "GtkInspectionField.h"

namespace MagnumInspector {

GtkInspectionField::GtkInspectionField()
:	valueWidget(nullptr)
{
	set_spacing(5);
	labelWidget.set_size_request(100, -1);
	labelWidget.property_xalign().set_value(0);
	add(labelWidget);
	show_all();
}
	
	
}