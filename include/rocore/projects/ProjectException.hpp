//
// Created by mroszko on 1/6/2018.
//

#ifndef ROEDA_PROJECTEXCEPTION_HPP
#define ROEDA_PROJECTEXCEPTION_HPP

#include "rocore/BaseException.hpp"

namespace rocore {
namespace projects {
class ProjectDeserializeException : public BaseException {

public:
	ProjectDeserializeException(std::string msg) : BaseException(msg) {}
};
}
}

#endif //ROEDA_PROJECTEXCEPTION_HPP
