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
	void LoadFile(const QString &fileName);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    
    rocore::ui::GLWidget* glarea;
    rocore::ui::GLScrollArea* glscrollarea;

	void setupMenubar();

private slots:
	void open();
	bool save();
	bool saveAs();
	void about();
};

#endif // MAINWINDOW_H
