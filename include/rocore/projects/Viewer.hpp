//
// Created by mroszko on 3/28/2017.
//

#ifndef ROEDA_VIEWERPROJECT_HPP
#define ROEDA_VIEWERPROJECT_HPP

#include <string>
#include "rocore/rocore.hpp"
#include "rocore/projects/Project.hpp"

namespace rocore {
namespace projects {

class ROCORE_EXPORT Viewer: public Project {
public:
	Viewer(QString name) : Project(name)
	{

	}
};

}
}

#endif //ROEDA_VIEWERPROJECT_HPP
