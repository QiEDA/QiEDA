#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMenuBar>
#include "rocore/ui/GLScrollArea.hpp"
#include "rocore/ui/GLWidget.hpp"
#include "rocore/ui/QiMainWindow.hpp"

class MainWindow : public QiMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    
    rocore::ui::GLWidget* glarea;
    rocore::ui::GLScrollArea* glscrollarea;
    QMenuBar* menubar_;
};

#endif // MAINWINDOW_H
