//
// Created by mroszko on 3/29/2017.
//

#ifndef ROEDA_LAYERVIEWITEMMODEL_HPP
#define ROEDA_LAYERVIEWITEMMODEL_HPP

#include <QStandardItemModel>
#include <memory>
#include "rocore/rocore.hpp"
#include "rocore/projects/Project.hpp"

namespace rocore {
namespace ui {

class LayerViewItem;

class ROCORE_EXPORT LayerViewItemModel : public QStandardItemModel {
Q_OBJECT

public:
	LayerViewItemModel(std::shared_ptr<rocore::projects::Project> project_,
					 QObject *parent = 0);


private:
	std::shared_ptr<rocore::projects::Project> project_;
};

}
}

#endif //ROEDA_ITEMMODEL_HPP
