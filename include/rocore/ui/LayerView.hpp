//
// Created by mroszko on 3/29/2017.
//

#ifndef ROEDA_LAYERVIEW_HPP
#define ROEDA_LAYERVIEW_HPP

#include <memory>
#include <QListView>
#include "rocore/rocore.hpp"
#include "rocore/projects/Project.hpp"

namespace rocore {
namespace ui {

class ROCORE_EXPORT LayerView : public QListView
{
	Q_OBJECT

public:
	LayerView(std::shared_ptr<rocore::projects::Project> project, QWidget* parent=0);

private:
	std::shared_ptr<rocore::projects::Project> project_;
};

}
}

#endif //ROEDA_PROJECTVIEWER_HPP
