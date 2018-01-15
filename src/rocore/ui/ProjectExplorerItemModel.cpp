//
// Created by mroszko on 3/29/2017.
//

#include <QtWidgets>

#include "rocore/ui/ProjectExplorerItem.hpp"
#include "rocore/ui/ProjectExplorerItemModel.hpp"

using namespace rocore::ui;

ProjectExplorerItemModel::ProjectExplorerItemModel(std::shared_ptr<rocore::projects::Project> project, QObject *parent)
		: QStandardItemModel(parent)
{
	project_ = project;

	setColumnCount(1);

	auto root = invisibleRootItem();

	QStandardItem *projectRoot = new QStandardItem("[Project Name]");
	root->appendRow(projectRoot);

	QStandardItem *gerbers = new QStandardItem(QIcon(":/icons/folder.png"),"Gerbers");
	projectRoot->appendRow(gerbers);

	QStandardItem * ln = new QStandardItem("test.gbr");

	gerbers->appendRow(ln);
}

