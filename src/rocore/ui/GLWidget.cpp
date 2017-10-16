#define NANOVG_GL2_IMPLEMENTATION

#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <QDebug>
#include <iostream>
#include "rocore/Units.hpp"
#include "rocore/ui/GLWidget.hpp"
#include "rocore/graphics/Color.hpp"
#include "rocore/graphics/GraphicCircle.hpp"
#include "rocore/graphics/GraphicLine.hpp"
#include "rocore/graphics/GraphicArc.hpp"
#include "rocore/graphics/GraphicRectangle.hpp"
#include "rocore/graphics/GridLayer.hpp"

#include "rocore/graphics/GraphicText.hpp"

using namespace rocore::ui;
using namespace rocore::graphics;

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

    auto test = new GridLayer();

    painter_ = new GLPainter();

    GraphicLayer* layer = new GraphicLayer(Colors::Blue);

    Point p1;
    p1.x = 0;
    p1.y = 0;
    Point p2;
    p2.x = 0;
    p2.y = Units::InchesToInternalUnits(8);

    GraphicLine* gral = new GraphicLine(p1,p2, Units::MilsToInternalUnits(40));


/*
    Point p3;
    p3.x = 0;
    p3.y = 0;
    GraphicRectangle* gral2 = new GraphicRectangle(p3, Units::InchesToInternalUnits(2), Units::InchesToInternalUnits(1));

    Point p4;
    p4.x = Units::InchesToInternalUnits(1.4);
    p4.y = Units::InchesToInternalUnits(2.24);
    GraphicRectangle* gral3 = new GraphicRectangle(p4,Units::InchesToInternalUnits(0.5), Units::InchesToInternalUnits(0.5));
*/
    Point p5;
    p5.x = Units::InchesToInternalUnits(0);
    p5.y = Units::InchesToInternalUnits(0);
    GraphicCircle* gral4 = new GraphicCircle(p5,Units::MilsToInternalUnits(300));

    Point p11;
    p11.x = Units::InchesToInternalUnits(1);
    p11.y = Units::InchesToInternalUnits(1);
    GraphicCircle* gral111 = new GraphicCircle(p11,Units::MilsToInternalUnits(300));

    Point p6;
    p6.x = 20;
    p6.y = 2;
    GraphicArc* gral5 = new GraphicArc(p6,4,0,2);

    Point p7;
    p7.x = 15;
    p7.y = 10;
    GraphicText* gral6 = new GraphicText(p7,"TESTING",12);


    layer->AddItem(gral);
   // layer->AddItem(gral2);
    //layer->AddItem(gral3);
    layer->AddItem(gral4);
    layer->AddItem(gral5);
    layer->AddItem(gral6);
    layer->AddItem(gral111);

    layers_.push_back(layer);

    painter_->RegisterGraphicLayer(layer);
   painter_->RegisterGraphicLayer(test);

    update_timer_.start(1000 / 60.0);
}

void GLWidget::resizeGL(int w, int h) {

    painter_->Resize(w,h);
}

void GLWidget::paintGL() {

    painter_->PrepareDraw(panX_,panY_, zoom_);

    painter_->Draw();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MouseButton::MidButton)
    {
        panStarted_ = true;
        mouseMoveStartPos_ = event->pos();
    }

    makeCurrent();
    auto world = painter_->ScreenToWorldCoordinates( glm::ivec2(event->x(),event->y()), 0 );
    QString str;
    str.sprintf("Mouse click at screen %d,%d; world %f,%f,%f", event->x(), event->y(), world.x, world.y, world.z);
    std::cout << str.toStdString();
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