#pragma once

#include <string>
#include <unordered_map>

namespace dd {

class SharedLibrary {
public:
	SharedLibrary(const char* libraryName);
	~SharedLibrary();

	template <typename T, typename ...Args>
	T (*GetFunction(const char* functionName))(Args...) {
		return reinterpret_cast<T(*)(Args...)>(GetSymbol(functionName));
	}

	void Reload();

	bool IsLoaded() const;

private:
	void Load();
	void Unload();

	void* GetSymbol(const char* symbol);

	std::string mName;
	void* mHandle;

	std::unordered_map<std::string, void*> mSymbolCache;
};

}  // namespace dd
