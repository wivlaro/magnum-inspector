#include "GtkInspectionField.h"

namespace MagnumInspector {

GtkInspectionField::GtkInspectionField()
:	valueWidget(nullptr)
{
	add(labelWidget);
	show_all();
}
	
	
}