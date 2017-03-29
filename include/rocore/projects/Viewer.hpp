//
// Created by mroszko on 3/28/2017.
//

#ifndef ROEDA_VIEWERPROJECT_HPP
#define ROEDA_VIEWERPROJECT_HPP

#include <string>
#include "rocore/rocore.hpp"
#include "rocore/projects/Base.hpp"

namespace rocore {
namespace projects {

class ROCORE_EXPORT Viewer: public Base {
public:
	Viewer(QString name) : Base(name)
	{

	}
};

}
}

#endif //ROEDA_VIEWERPROJECT_HPP
