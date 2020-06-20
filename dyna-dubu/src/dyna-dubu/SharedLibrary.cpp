#include "SharedLibrary.h"

#include <iostream>

namespace dd {

SharedLibrary::SharedLibrary(const char* libraryName) {
#ifdef WIN32
	std::cout << "Constructor Win32" << std::endl;
#else
	std::cout << "Constructor Unix" << std::endl;
#endif
}

SharedLibrary::~SharedLibrary() {
#ifdef WIN32
	std::cout << "Destructor Win32" << std::endl;
#else
	std::cout << "Destructor Unix" << std::endl;
#endif
}

}  // namespace dd

