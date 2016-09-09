#ifndef GLSCROLLAREA_H_
#define GLSCROLLAREA_H_


#include <QAbstractScrollArea>
#include "qicore/qicore.hpp"

namespace qicore {
namespace ui {
    
class QICORE_EXPORT GLScrollArea : public QAbstractScrollArea
{
public:
    GLScrollArea(QWidget * parent) : QAbstractScrollArea(parent){}
    ~GLScrollArea(){}
protected:
    void resizeEvent(QResizeEvent * event) override;
    void paintEvent(QPaintEvent *event) override;
};

}
}

#endif