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

	bool NeedsToReload() const;

public:
	template <typename T, typename ...Args>
	T (*GetFunction(const char* functionName))(Args...) {
		return reinterpret_cast<T(*)(Args...)>(GetSymbol(functionName));
	}
	
	template <typename T, typename ...Args>
	T Call(const char* functionName, Args... args){
		return GetFunction<T, Args...>(functionName)(args...);
	}

private:
	void Load();
	void Unload();

	long GetLastWriteTime() const;
	
	void* GetSymbol(const char* symbol);

	std::string mName;
	std::string mPath;
	long mLastWriteTime;
	void* mHandle;

	std::unordered_map<std::string, void*> mSymbolCache;

};

}  // namespace dd
