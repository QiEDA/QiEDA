#define NANOVG_GL2_IMPLEMENTATION

#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "nanovg.h"
#include "nanovg_gl.h"
#include "qicore/ui/GLWidget.hpp"


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

    nvgEndFrame(nanovg_);
}