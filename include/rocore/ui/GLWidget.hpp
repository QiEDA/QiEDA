#ifndef GLWIDGET_H_
#define GLWIDGET_H_

#include <QGLWidget>
#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QMouseEvent>
#include <QTimer>
#include <list>
#include "rocore/rocore.hpp"
#include "rocore/graphics/GraphicItem.hpp"
#include "rocore/graphics/GraphicDocument.hpp"
#include "rocore/graphics/GLPainter.hpp"

namespace rocore {
namespace ui {
class ROCORE_EXPORT GLWidget : public QOpenGLWidget  {
friend class GLScrollArea;

Q_OBJECT

public:
    explicit GLWidget(rocore::graphics::GraphicDocument* document, QWidget *parent = 0);
    ~GLWidget();
	void AddLayer(rocore::graphics::GraphicLayer * layer)
	{
		//layers_.push_back(layer);
		//painter_->RegisterGraphicLayer(layer);
	}

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
    graphics::GLPainter* painter_;
	graphics::GraphicDocument* document_;

    float panX_;
    float panY_;
    float zoom_;

    bool panStarted_;
    QTimer update_timer_;
};
}
}
#endif