//
// Created by mroszko on 3/29/2017.
//

#ifndef ROEDA_PROJECTVIEW_HPP
#define ROEDA_PROJECTVIEW_HPP

#include <memory>
#include <QTreeView>
#include "rocore/rocore.hpp"
#include "rocore/projects/Project.hpp"

namespace rocore {
namespace ui {

class ROCORE_EXPORT ProjectExplorer : public QTreeView
{
	Q_OBJECT

public:
	ProjectExplorer(QWidget* parent=0);

	void SetProject(std::shared_ptr<rocore::projects::Project> project);

public slots:
	void projectNameChanged(QString name);

protected:
	void mouseDoubleClickEvent (QMouseEvent *e);
private:
	std::shared_ptr<rocore::projects::Project> project_ = nullptr;
private slots:
	void onCustomContextMenuRequested(const QPoint& pos);
	void showContextMenu(const QAbstractItemModel* item, const QPoint& globalPos);
};

}
}

#endif //ROEDA_PROJECTVIEWER_HPP
