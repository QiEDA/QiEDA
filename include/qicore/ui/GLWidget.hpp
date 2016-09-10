#ifndef GLWIDGET_H_
#define GLWIDGET_H_

#include <QtOpenGL>
#include <list>
#include "qicore/qicore.hpp"
#include "qicore/graphics/GraphicItem.hpp"

//forward decl as we dont want to expose nanovg
struct NVGcontext;

namespace qicore {
namespace ui {
    class QICORE_EXPORT GLWidget : public QOpenGLWidget {
    friend class GLScrollArea;
        
    //Q_OBJECT

    public:
        GLWidget(QWidget *parent): QOpenGLWidget(parent) {}
        ~GLWidget();
        
    protected:
        void initializeGL() override;
        void resizeGL(int width, int height) override;
        void paintGL() override;
        
        struct NVGcontext* nanovg_;

        std::list<qicore::graphics::GraphicItem *> graphicItems_;
    };
}
}
#endif