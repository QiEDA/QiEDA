#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
   // Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    bool event(QEvent *event) override;
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
