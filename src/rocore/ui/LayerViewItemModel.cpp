//
// Created by mroszko on 3/29/2017.
//

#include <QtWidgets>

#include "rocore/ui/LayerViewItem.hpp"
#include "rocore/ui/LayerViewItemModel.hpp"

using namespace rocore::ui;

LayerViewItemModel::LayerViewItemModel(std::shared_ptr<rocore::projects::Project> project, QObject *parent)
		: QStandardItemModel(parent)
{
	project_ = project;

	auto root = invisibleRootItem();

	LayerViewItem *projectRoot = new LayerViewItem("Test");

	projectRoot->setEditable(false);
	root->appendRow(projectRoot);
}

