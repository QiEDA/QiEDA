#include <QApplication>
#include "About.hpp"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	About window;
	window.show();

	return (app.exec());
}