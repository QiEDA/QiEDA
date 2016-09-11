
#include <QtWidgets/QWidget>
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QiMainWindow(parent)
{
   // glscrollarea = new qicore::ui::GLScrollArea(this);

   // glscrollarea->setViewport(glarea);

    QMdiSubWindow* child = new QMdiSubWindow(mdiArea_->viewport());
    child->setAttribute(Qt::WA_DeleteOnClose);

    glarea = new qicore::ui::GLWidget(child);
    child->setWidget(glarea);

    mdiArea_->addSubWindow(child);

    child->showMaximized();
  //  menubar_ = new QMenuBar(glscrollarea);
  //  QMenu* fileMenu = new QMenu(tr("&File"));
  //  fileMenu->addAction("Open file");
  //  menubar_->addMenu(fileMenu);


}

MainWindow::~MainWindow()
{
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
}

bool MainWindow::event(QEvent *event)
{
    return true;
}