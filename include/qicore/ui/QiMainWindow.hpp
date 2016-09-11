//
// Created by mroszko on 9/10/2016.
//

#ifndef QIEDA_BASEWINDOW_H
#define QIEDA_BASEWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMenuBar>
#include "qicore/qicore.hpp"

class QICORE_EXPORT QiMainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit QiMainWindow(QWidget *parent = 0);
    ~QiMainWindow();
protected:
    QMdiArea* mdiArea_;
    QMenuBar* menubar_;
};


#endif //QIEDA_BASEWINDOW_H
