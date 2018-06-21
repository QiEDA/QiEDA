#ifndef QVIEWER_ABOUT_HPP
#define QVIEWER_ABOUT_HPP

#include <QDialog>
#include "ui_About.h"

class QWidget;

class About: public QDialog, public Ui::About
{
public:
	About(QWidget * parent = 0);
	~About();
};

#endif