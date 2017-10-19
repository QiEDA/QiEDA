//
// Created by mroszko on 9/25/2016.
//

#include "rocore/graphics/GraphicRawLine.hpp"
#include "rocore/graphics/GridLayer.hpp"
#include "rocore/Units.hpp"

using namespace rocore::graphics;

GridLayer::GridLayer() : GraphicLayer(Colors::DarkGray) {
    updateGrid();
}

void GridLayer::updateGrid() {
    /* square grid so min and max are identical for X and Y */
    float max = Units::MetersToInternalUnits(1);
    float majorIncrement  = Units::MillimetersToInternalUnits(10);

    //total lines
    long axisHalfLines =  std::floor(max/majorIncrement);

    max -= majorIncrement;  //decrement the max by the increment to "cap" off the ends

    Point p1;
    Point p2;
    double width = 0.00005;
	GraphicRawLine* line = nullptr;
    for(int i = 0;i < axisHalfLines; i++) {
        float pos = i*majorIncrement;

        p1.x = pos;
        p1.y = max;
        p2.x = pos;
        p2.y = -max;
        line = new GraphicRawLine(p1,p2,width);
        AddItem(line);

        p1.x = -pos;
        p1.y = max;
        p2.x = -pos;
        p2.y = -max;
        line = new GraphicRawLine(p1,p2,width);
        AddItem(line);

        p1.x = max;
        p1.y = pos;
        p2.x = -max;
        p2.y = pos;
        line = new GraphicRawLine(p1,p2,width);
        AddItem(line);

        p1.x = max;
        p1.y = -pos;
        p2.x = -max;
        p2.y = -pos;
        line = new GraphicRawLine(p1,p2,width);
        AddItem(line);
    }

    dirty_ = true;
}