//
// Created by mroszko on 1/6/2018.
//

#ifndef ROEDA_PROJECTLOADER_HPP
#define ROEDA_PROJECTLOADER_HPP

#include "rocore/rocore.hpp"
#include "rocore/projects/Project.hpp"
#include "rocore/projects/ProjectException.hpp"
#include <memory>

namespace rocore {
namespace projects {

class ROCORE_EXPORT Loader{

public:
	Loader();

	static std::unique_ptr<Project> Load();
};

}
}

#endif //ROEDA_PROJECTLOADER_HPP
