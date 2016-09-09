#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qicore/ui/GLScrollArea.hpp"
#include "qicore/ui/GLWidget.hpp"

class MainWindow : public QMainWindow
{
   // Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    bool event(QEvent *event) override;
    
    qicore::ui::GLWidget* glarea;
    qicore::ui::GLScrollArea* glscrollarea;
};

#endif // MAINWINDOW_H
