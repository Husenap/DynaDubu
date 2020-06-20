#pragma once

#include <string>
#include <unordered_map>

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

	void* GetSymbol(const char* symbol);

	std::string mName;
	void* mHandle;

	std::unordered_map<std::string, void*> mSymbolCache;

public:
	template <typename T, typename ...Args>
	T (*GetFunction(const char* functionName))(Args...) {
		return reinterpret_cast<T(*)(Args...)>(GetSymbol(functionName));
	}
	
	template <typename T, typename ...Args>
	T Call(const char* functionName, Args... args){
		return GetFunction<T, Args...>(functionName)(args...);
	}

};

}  // namespace dd
