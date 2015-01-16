#pragma once
#include <gtkmm/grid.h>

namespace MagnumInspector {

class GtkMatrixWidget : public Gtk::Grid
{
public:
    GtkMatrixWidget() {
		set_row_homogeneous(true);
		set_column_homogeneous(true);
	}
	
	virtual ~GtkMatrixWidget() { }
	
	template<typename CellContent, typename ValueType>
	void update(ValueType* f, uint cols, uint rows, std::function<void(CellContent&, ValueType&)> update) {
		bool anyAdd = false;
		for (uint j = 0, index = 0; j != rows; j++) {
			for (uint i = 0; i != cols; i++, index++) {
				auto content = dynamic_cast<CellContent*>(get_child_at(i, j));
				if (!content) {
					content = Gtk::manage(new CellContent());
					attach(*content, i, j, 1, 1);
					anyAdd = true;
				}
				update(*content, f[index]);
			}
		}
		if (anyAdd) show_all();
	}
};

}