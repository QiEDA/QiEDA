#define NANOVG_GL2_IMPLEMENTATION

#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <QDebug>
#include "qicore/Units.hpp"
#include "qicore/ui/GLWidget.hpp"
#include "qicore/graphics/Color.hpp"
#include "qicore/graphics/GraphicCircle.hpp"
#include "qicore/graphics/GraphicLine.hpp"
#include "qicore/graphics/GraphicArc.hpp"
#include "qicore/graphics/GraphicRectangle.hpp"

#include "qicore/graphics/GraphicText.hpp"

using namespace qicore::ui;
using namespace qicore::graphics;

GLWidget::GLWidget(QWidget *parent): QOpenGLWidget (parent) {
    connect(&update_timer_, SIGNAL(timeout()), this, SLOT(update()));
    panX_ = 0;
    panY_ = 0;
    zoom_ = 10000;
    setMouseTracking(true);
    panStarted_ = false;
}

GLWidget::~GLWidget() {
    setFocusPolicy(Qt::StrongFocus);
}

#define MM(x)   (x/1000.0f)
#define INCHES_TO_MM(x) MM(x*25.4f)
#define MILS_TO_MM(x) MM(x*39.37f)

void GLWidget::initializeGL() {
    qDebug() << "Widget OpenGl: " << format().majorVersion() << "." << format().minorVersion();
    qDebug() << "Context valid: " << context()->isValid();
    qDebug() << "Really used OpenGl: " << context()->format().majorVersion() << "." << context()->format().minorVersion();
    qDebug() << "OpenGl information: VENDOR:       " << (const char*)glGetString(GL_VENDOR);
    qDebug() << "                    RENDERDER:    " << (const char*)glGetString(GL_RENDERER);
    qDebug() << "                    VERSION:      " << (const char*)glGetString(GL_VERSION);
    qDebug() << "                    GLSL VERSION: " << (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);

    painter_ = new GLPainter();

    Point p1;
    p1.x = 0;
    p1.y = 0;
    Point p2;
    p2.x = 0;
    p2.y = Units::InchesToInternalUnits(1.4);

    GraphicLine* gral = new GraphicLine(p1,p2, Units::MilsToInternalUnits(40), Colors::Red);


    Point p3;
    p3.x = 0;
    p3.y = 0;
    GraphicRectangle* gral2 = new GraphicRectangle(p3, Units::InchesToInternalUnits(2), Units::InchesToInternalUnits(1), Colors::Blue);


    Point p4;
    p4.x = Units::InchesToInternalUnits(1.4);
    p4.y = Units::InchesToInternalUnits(2.24);
    GraphicRectangle* gral3 = new GraphicRectangle(p4,Units::InchesToInternalUnits(0.5), Units::InchesToInternalUnits(0.5), Colors::Purple);

    Point p5;
    p4.x = Units::InchesToInternalUnits(0);
    p4.y = Units::InchesToInternalUnits(0);
    GraphicCircle* gral4 = new GraphicCircle(p5,Units::MilsToInternalUnits(300), Colors::Silver);

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

    update_timer_.start(1000 / 60.0);
}

void GLWidget::resizeGL(int w, int h) {

    painter_->Resize(w,h);
}

void GLWidget::paintGL() {

    painter_->PrepareDraw(panX_,panY_, zoom_);

    painter_->Draw(graphicItems_);
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
        float dx = event->x() - mouseMoveStartPos_.x();
        float dy = event->y() - mouseMoveStartPos_.y();

        panX_ += dx/1.0f;
        panY_ += -dy/1.0f;

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