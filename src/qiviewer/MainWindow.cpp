
#include <QtWidgets/QWidget>
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    glscrollarea = new qicore::ui::GLScrollArea(this);
    
    glarea = new qicore::ui::GLWidget(glscrollarea);
    glscrollarea->setViewport(glarea);
    setCentralWidget(glscrollarea);

    menubar_ = new QMenuBar(glscrollarea);
    QMenu* fileMenu = new QMenu(tr("&File"));
    fileMenu->addAction("Open file");
    menubar_->addMenu(fileMenu);


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