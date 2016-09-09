#include "qicore/ui/GLScrollArea.hpp"
#include "qicore/ui/GLWidget.hpp"

using namespace qicore::ui;

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