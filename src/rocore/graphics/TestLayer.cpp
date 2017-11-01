//
// Created by mroszko on 10/16/2017.
//

#include "rocore/graphics/TestLayer.hpp"
#include "rocore/graphics/GraphicLine.hpp"
#include "rocore/graphics/GraphicCircle.hpp"
#include "rocore/graphics/GraphicArc.hpp"
#include "rocore/graphics/GraphicText.hpp"
#include "rocore/Units.hpp"

using namespace rocore::graphics;


TestLayer::TestLayer() : GraphicLayer(Colors::Blue) {

	depth_ = -5.0;
/*
    Point p3;
    p3.x = 0;
    p3.y = 0;
    GraphicRectangle* gral2 = new GraphicRectangle(p3, Units::InchesToInternalUnits(2), Units::InchesToInternalUnits(1));

    Point p4;
    p4.x = Units::InchesToInternalUnits(1.4);
    p4.y = Units::InchesToInternalUnits(2.24);
    GraphicRectangle* gral3 = new GraphicRectangle(p4,Units::InchesToInternalUnits(0.5), Units::InchesToInternalUnits(0.5));
*/

	Point p1;
	p1.x = 0;
	p1.y = 0;
	Point p2;
	p2.x = 0;
	p2.y = Units::InchesToInternalUnits(2);

	GraphicLine* lineTest1 = new GraphicLine(p1,p2, Units::MilsToInternalUnits(40));

	p1.x = 0;
	p1.y = 0;
	p2.x = Units::InchesToInternalUnits(2);
	p2.y = Units::InchesToInternalUnits(2);

	GraphicLine* lineTest2 = new GraphicLine(p1,p2, Units::MilsToInternalUnits(40));

	Point p5;
	p5.x = Units::InchesToInternalUnits(0);
	p5.y = Units::InchesToInternalUnits(0);
	GraphicCircle* circleTest1 = new GraphicCircle(p5,Units::MilsToInternalUnits(100));

	Point p11;
	p11.x = Units::InchesToInternalUnits(1);
	p11.y = Units::InchesToInternalUnits(1);
	GraphicCircle* circleTest2 = new GraphicCircle(p11,Units::MilsToInternalUnits(100));

	Point p6;
	p6.x = Units::InchesToInternalUnits(2);
	p6.y = Units::InchesToInternalUnits(2);
	GraphicArc* arcTest1 = new GraphicArc(p6,Units::MilsToInternalUnits(300),M_PI/4, M_PI/2, Units::MilsToInternalUnits(40));

	Point p8;
	p8.x = Units::InchesToInternalUnits(1);
	p8.y = Units::InchesToInternalUnits(2);
	GraphicArc* arcTest2 = new GraphicArc(p8,Units::MilsToInternalUnits(300),M_PI/4, M_PI/2);

	Point p7;
	p7.x = 15;
	p7.y = 10;
	GraphicText* textTest = new GraphicText(p7,"TESTING",12);

	AddItem(lineTest1);
	AddItem(lineTest2);
	AddItem(circleTest1);
	AddItem(circleTest2);
	AddItem(arcTest1);
	AddItem(arcTest2);
}