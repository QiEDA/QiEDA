//
// Created by mroszko on 3/29/2017.
//

#ifndef ROEDA_LAYERVIEWITEM_HPP
#define ROEDA_LAYERVIEWITEM_HPP

#include <QStyledItemDelegate>
#include <QStandardItem>
#include "rocore/rocore.hpp"

namespace rocore {
namespace ui {

class ROCORE_EXPORT LayerViewItem : public QStandardItem {

public:
	LayerViewItem();
	LayerViewItem(const QString& text);

	virtual int type() const override
	{
		return QStandardItem::UserType + 1;
	}
};

}
}

#endif //ROEDA_PROJECTITEM_HPP
