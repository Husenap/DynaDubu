#include "SharedLibrary.h"

#include <iostream>

namespace dd {

SharedLibrary::SharedLibrary(const char* libraryName) {
	std::cout << "Constructor" << std::endl;
}

SharedLibrary::~SharedLibrary() {
	std::cout << "Destructor" << std::endl;
}

}  // namespace dd

