//
// Created by mroszko on 7/24/2017.
//

#ifndef ROEDA_GERBERDOCUMENTVIEW_HPP
#define ROEDA_GERBERDOCUMENTVIEW_HPP

#include "rocore/ui/DocumentView.hpp"
#include "rocore/graphics/GraphicLayer.hpp"


namespace rocore {
namespace ui {

class ROCORE_EXPORT GerberDocumentView : public DocumentView {

Q_OBJECT
public:
	GerberDocumentView(QWidget* parent = 0, Qt::WindowFlags flags = 0);

	void AddLayer(rocore::graphics::GraphicLayer* layer)
	{
		glArea_->AddLayer(layer);
	}
};

}
}

#endif //ROEDA_GERBERDOCUMENTVIEW_HPP
