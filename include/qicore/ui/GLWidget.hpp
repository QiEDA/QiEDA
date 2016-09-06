#ifndef GLWIDGET_H_
#define GLWIDGET_H_

#include <QtOpenGL/QGLWidget>
#include "qicore/qicore.hpp"

namespace qicore {
namespace ui {
    class QICORE_EXPORT GLWidget : public QGLWidget {
    Q_OBJECT

    public:
        GLWidget(QWidget *parent): QGLWidget(parent) {}
        
    protected:
        void initializeGL() override;
        void resizeGL(int width, int height) override;
        void paintGL() override;
    };
}
}
#endif