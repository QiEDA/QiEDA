//
// Created by mroszko on 9/25/2016.
//

#include "rocore/graphics/GraphicGrid.hpp"
#include "rocore/graphics/GridLayer.hpp"
#include "rocore/Units.hpp"

using namespace rocore::graphics;

GridLayer::GridLayer() : GraphicLayer(Colors::DarkGray) {
    depth_ = -5;
    GraphicGrid* gridGraphic = new GraphicGrid();
    AddItem(gridGraphic);
}