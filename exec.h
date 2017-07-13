#ifndef EXEC_H
#define EXEC_H

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

using std::string;
using std::array;
using std::shared_ptr;
using std::runtime_error;

string exec(const char* cmd) { 
	array<char, 128> buffer;
	string result;
	shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
	if (!pipe)
		throw runtime_error("popen failed!");
	while(!feof(pipe.get())) {
		if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
			result += buffer.data();
    }

	return result;
}

#endif // EXEC_H
