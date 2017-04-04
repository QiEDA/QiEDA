//
// Created by mroszko on 3/29/2017.
//

#include <QtWidgets>

#include "rocore/projects/ProjectViewItem.hpp"
#include "rocore/projects/ProjectViewItemModel.hpp"

using namespace rocore::projects;

ProjectViewItemModel::ProjectViewItemModel(std::shared_ptr<Project> project, QObject *parent)
		: QStandardItemModel(parent)
{
	project_ = project;

	auto root = invisibleRootItem();

	QStandardItem *projectRoot = new QStandardItem("[Project Name]");
	root->appendRow(projectRoot);

	for (int i = 0; i < 4; ++i) {
		QStandardItem *item = new QStandardItem(QString("item %0").arg(i));
		projectRoot->appendRow(item);
	}
}

