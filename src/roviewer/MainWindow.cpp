
#include <QtWidgets/QWidget>
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QiMainWindow("QiViewer",parent)
{
   // glscrollarea = new rocore::ui::GLScrollArea(this);

   // glscrollarea->setViewport(glarea);

    QMdiSubWindow* child = new QMdiSubWindow(mdiArea_->viewport());
    child->setAttribute(Qt::WA_DeleteOnClose);

    glarea = new rocore::ui::GLWidget(child);
    child->setWidget(glarea);

    mdiArea_->addSubWindow(child);

    child->showMaximized();


 //   menubar_ = new QMenuBar(mdiArea_);
 //   QMenu* fileMenu = new QMenu(tr("&File"));
 //   fileMenu->addAction("Open file");
 //   menubar_->addMenu(fileMenu);
}

MainWindow::~MainWindow()
{
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
}
