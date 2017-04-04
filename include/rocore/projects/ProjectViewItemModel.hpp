//
// Created by mroszko on 3/29/2017.
//

#ifndef ROEDA_ITEMMODEL_HPP
#define ROEDA_ITEMMODEL_HPP

#include <QStandardItemModel>
#include <QModelIndex>
#include <QVariant>
#include <memory>
#include "rocore/rocore.hpp"
#include "rocore/projects/Project.hpp"

namespace rocore {
namespace projects {

class ProjectViewItem;

class ROCORE_EXPORT ProjectViewItemModel : public QStandardItemModel {
Q_OBJECT

public:
	ProjectViewItemModel(std::shared_ptr<Project> project_,
					 QObject *parent = 0);


private:
	std::shared_ptr<Project> project_;
};

}
}

#endif //ROEDA_ITEMMODEL_HPP
