//
// Created by mroszko on 9/25/2016.
//

#include "rocore/graphics/GridLayer.hpp"
#include "rocore/Units.hpp"

using namespace rocore::graphics;

bool GridLayer::Prepare(GLPainter* painter) {

    if(dirty_)
    {
        /* square grid so min and max are identical for X and Y */
        float max = Units::MetersToInternalUnits(1);
        float majorIncrement  = Units::MillimetersToInternalUnits(10);

        //total lines
        long axisHalfLines =  std::floor(max/majorIncrement);
        long axisHalfVerts = axisHalfLines*2;
        long totalVerts = axisHalfVerts*4;

        vertBuffer_.reserve(totalVerts);

        max -= majorIncrement;  //decrement the max by the increment to "cap" off the ends

        AddOperation(GraphicPaintOperationLine,totalVerts);
        for(int i = 0;i < axisHalfLines; i++) {
            float pos = i*majorIncrement;
            AddVertex(pos,max);
            AddVertex(pos,-max);

            AddVertex(-pos,max);
            AddVertex(-pos,-max);

            AddVertex(max,pos);
            AddVertex(-max,pos);

            AddVertex(max,-pos);
            AddVertex(-max,-pos);
        }

        dirty_ = false;
        return true;
    }
    return false;
}