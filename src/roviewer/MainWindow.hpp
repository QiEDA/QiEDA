#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMenuBar>
#include <memory>
#include "rocore/ui/GLScrollArea.hpp"
#include "rocore/ui/GLWidget.hpp"
#include "rocore/ui/QiMainWindow.hpp"
#include "rocore/projects/Viewer.hpp"

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

public slots:
	void projectNameChanged(QString name);

private:
	std::unique_ptr<rocore::projects::Viewer> project_;
};

#endif // MAINWINDOW_H
