#include "SharedLibrary.h"

#ifdef WIN32
#	include <direct.h>
#	include <windows.h>
#else
#	include <dlfcn.h>
#endif

#include <iostream>
#include <string>

namespace dd {

SharedLibrary::SharedLibrary(const char* libraryName) {
	mName   = libraryName;
	mHandle = nullptr;

	Load();
}

SharedLibrary::~SharedLibrary() {
	Unload();
}

void SharedLibrary::Reload() {
	Unload();
	Load();
}

bool SharedLibrary::IsLoaded() const {
	return mHandle != nullptr;
}

void SharedLibrary::Load() {
#ifdef WIN32
	std::string libraryToLoad = mName + ".dll";
	mHandle                   = static_cast<void*>(LoadLibrary(TEXT(libraryToLoad.c_str())));
	if (mHandle == nullptr) {
		std::cerr << "Cannot load library: " << libraryToLoad << std::endl;
	} else {
		std::cout << "Successfully loaded library: " << libraryToLoad << std::endl;
	}
#else
	std::string libraryToLoad = std::string("./lib") + mName + ".so";
	mHandle                   = dlopen(libraryToLoad.c_str(), RTLD_LAZY);
	if (mHandle == nullptr) {
		std::cerr << "Cannot load library[" << dlerror() << "]: " << libraryToLoad << std::endl;
	} else {
		std::cout << "Successfully loaded library: " << libraryToLoad << std::endl;
	}
#endif
}

void SharedLibrary::Unload() {
	if (mHandle != nullptr) {
#ifdef WIN32
		FreeLibrary(static_cast<HINSTANCE>(mHandle));
#else
		dlclose(mHandle);
#endif
		mHandle = nullptr;
	}
}

}  // namespace dd

