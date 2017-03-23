#include "rocore/ui/GLScrollArea.hpp"
#include "rocore/ui/GLWidget.hpp"

using namespace rocore::ui;

void GLScrollArea::resizeEvent(QResizeEvent * event)
{
    GLWidget * glw = dynamic_cast<GLWidget *>(viewport());
    glw->resizeEvent(event);
}

void GLScrollArea::paintEvent(QPaintEvent *event)
{
    GLWidget * glw = dynamic_cast<GLWidget *>(viewport());
    glw->paintEvent(event);
} 