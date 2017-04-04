//
// Created by mroszko on 3/29/2017.
//

#include <QHeaderView>
#include "rocore/ui/ProjectView.hpp"
#include "rocore/projects/ProjectViewItemModel.hpp"

using namespace rocore::ui;
using namespace rocore::projects;

ProjectView::ProjectView(std::shared_ptr<rocore::projects::Project> project, QWidget* parent)
		: QTreeView(parent)
{
	header()->hide();

	setModel(new ProjectViewItemModel(project));

	for (int column = 0; column < model()->columnCount(); ++column)
		resizeColumnToContents(column);

	QModelIndex root = this->model()->index(0,0,QModelIndex());
	this->setExpanded(root, true);
	//this->setDragEnabled(true);
	//this->setAcceptDrops(true);
	//this->setDropIndicatorShown(false);
	//this->setRootIsDecorated(false);
	this->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

void ProjectView::mouseDoubleClickEvent (QMouseEvent * event)
{
}

void ProjectView::projectNameChanged(QString name) {
	setWindowTitle("roviewer - " + name);

	QModelIndex root = this->model()->index(0,0,QModelIndex());
	model()->setData(root, name);
}