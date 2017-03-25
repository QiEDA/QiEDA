//
// Created by mroszko on 3/24/2017.
//

#ifndef ROEDA_GERBEREXCEPTION_HPP
#define ROEDA_GERBEREXCEPTION_HPP

#include <stdexcept>

class GerberException : public std::exception {
	std::string _msg;
public:
	GerberException(std::string msg) : exception(), _msg(msg) {}

	virtual const char* what() const throw()
	{
		return _msg.c_str();
	}
};

#endif //ROEDA_GERBEREXCEPTION_HPP
