//
// Created by mroszko on 3/28/2017.
//

#include "rocore/ui/DocumentView.hpp"
#include "rocore/graphics/GraphicDocument.hpp"

using namespace rocore::ui;

DocumentView::DocumentView(QWidget* parent, Qt::WindowFlags flags)
		: QMdiSubWindow(parent, flags)
{
	setAttribute(Qt::WA_DeleteOnClose);
	showMaximized();

	document_ = new rocore::graphics::GraphicDocument();
	glArea_ = new rocore::ui::GLWidget(document_, this);
	setWidget(glArea_);
}
