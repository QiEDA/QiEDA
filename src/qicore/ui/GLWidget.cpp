#define NANOVG_GL2_IMPLEMENTATION

#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "nanovg.h"
#include "nanovg_gl.h"
#include "qicore/ui/GLWidget.hpp"
#include "qicore/graphics/Color.hpp"
#include "qicore/graphics/GraphicLine.hpp"
#include "qicore/graphics/GraphicRectangle.hpp"


using namespace qicore::ui;

GLWidget::~GLWidget() {
	nvgDeleteGL2(nanovg_);
}

void GLWidget::initializeGL() {
    glewInit();
    glClearColor(0,0,0,1);
//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_LIGHT0);
//    glEnable(GL_LIGHTING);
    nanovg_ = nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES);


    qicore::graphics::Point p1;
    p1.x = 1;
    p1.y = 50;
    qicore::graphics::Point p2;
    p2.x = 100;
    p2.y = 50;

    qicore::graphics::GraphicLine* gral = new qicore::graphics::GraphicLine(p1,p2, 10, qicore::graphics::Colors::Red);


    qicore::graphics::Point p3;
    p1.x = 155;
    p1.y = 150;
    qicore::graphics::GraphicRectangle* gral2 = new qicore::graphics::GraphicRectangle(p3,300, 10, qicore::graphics::Colors::Blue);

    graphicItems_.push_back(gral);
    graphicItems_.push_back(gral2);
}

void GLWidget::resizeGL(int width, int height) {
    glViewport(0,0,width,height);
}

void GLWidget::paintGL() {

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    nvgBeginFrame(nanovg_, width(), height(), devicePixelRatio());
    nvgBeginPath(nanovg_);
    nvgRect(nanovg_, 100,100, 120,30);
    nvgFillColor(nanovg_, nvgRGBA(255,192,0,255));
    nvgFill(nanovg_);

    for (std::list<qicore::graphics::GraphicItem*>::iterator it = graphicItems_.begin(); it != graphicItems_.end(); ++it) {
        (*it)->draw(nanovg_);
    }

    nvgEndFrame(nanovg_);
}