//
// Created by mroszko on 3/28/2017.
//

#include <QFile>
#include <QIODevice>
#include "rocore/projects/Project.hpp"
#include "rapidjson/prettywriter.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/stringbuffer.h"


using namespace rocore::projects;

Project::Project(QString name)
{
	name_ = name;
}

template <typename Writer>
void Project::Serialize(Writer& writer) const {
	writer.StartObject();

	writer.String("name");
	writer.String(name_.toStdString());


	writer.EndObject();
}

void Project::Deserialize(rapidjson::Document& document) {
	if(document.IsObject()) {
		auto name = document.FindMember("name");

		name_ = ( (name != document.MemberEnd() && name->value.IsString())
				  ? name->value.GetString() : throw ProjectDeserializeException("Missing name"));


		auto filesIt = document.FindMember("files");

		if(filesIt != document.MemberEnd()) {

		}
	}
}

void Project::SaveToFile(QString filename) {
	rapidjson::StringBuffer buffer;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);

	Serialize(writer);

	const char* output = buffer.GetString();

	QFile file(filename);
	if (!file.open(QIODevice::WriteOnly))
		return;

	file.write(output);
	file.flush();
	file.close();
}

void Project::LoadFromFile(QString filename) {
	rapidjson::Document document;

	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly))
		return;

	auto fileContents = file.readAll();

	document.Parse(fileContents.toStdString());

	if(document.HasParseError()) {
		throw ProjectDeserializeException("Error parsing project file format");
	}

	if( !document.IsObject() ) {
		throw ProjectDeserializeException("Missing root object");
	}

	Deserialize(document);
}