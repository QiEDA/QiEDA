#include "qicore/ui/GLWidget.hpp"
#include <gl/GLU.h>
#include <gl/GL.h>

using namespace qicore::ui;

void GLWidget::initializeGL() {
    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void GLWidget::resizeGL(int width, int height) {
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)width/height, 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5,0,0,0,0,1,0);
}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-0.5, -0.5, 0);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f( 0.5, -0.5, 0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f( 0.0,  0.5, 0);
    glEnd();
}