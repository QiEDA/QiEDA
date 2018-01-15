//
// Created by mroszko on 1/15/2018.
//

#ifndef ROEDA_SETTINGS_HPP
#define ROEDA_SETTINGS_HPP

#include <QSettings>
#include "rocore/rocore.hpp"

namespace rocore {
namespace constants {
	const int MaxRecentProjects = 5;
}

class ROCORE_EXPORT Settings {
public:
	static Settings& instance();

	void     write(const QString & key, const QVariant & variant);
	QVariant read (const QString & key) const;

	void setDefaultDirectoryPath(const QString& path);
	QString getDefaultDirectoryPath();

	void appendToRecentProjects(const QString& path);
	QStringList getRecentProjects();

private:
	Settings(const QString & path) :
			settings(path, QSettings::IniFormat)
	{}

	QSettings settings;
};
}

#endif //ROEDA_SETTINGS_HPP
