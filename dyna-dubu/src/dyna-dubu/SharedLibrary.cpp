#include "SharedLibrary.h"

#ifdef WIN32
#	include <direct.h>
#	include <windows.h>
#else
#	include <dlfcn.h>
#	include <sys/types.h>
#endif

#include <iostream>

namespace dd {

SharedLibrary::SharedLibrary(const char* libraryName) {
	mHandle = nullptr;

#ifdef WIN32
	std::string libraryToLoad = std::string(libraryName) + ".dll";
	mHandle                   = static_cast<void*>(LoadLibrary(TEXT(libraryToLoad.c_str())));
	if (mHandle == nullptr) {
		std::cerr << "Cannot load library: " << libraryToLoad << std::endl;
	}
#else
	std::string libraryToLoad = std::string("lib") + libraryName + ".so";
	mHandle                   = dlopen(libraryToLoad.c_str(), RTLD_LAZY);
	if (mHandle == nullptr) {
		std::cerr << "Cannot load library: " << libraryToLoad << std::endl;
	}
#endif
}

SharedLibrary::~SharedLibrary() {
	if (mHandle != nullptr) {
#ifdef WIN32
		FreeLibrary(static_cast<HINSTANCE>(mHandle));
#else
		dlclose(mHandle);
#endif
	}
}

}  // namespace dd

