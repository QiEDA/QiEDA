//
// Created by mroszko on 1/6/2018.
//

#ifndef ROEDA_BASEEXCEPTION_HPP
#define ROEDA_BASEEXCEPTION_HPP

#include <stdexcept>

namespace rocore {
class BaseException : public std::exception {
	std::string _msg;
public:
	BaseException(std::string msg) : exception(), _msg(msg) {}

	virtual const char *what() const throw() {
		return _msg.c_str();
	}
};
}

#endif //ROEDA_BASEEXCEPTION_HPP
