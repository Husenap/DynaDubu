#pragma once

#include <string>

namespace dd {

class SharedLibrary {
public:
	SharedLibrary(const char* libraryName);
	~SharedLibrary();

	void Reload();

	bool IsLoaded() const;

private:
	void Load();
	void Unload();

	std::string mName;
	void* mHandle;
};

}  // namespace dd
