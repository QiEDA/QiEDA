//
// Created by mroszko on 3/29/2017.
//

#include <QHeaderView>
#include <QMenu>
#include <QTreeWidgetItem>
#include "rocore/ui/ProjectExplorer.hpp"
#include "rocore/ui/ProjectExplorerItemModel.hpp"

using namespace rocore::ui;
using namespace rocore::projects;

ProjectExplorer::ProjectExplorer(QWidget* parent)
		: QTreeView(parent)
{
	header()->hide();
	setContextMenuPolicy(Qt::CustomContextMenu);

	SetProject(nullptr);

	connect(this,
			SIGNAL(customContextMenuRequested(const QPoint&)),
			SLOT(onCustomContextMenuRequested(const QPoint&)));
}

static const int ItemType1 = QTreeWidgetItem::UserType;
static const int ItemType2 = QTreeWidgetItem::UserType + 1;

void ProjectExplorer::mouseDoubleClickEvent (QMouseEvent * event)
{
}

void ProjectExplorer::onCustomContextMenuRequested(const QPoint& pos) {
	QModelIndex index = indexAt(pos);

	if (index.isValid() && index.row() % 2 == 0) {
		showContextMenu(index.model(), mapToGlobal(pos));
	}
}

void ProjectExplorer::showContextMenu(const QAbstractItemModel* item, const QPoint& globalPos) {
	QMenu menu;

	menu.addAction("This is a type 2");

	menu.exec(globalPos);
}

void ProjectExplorer::projectNameChanged(QString name) {
	setWindowTitle("roviewer - " + name);

	QModelIndex root = this->model()->index(0,0,QModelIndex());
	model()->setData(root, name);
}

void ProjectExplorer::SetProject(std::shared_ptr<rocore::projects::Project> project) {

	if(project_ != nullptr) {
		project_->disconnect(this);
	}

	project_.reset();

	project_ = project;

	// project could be null (blank startup)
	if(project != nullptr) {
		QObject::connect(project_.get(), &rocore::projects::Project::NameChanged,
						 this, &rocore::ui::ProjectExplorer::projectNameChanged);


		// Update the model
		auto m = model();
		setModel(new ProjectExplorerItemModel(project));
		if(m != nullptr) {
			delete m;
		}

		for (int column = 0; column < model()->columnCount(); ++column)
			resizeColumnToContents(column);

		QModelIndex root = this->model()->index(0,0,QModelIndex());
		this->setExpanded(root, true);
		//this->setDragEnabled(true);
		//this->setAcceptDrops(true);
		//this->setDropIndicatorShown(false);
		//this->setRootIsDecorated(false);
		this->setSelectionBehavior(QAbstractItemView::SelectRows);
		this->setSelectionMode(QAbstractItemView::ExtendedSelection);


		projectNameChanged(project->GetName());
	}
}