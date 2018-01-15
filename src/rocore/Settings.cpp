//
// Created by mroszko on 1/15/2018.
//

#include "rocore/Settings.hpp"

#include <QApplication>
#include <QDir>
#include <QStandardPaths>

using namespace rocore;

const QString DEFAULT_DIR_KEY("default_dir");
const QString RECENT_PROJECTS("recent_projects");

Settings& Settings::instance() {
	static Settings s(QDir(QStandardPaths::writableLocation(QStandardPaths::DataLocation)).filePath("settings.ini"));
	return s;
}

void Settings::write(const QString & key, const QVariant & variant)
{
	settings.setValue(key, variant);
}

QVariant Settings::read(const QString & key) const
{
	return settings.value(key);
}

void Settings::setDefaultDirectoryPath(const QString& path) {
	settings.setValue(DEFAULT_DIR_KEY, path);
}

QString Settings::getDefaultDirectoryPath() {
	return settings.value(DEFAULT_DIR_KEY).toString();
}


void Settings::appendToRecentProjects(const QString& path) {
	QStringList files = settings.value(RECENT_PROJECTS).toStringList();

	files.removeAll(path);
	files.prepend(path);

	while(files.size() > rocore::constants::MaxRecentProjects) {
		files.removeLast();
	}

	settings.setValue(RECENT_PROJECTS, files);
}

QStringList Settings::getRecentProjects() {
	return settings.value(RECENT_PROJECTS).toStringList();
}