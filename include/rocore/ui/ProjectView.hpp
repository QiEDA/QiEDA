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

class ROCORE_EXPORT ProjectView : public QTreeView
{
	Q_OBJECT

public:
	ProjectView(std::shared_ptr<rocore::projects::Project> project, QWidget* parent=0);

public slots:
	void projectNameChanged(QString name);

protected:
	void mouseDoubleClickEvent (QMouseEvent * );
private:
	std::shared_ptr<rocore::projects::Project> project_;
};

}
}

#endif //ROEDA_PROJECTVIEWER_HPP
