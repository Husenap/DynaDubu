#pragma once

namespace dd {

class SharedLibrary {
public:
	SharedLibrary(const char* libraryName);
	~SharedLibrary();

private:
	void* mHandle;
};

}  // namespace dd
