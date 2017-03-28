
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QtWidgets/QWidget>
#include "About.hpp"
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

    setupMenubar();
}

void MainWindow::setupMenubar()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open gerber"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);
    fileMenu->addAction(openAct);

    QAction *saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);
    fileMenu->addAction(saveAct);


    QAction *saveAsAct = fileMenu->addAction(tr("Save &As..."), this, &MainWindow::saveAs);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the document under a new name"));

    fileMenu->addSeparator();

    QAction *exitAct = fileMenu->addAction(tr("E&xit"), this, &QWidget::close);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction *aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::about);
    aboutAct->setStatusTip(tr("Show the application's About box"));
}

void MainWindow::open()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    QStringList filters;
    filters << "Gerber (*.gbr *.ger *.gtl *.gbl *.gts *.gbs *.gto *.gbo *.gtp *.gbp)"
            << "Any files (*)";

    dialog.setNameFilters(filters);

    if(dialog.exec())
    {
        QString fileName = dialog.selectedFiles()[0];
        if (!fileName.isEmpty())
            LoadFile(fileName);
    }
}

bool MainWindow::save()
{

}

bool MainWindow::saveAs()
{
}
void MainWindow::about()
{
    About about;
    about.exec();
}

void MainWindow::LoadFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                                     .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    QTextStream in(&file);
    QString inStr = in.readAll();


}

MainWindow::~MainWindow()
{
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
}
