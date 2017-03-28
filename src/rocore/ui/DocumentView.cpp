//
// Created by mroszko on 3/28/2017.
//

#include "rocore/ui/DocumentView.hpp"

using namespace rocore::ui;

DocumentView::DocumentView(QWidget* parent, Qt::WindowFlags flags)
		: QMdiSubWindow(parent, flags)
{
	setAttribute(Qt::WA_DeleteOnClose);
	showMaximized();

	glarea_ = new rocore::ui::GLWidget(this);
	setWidget(glarea_);
}
