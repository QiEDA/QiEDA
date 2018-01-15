#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMenuBar>
#include <memory>
#include "rocore/ui/GerberDocumentView.hpp"
#include "rocore/ui/GLScrollArea.hpp"
#include "rocore/ui/GLWidget.hpp"
#include "rocore/ui/QiMainWindow.hpp"
#include "rocore/ui/ProjectExplorer.hpp"
#include "rocore/projects/Project.hpp"

class MainWindow : public QiMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	void LoadFile(const QString &fileName);
	void LoadProject(const QString &fileName);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
	rocore::ui::GerberDocumentView* doc;
	rocore::ui::ProjectExplorer* projectView;

	void setupMenubar();
	void setProject(std::shared_ptr<rocore::projects::Project> project);

private slots:
	void open();
	bool save();
	bool saveAs();
	void about();
	void openRecentProject();

public slots:
	void projectNameChanged(QString name);

private:
	std::shared_ptr<rocore::projects::Project> project_ = nullptr;
	void setupProjectExplorer();
	void setupLayerView();
	void setupProjectSignals();
	void updateRecentFileActions();
	QString strippedName(const QString &fullFileName);


	QAction *recentFileActs[5];
};

#endif // MAINWINDOW_H
