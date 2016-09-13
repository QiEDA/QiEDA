#ifndef GLWIDGET_H_
#define GLWIDGET_H_

#include <QGLWidget>
#include <QMouseEvent>
#include <QTimer>
#include <list>
#include "qicore/qicore.hpp"
#include "qicore/graphics/GraphicItem.hpp"
#include "qicore/graphics/GLPainter.hpp"

//forward decl as we dont want to expose nanovg
struct NVGcontext;

namespace qicore {
namespace ui {
    class QICORE_EXPORT GLWidget : public QGLWidget  {
    friend class GLScrollArea;

    Q_OBJECT

    public:
        explicit GLWidget(QWidget *parent = 0);
        ~GLWidget();
        
    protected:
        void initializeGL() override;
        void resizeGL(int width, int height) override;
        void paintGL() override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;
        void wheelEvent(QWheelEvent *event) override;

        void drawGrid();
        QPoint mouseMoveStartPos_;
        struct NVGcontext* nanovg_;
        graphics::GLPainter* painter_;

        std::list<qicore::graphics::GraphicItem *> graphicItems_;

        float panX_;
        float panY_;
        float zoom_;

        bool panStarted_;
        QTimer update_timer_;
    };
}
}
#endif