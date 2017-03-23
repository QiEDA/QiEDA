//
// Created by mroszko on 9/10/2016.
//

#include "rocore/ui/QiMainWindow.hpp"


QiMainWindow::QiMainWindow(QString appKey, QWidget *parent):
        QMainWindow(parent)
{
    appKey_ = appKey;

    mdiArea_ = new QMdiArea(this);
    mdiArea_->setTabPosition(QTabWidget::South);
    mdiArea_->setViewMode(QMdiArea::TabbedView);
    mdiArea_->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea_->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea_->setActivationOrder(QMdiArea::ActivationHistoryOrder);
    mdiArea_->setOption(QMdiArea::DontMaximizeSubWindowOnActivation, false);

    setCentralWidget(mdiArea_);


    readSettings();
}


QiMainWindow::~QiMainWindow()
{
}

void QiMainWindow::readSettings()
{
    QSettings settings("QiEDA", appKey_);
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
}

void QiMainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings("QiEDA", appKey_);
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    QMainWindow::closeEvent(event);
}

