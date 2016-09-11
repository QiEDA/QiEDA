#define NANOVG_GL2_IMPLEMENTATION

#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "nanovg.h"
#include "nanovg_gl.h"
#include "qicore/ui/GLWidget.hpp"
#include "qicore/graphics/Color.hpp"
#include "qicore/graphics/GraphicCircle.hpp"
#include "qicore/graphics/GraphicLine.hpp"
#include "qicore/graphics/GraphicArc.hpp"
#include "qicore/graphics/GraphicRectangle.hpp"
#include "qicore/graphics/GraphicText.hpp"


using namespace qicore::ui;
using namespace qicore::graphics;

GLWidget::GLWidget(QWidget *parent): QGLWidget (parent) {
    connect(&update_timer_, SIGNAL(timeout()), this, SLOT(updateGL()));
    panX = 0;
    panY = 0;
    zoom_ = 10;
    setMouseTracking(true);
    panStarted_ = false;
}

GLWidget::~GLWidget() {
	nvgDeleteGL2(nanovg_);
    setFocusPolicy(Qt::StrongFocus);
}

void GLWidget::initializeGL() {
    glewInit();
    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);
    nanovg_ = nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES);


    Point p1;
    p1.x = 5;
    p1.y = 5;
    qicore::graphics::Point p2;
    p2.x = 9;
    p2.y = 5;

    GraphicLine* gral = new GraphicLine(p1,p2, 2, Colors::Red);


    Point p3;
    p3.x = 1;
    p3.y = 2;
    GraphicRectangle* gral2 = new GraphicRectangle(p3,3, 4, Colors::Blue);


    Point p4;
    p4.x = 5;
    p4.y = 2;
    GraphicRectangle* gral3 = new GraphicRectangle(p4,2, 4, Colors::Purple);

    Point p5;
    p4.x = 15;
    p4.y = 2;
    GraphicCircle* gral4 = new GraphicCircle(p5,4, Colors::Silver);

    Point p6;
    p6.x = 20;
    p6.y = 2;
    GraphicArc* gral5 = new GraphicArc(p6,4,0,2, Colors::Silver);

    Point p7;
    p7.x = 15;
    p7.y = 10;
    GraphicText* gral6 = new GraphicText(p7,"TESTING",12, Colors::Lime);


    graphicItems_.push_back(gral);
    graphicItems_.push_back(gral2);
    graphicItems_.push_back(gral3);
    graphicItems_.push_back(gral4);
    graphicItems_.push_back(gral5);
    graphicItems_.push_back(gral6);

    update_timer_.start(16);

    nvgCreateFont(nanovg_, "sans", "./fonts/Roboto-Regular.ttf");
}

void GLWidget::resizeGL(int width, int height) {
    glViewport(0,0,width,height);
}

void GLWidget::paintGL() {

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    nvgBeginFrame(nanovg_, width(), height(), devicePixelRatio());
    nvgResetTransform(nanovg_);
    nvgTranslate(nanovg_,panX,panY);
    nvgScale(nanovg_,zoom_,zoom_);

    for (std::list<qicore::graphics::GraphicItem*>::iterator it = graphicItems_.begin(); it != graphicItems_.end(); ++it) {
        (*it)->draw(nanovg_);
    }

    nvgEndFrame(nanovg_);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MouseButton::MidButton)
    {
        panStarted_ = true;
        mouseMoveStartPos_ = event->pos();
    }
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    panStarted_ = false;
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(panStarted_)
    {
        int dx = event->x() - mouseMoveStartPos_.x();
        int dy = event->y() - mouseMoveStartPos_.y();

        panX += dx;
        panY += dy;

        mouseMoveStartPos_ = event->pos();
    }
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    QPoint delta = event->angleDelta();
    if(delta.ry() > 0)
    {
        zoom_ *= 1.1;
    }
    else
    {
        zoom_ /= 1.1;
    }
}