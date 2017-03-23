#ifndef GLSCROLLAREA_H_
#define GLSCROLLAREA_H_


#include <QAbstractScrollArea>
#include "rocore/rocore.hpp"

namespace rocore {
namespace ui {
    
class ROCORE_EXPORT GLScrollArea : public QAbstractScrollArea
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