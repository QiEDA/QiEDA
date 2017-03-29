#include <iostream>
#include <QtDebug>
#include <QApplication>
#include "MainWindow.hpp"

void qtMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString &message)
{
    switch(type){
        case QtDebugMsg:
            std::cout << "[Debug] ";
            break;
        case QtInfoMsg:
            std::cout << "[Info] ";
            break;
        case QtWarningMsg:
            std::cout << "[Warning] ";
            break;
        case QtCriticalMsg:
            std::cout << "[Critical] ";
            break;
        case QtFatalMsg:
            std::cout << "[Fatal] ";
            break;
    }
	std::cout << message.toLocal8Bit().constData() << std::endl;
}


int main(int argc, char *argv[])
{
    QSurfaceFormat format;
    format.setVersion(2,0);
    format.setProfile(QSurfaceFormat::NoProfile);
    QSurfaceFormat::setDefaultFormat(format);

	qInstallMessageHandler(qtMessageHandler);
	QApplication app(argc, argv);

	MainWindow window;
	window.show();

	return (app.exec());
}