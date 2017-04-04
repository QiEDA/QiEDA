//
// Created by mroszko on 3/29/2017.
//

#include <QApplication>
#include <QPainter>
#include <QColor>
#include <QStringList>
#include "rocore/ui/LayerViewItem.hpp"

using namespace rocore::ui;

LayerViewItem::LayerViewItem() : QStandardItem()
{
	QColor color = Qt::blue;
	setData(color, Qt::DecorationRole);
}

LayerViewItem::LayerViewItem(const QString& text) : QStandardItem(text)
{

}