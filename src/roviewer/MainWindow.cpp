
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>
#include <QtWidgets/QDirModel>
#include <rocore/ui/GerberDocumentView.hpp>
#include "About.hpp"
#include "MainWindow.hpp"
#include "rogerber/Gerber.hpp"
#include "rogerber/GerberProcessor.hpp"
#include "rocore/projects/ProjectException.hpp"
#include "rocore/ui/DocumentView.hpp"
#include "rocore/ui/LayerView.hpp"
#include "rocore/graphics/Color.hpp"
#include "util/make_unique.hpp"
#include "GerberOpenGlProcessor.hpp"
#include "rocore/Settings.hpp"

MainWindow::MainWindow(QWidget *parent) :
        QiMainWindow("roviewer",parent)
{
	setupMenubar();

    setCentralWidget(mdiArea_);
	//doc = new rocore::ui::GerberDocumentView(mdiArea_->viewport());
	//mdiArea_->addSubWindow(doc);

	//project_ = std::make_shared<rocore::projects::Project>("untitled");
	setupProjectExplorer();

	setProject(project_);

	setupLayerView();
}

void MainWindow::setProject(std::shared_ptr<rocore::projects::Project> project) {
	//disconnect existing pointer where needed
	if(project_ != nullptr) {
		project_->disconnect(this);
	}

	//transfer pointer
	project_ = project;

	if(project != nullptr) {
		QObject::connect(project_.get(), &rocore::projects::Project::NameChanged,
						 this, &MainWindow::projectNameChanged);

		projectView->SetProject(project_);

		//set manually :/
		projectNameChanged(project_->GetName());
	}
}


void MainWindow::projectNameChanged(QString name) {
    setWindowTitle("roviewer - " + name);
}

void MainWindow::setupProjectExplorer()
{
	QDockWidget *dock = new QDockWidget(tr("Project"), this);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	projectView = new rocore::ui::ProjectExplorer(dock);

	dock->setWidget(projectView);
	addDockWidget(Qt::LeftDockWidgetArea, dock);
}

void MainWindow::setupLayerView()
{
	QDockWidget *dock = new QDockWidget(tr("Layers"), this);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	auto projView = new rocore::ui::LayerView(project_,dock);

	dock->setWidget(projView);
	addDockWidget(Qt::RightDockWidgetArea, dock);
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
    saveAct->setStatusTip(tr("Save the project to disk"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);
    fileMenu->addAction(saveAct);

    QAction *saveAsAct = fileMenu->addAction(tr("Save &As..."), this, &MainWindow::saveAs);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the project under a new name"));

    fileMenu->addSeparator();

	QMenu *openRecentProjectsMenu = fileMenu->addMenu(tr("Open &Recent Project"));

	for (int i = 0; i < rocore::constants::MaxRecentProjects; ++i) {
		recentFileActs[i] = new QAction(this);
		recentFileActs[i]->setVisible(false);
		connect(recentFileActs[i], SIGNAL(triggered()),
				this, SLOT(openRecentProject()));

		openRecentProjectsMenu->addAction(recentFileActs[i]);
	}

	updateRecentFileActions();
	fileMenu->addSeparator();

    QAction *exitAct = fileMenu->addAction(tr("E&xit"), this, &QWidget::close);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction *aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::about);
    aboutAct->setStatusTip(tr("Show the application's About box"));
}

void MainWindow::openRecentProject()
{
	QAction *action = qobject_cast<QAction *>(sender());
	if (action)
		LoadProject(action->data().toString());
}


QString MainWindow::strippedName(const QString &fullFileName)
{
	return QFileInfo(fullFileName).fileName();
}

void MainWindow::updateRecentFileActions()
{
	QStringList files = rocore::Settings::instance().getRecentProjects();
	int numRecentFiles = qMin(files.size(), rocore::constants::MaxRecentProjects);

	for (int i = 0; i < numRecentFiles; ++i) {
		QString text = tr("&%1 %2").arg(i + 1).arg(strippedName(files[i]));
		recentFileActs[i]->setText(text);
		recentFileActs[i]->setData(files[i]);
		recentFileActs[i]->setVisible(true);
	}
	for (int j = numRecentFiles; j < rocore::constants::MaxRecentProjects; ++j)
		recentFileActs[j]->setVisible(false);
}

void MainWindow::open()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
	dialog.setDirectory(rocore::Settings::instance().getDefaultDirectoryPath());
    QStringList filters;
    filters << "roEDA Project (*.roproj)"
            << "Any files (*)";

	dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setNameFilters(filters);

    if(dialog.exec())
    {
        QString selectedFile = dialog.selectedFiles()[0];
        if (!selectedFile.isEmpty()) {
			LoadProject(selectedFile);

			QDir currentDir;
			rocore::Settings::instance().setDefaultDirectoryPath(currentDir.absoluteFilePath(selectedFile));
			rocore::Settings::instance().appendToRecentProjects(selectedFile);
			updateRecentFileActions();
		}
    }
}

void MainWindow::LoadProject(const QString &fileName)
{
	auto project = std::make_shared<rocore::projects::Project>("");

	try {
		project->LoadFromFile(fileName);

		setProject(project);
	} catch (const rocore::projects::ProjectDeserializeException& e) {
		QMessageBox msgBox;
		msgBox.setText("Error loading project.");
		msgBox.setDetailedText(e.what());
		msgBox.setIcon(QMessageBox::Critical);
		msgBox.exec();
	}
}

bool MainWindow::save()
{
	QFileDialog dialog(this);
	dialog.setFileMode(QFileDialog::AnyFile);

	QStringList filters;
	filters << "roEDA Project (*.roproj)";

	dialog.setAcceptMode(QFileDialog::AcceptSave);
	dialog.setNameFilters(filters);

	if(dialog.exec())
	{
		QString fileName = dialog.selectedFiles()[0];
		if (!fileName.isEmpty())
			project_->SaveToFile(fileName);
	}

	return false;
}

bool MainWindow::saveAs()
{
	return false;
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


	rogerber::Gerber gerber;
	std::string data = inStr.toStdString();
	gerber.Parse(data);


	rocore::graphics::GraphicLayer* layer = new rocore::graphics::GraphicLayer(rocore::graphics::Colors::Red);

	GerberOpenGlProcessor processor(gerber, layer);
	processor.Execute();

	doc->AddLayer(layer);
}

MainWindow::~MainWindow()
{
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
}
