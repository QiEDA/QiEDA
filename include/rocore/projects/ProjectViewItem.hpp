//
// Created by mroszko on 3/29/2017.
//

#ifndef ROEDA_PROJECTITEM_HPP
#define ROEDA_PROJECTITEM_HPP

#include <QStandardItem>
#include "rocore/rocore.hpp"

namespace rocore {
namespace projects {

class ROCORE_EXPORT ProjectViewItem : public QStandardItem {
public:
	ProjectViewItem();

	virtual int type() const override
	{
		return QStandardItem::UserType + 2;
	}
};

}
}

#endif //ROEDA_PROJECTITEM_HPP
