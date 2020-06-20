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
	mSymbolCache.clear();
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
		std::cerr << "Cannot load library[" << GetLastError() << "]: " << libraryToLoad << std::endl;
	} else {
		std::cout << "Successfully loaded library: " << libraryToLoad << std::endl;
	}
#else
#	ifdef __APPLE__
	std::string libraryToLoad = std::string("./lib") + mName + ".dylib";
#	else
	std::string libraryToLoad = std::string("./lib") + mName + ".so";
#	endif
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

void* SharedLibrary::GetSymbol(const char* symbol) {
	void* symbolHandle = nullptr;

	auto it = mSymbolCache.find(symbol);
	if (it != mSymbolCache.end()) {
		return it->second;
	}

#ifdef WIN32
	symbolHandle = GetProcAddress(static_cast<HINSTANCE>(mHandle), symbol);
	if (symbolHandle == nullptr) {
		std::cerr << "Cannot load symbol " << symbol << ": " << GetLastError() << std::endl;
	}
#else
	dlerror();
	symbolHandle           = dlsym(mHandle, symbol);
	const char* dlsymError = dlerror();
	if (dlsymError != nullptr) {
		std::cerr << "Cannot load symbol " << symbol << ": " << dlsymError << std::endl;
	}
#endif

	if (symbolHandle != nullptr) {
		mSymbolCache[symbol] = symbolHandle;
	}

	return symbolHandle;
}

}  // namespace dd

