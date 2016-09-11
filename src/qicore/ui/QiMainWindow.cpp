//
// Created by mroszko on 9/10/2016.
//

#include "qicore/ui/QiMainWindow.hpp"


QiMainWindow::QiMainWindow(QWidget *parent):
        QMainWindow(parent)
{
    mdiArea_ = new QMdiArea(this);
    mdiArea_->setTabPosition(QTabWidget::South);
    mdiArea_->setViewMode(QMdiArea::TabbedView);
    mdiArea_->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea_->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea_->setActivationOrder(QMdiArea::ActivationHistoryOrder);
    mdiArea_->setOption(QMdiArea::DontMaximizeSubWindowOnActivation, false);

    setCentralWidget(mdiArea_);
}


QiMainWindow::~QiMainWindow()
{
}