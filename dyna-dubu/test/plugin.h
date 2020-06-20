#pragma once

#ifdef PLUGIN_EXPORT
#	ifdef WIN32
#		define PLUGIN_API __declspec(dllexport)
#	else
#		define PLUGIN_API __attribute__((visibility("default")))
#	endif
#else
#	ifdef WIN32
#		define PLUGIN_API __declspec(dllimport)
#	else
#		define PLUGIN_API
#	endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

PLUGIN_API const char* name();

PLUGIN_API int magic(int a, int b);

struct ITofu {
	virtual ~ITofu()    = default;
	virtual void Cook() = 0;
	virtual void Eat()  = 0;
};

PLUGIN_API ITofu* CreateTofu();

#ifdef __cplusplus
}
#endif

