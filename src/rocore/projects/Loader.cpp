//
// Created by mroszko on 1/6/2018.
//

#include "rocore/projects/Loader.hpp"
#include "util/make_unique.hpp"
#include "rapidjson/document.h"

using namespace rocore::projects;

std::unique_ptr<Project> Loader::Load() {
	rapidjson::Document document;

	document.Parse("test.roproj");

	auto proj = std::make_unique<Project>();
	if(document.HasParseError()) {
		throw ProjectDeserializeException("Error parsing project file format");
	}

	if( !document.IsObject() ) {
		throw ProjectDeserializeException("Error parsing project file format");
	}



	return proj;
}