#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMenuBar>
#include "qicore/ui/GLScrollArea.hpp"
#include "qicore/ui/GLWidget.hpp"
#include "qicore/ui/QiMainWindow.hpp"

class MainWindow : public QiMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    bool event(QEvent *event) override;
    
    qicore::ui::GLWidget* glarea;
    qicore::ui::GLScrollArea* glscrollarea;
    QMenuBar* menubar_;
};

#endif // MAINWINDOW_H
