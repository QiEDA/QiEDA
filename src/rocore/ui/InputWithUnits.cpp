//
// Created by mroszko on 10/26/2017.
//
#include <stdexcept>
#include <QHBoxLayout>
#include <QDoubleValidator>
#include "rocore/ui/InputWithUnits.hpp"

using namespace rocore;
using namespace rocore::ui;


const std::vector<struct InputWithUnits::unitDefinition> InputWithUnits::unitDefinitions_ = {
		{rocore::Units::Type::Mils, tr("mil")},
		{rocore::Units::Type::Millimeters, tr("mm")},
		{rocore::Units::Type::Inches, tr("inch")}
};

InputWithUnits::InputWithUnits(double value, Units::Type unit, QWidget* parent)
		: QWidget(parent), unit_(unit)
{
	QHBoxLayout *layout = new QHBoxLayout(this);

	layout->addWidget(&valueBox_);
	layout->addWidget(&unitBox_);

	unitBox_.setValidator(new QDoubleValidator());

	int idx = 0;
	for(auto unitDef : unitDefinitions_) {
		unitBox_.addItem(unitDef.str);
		if(unitDef.unit == unit_) {
			unitBox_.setCurrentIndex(idx);
		}
		idx++;
	}

	connect(&unitBox_, SIGNAL(activated(int)),
			this, SLOT(unitsChanged(int)));

	connect(&valueBox_, SIGNAL(textEdited(const QString&)),
			this, SLOT(inputEdited(const QString&)));


	setValue(value);
	setLayout(layout);
}

void InputWithUnits::setValue(double value) {
	value_ = value;
	valueBox_.setText(QString::number(value_));
}

void InputWithUnits::unitsChanged(int index)
{
	if(index >= (int)unitDefinitions_.size()) {
		throw std::invalid_argument("index did not exist in unit definitions");
	}

	double newValue = 0;
	auto unitDef = unitDefinitions_[index];
	newValue = Units::Convert(value_, unit_, unitDef.unit);

	setValue(newValue);
}

void InputWithUnits::inputEdited(const QString &text) {
	bool ok = false;
	double result = text.toDouble(&ok);

	if(!ok) {
		//exception, should happen as we double validate....
	}
	else {
		value_ = result;
	}

}