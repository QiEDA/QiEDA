//
// Created by mroszko on 3/29/2017.
//

#include <QHeaderView>
#include "rocore/ui/LayerView.hpp"
#include "rocore/ui/LayerViewItem.hpp"
#include "rocore/ui/LayerViewItemModel.hpp"

using namespace rocore::ui;

LayerView::LayerView(std::shared_ptr<rocore::projects::Project> project, QWidget* parent)
		: QListView(parent)
{
	setModel(new LayerViewItemModel(project));
}