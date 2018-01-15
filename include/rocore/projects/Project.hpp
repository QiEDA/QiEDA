//
// Created by mroszko on 3/28/2017.
//

#ifndef ROEDA_PROJECT_HPP
#define ROEDA_PROJECT_HPP

#include <string>
#include <QObject>
#include "rocore/rocore.hpp"
#include "rocore/projects/ProjectException.hpp"
#include "rapidjson/document.h"

namespace rocore {
namespace projects {
class ROCORE_EXPORT Project : public QObject {
Q_OBJECT

private:
	std::string filename_;
	bool dirty_ = false;
	QString name_;
	QString file_;

signals:
	void DirtyChanged(bool isDirty);
	void NameChanged(QString name);

public:
	Project(QString name = "");

	void SetName(QString name) {
		name_ = name;
		dirty_ = true;

		emit DirtyChanged(dirty_);
		emit NameChanged(name);
	}

	QString GetName() {
		return name_;
	}

	bool IsDirty() const {
		return dirty_;
	}

	void LoadFromFile(QString filename);

	void SaveToFile(QString filename);

protected:
	template <typename Writer>
	void Serialize(Writer& writer) const;

	void Deserialize(rapidjson::Document& document);
};
}
}

#endif //ROEDA_PROJECTBASE_HPP
