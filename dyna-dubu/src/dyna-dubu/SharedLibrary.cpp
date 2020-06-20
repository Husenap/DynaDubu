#include "SharedLibrary.h"

#ifdef WIN32
#	include <direct.h>
#	include <windows.h>
#else
#	include <dlfcn.h>
#endif

#include <iostream>
#include <string>

#include <chrono>
#include <filesystem>

namespace dd {

SharedLibrary::SharedLibrary(const char* libraryName) {
	mName          = libraryName;
	mHandle        = nullptr;
	mLastWriteTime = -1;

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

bool SharedLibrary::NeedsToReload() const {
	return GetLastWriteTime() != mLastWriteTime;
}

void SharedLibrary::Load() {
#ifdef WIN32
	mPath   = mName + ".dll";
	mHandle = static_cast<void*>(LoadLibrary(TEXT(mPath.c_str())));
	if (mHandle == nullptr) {
		std::cerr << "Cannot load library[" << GetLastError() << "]: " << mPath << std::endl;
	} else {
		std::cout << "Successfully loaded library: " << mPath << std::endl;
	}
#else
#	ifdef __APPLE__
	mPath   = std::string("./lib") + mName + ".dylib";
#	else
	mPath = std::string("./lib") + mName + ".so";
#	endif
	mHandle = dlopen(mPath.c_str(), RTLD_LAZY);
	if (mHandle == nullptr) {
		std::cerr << "Cannot load library[" << dlerror() << "]: " << mPath << std::endl;
	} else {
		std::cout << "Successfully loaded library: " << mPath << std::endl;
	}
#endif

	mLastWriteTime = GetLastWriteTime();
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

long SharedLibrary::GetLastWriteTime() const {
	try {
		if (!std::filesystem::exists(mPath)) {
			return -1;
		}
		return std::filesystem::last_write_time(mPath).time_since_epoch().count();
	} catch (const std::filesystem::filesystem_error& err) {
		std::cout << "Failed to get time for library: " << mPath << std::endl;
		std::cout << "filesystem_error: " << err.what() << std::endl;
	}

	return -1;
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

