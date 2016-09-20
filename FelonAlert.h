#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#ifndef FELON_H
#define FELON_H

class Felon {
public:
	// Example : char* = Caesar.encrypt(Felon.CallWMIC("wmic bios get serialnumber"));
	char* CallWMIC(char* cmd) {
		char buffer[128];
		std::string result;
		std::shared_ptr<FILE> pipe(_popen(cmd, "r"), _pclose);
		if (!pipe)	throw std::runtime_error("Failed identification");
		while (!feof(pipe.get())) {
			if (fgets(buffer, 128, pipe.get()) != NULL)
				result += buffer;
		}
		char *cstr = new char[result.length() + 1];
		strcpy(cstr, result.c_str());
		return cstr;
	}
};
#endif