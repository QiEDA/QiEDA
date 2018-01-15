//
// Created by mroszko on 3/29/2017.
//

#ifndef ROEDA_PROJECTEXPLORERITEM_HPP
#define ROEDA_PROJECTEXPLORERITEM_HPP

#include <QStandardItem>
#include "rocore/rocore.hpp"

namespace rocore {
namespace ui {

class ROCORE_EXPORT ProjectExplorerItem : public QStandardItem {
public:
	ProjectExplorerItem();

	virtual int type() const override
	{
		return QStandardItem::UserType + 2;
	}
};

}
}

#endif //ROEDA_PROJECTEXPLORERITEM_HPP
