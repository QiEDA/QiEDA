//
// Created by mroszko on 3/28/2017.
//

#ifndef ROEDA_MDIWINDOW_HPP
#define ROEDA_MDIWINDOW_HPP

#include <QMdiSubWindow>
#include "rocore/ui/GLWidget.hpp"

namespace rocore {
namespace ui {

class ROCORE_EXPORT DocumentView : public QMdiSubWindow {

	Q_OBJECT
public:
	DocumentView(QWidget* parent = 0, Qt::WindowFlags flags = 0);

private:
	rocore::ui::GLWidget* glarea_;
};

}
}

#endif //ROEDA_MDIWINDOW_HPP
