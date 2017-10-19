#include "rocore/graphics/GraphicLine.hpp"

using namespace rocore::graphics;

void GraphicLine::Draw(GraphicLayer* layer)
{
    /*
    layer->AddOperation(GraphicPaintOperationLine, 2, width_);
    layer->AddVertex(start_.x,start_.y);
    layer->AddVertex(end_.x, end_.y);
*/

    auto normal = getNormal();

    auto pointA = glm::highp_dvec2(start_.x,start_.y) - (normal * width_);
    auto pointB = glm::highp_dvec2(start_.x,start_.y) + (normal * width_);
    auto pointC = glm::highp_dvec2(end_.x,end_.y) - (normal * width_);
    auto pointD = glm::highp_dvec2(end_.x,end_.y) + (normal * width_);


    layer->AddOperation(GraphicPaintOperationLine, 4, width_);
    layer->AddVertex(pointA.x,pointA.y);
    layer->AddVertex(pointB.x, pointB.y);
    layer->AddVertex(pointC.x, pointC.y);
    layer->AddVertex(pointD.x, pointD.y);

}

glm::highp_dvec2 GraphicLine::getNormal() const {
    double dx = end_.x - start_.x;
    double dy = end_.y - start_.y;

    return glm::normalize(glm::highp_dvec2(-dy, dx));
}

BoundingBox GraphicLine::GetBoundingBox()
{
    return BoundingBox(start_,0,0);
}