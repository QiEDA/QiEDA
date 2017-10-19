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
	p2.y = Units::InchesToInternalUnits(8);

	GraphicLine* lineTest1 = new GraphicLine(p1,p2, Units::MilsToInternalUnits(40));

	p1.x = 0;
	p1.y = 0;
	p2.x = Units::InchesToInternalUnits(8);
	p2.y = Units::InchesToInternalUnits(8);

	GraphicLine* lineTest2 = new GraphicLine(p1,p2, Units::MilsToInternalUnits(40));

	Point p5;
	p5.x = Units::InchesToInternalUnits(0);
	p5.y = Units::InchesToInternalUnits(0);
	GraphicCircle* gral4 = new GraphicCircle(p5,Units::MilsToInternalUnits(300));

	Point p11;
	p11.x = Units::InchesToInternalUnits(1);
	p11.y = Units::InchesToInternalUnits(1);
	GraphicCircle* gral111 = new GraphicCircle(p11,Units::MilsToInternalUnits(300));

	Point p6;
	p6.x = 20;
	p6.y = 2;
	GraphicArc* gral5 = new GraphicArc(p6,4,0,2);

	Point p7;
	p7.x = 15;
	p7.y = 10;
	GraphicText* gral6 = new GraphicText(p7,"TESTING",12);

	AddItem(lineTest1);
	AddItem(lineTest2);
	AddItem(gral4);
	AddItem(gral111);
	AddItem(gral5);
	AddItem(gral6);
}