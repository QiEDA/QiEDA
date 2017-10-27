#include "rocore/graphics/GraphicDocument.hpp"
#include "rocore/graphics/GridLayer.hpp"

using namespace rocore::graphics;

GraphicDocument::GraphicDocument(){
	gridLayer_ = new GridLayer();
	AddLayer(gridLayer_);
}

GraphicDocument::~GraphicDocument(){

}

void GraphicDocument::AddLayer(GraphicLayer* layer)
{
	layers_.push_back(layer);
}

void GraphicDocument::RemoveLayer(GraphicLayer* layer)
{
	layers_.remove(layer);
}