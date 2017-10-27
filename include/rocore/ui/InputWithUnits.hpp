//
// Created by mroszko on 10/26/2017.
//

#ifndef ROEDA_UNITCONTROLLEDINPUT_HPP
#define ROEDA_UNITCONTROLLEDINPUT_HPP

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <vector>
#include "rocore/rocore.hpp"
#include "rocore/Units.hpp"

namespace rocore {
namespace ui {
	class InputWithUnits : public QWidget {
	Q_OBJECT

	public:
		explicit InputWithUnits(double value, Units::Type unit, QWidget *parent = Q_NULLPTR);

	public slots:
		void unitsChanged(int);
		void inputEdited(const QString &text);

	private:
		void setUnitBoxCurrent(Units::Type unit);
		void setValue(double value);
		struct unitDefinition
		{
			Units::Type unit;
			QString str;
		};

		static const std::vector<struct unitDefinition> unitDefinitions_;

		QLineEdit valueBox_;
		QComboBox unitBox_;

		double value_;
		Units::Type unit_;
	};
}
}

#endif //ROEDA_UNITCONTROLLEDINPUT_HPP
