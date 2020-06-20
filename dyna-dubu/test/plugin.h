#pragma once

#ifdef WIN32
#	ifdef PLUGIN_EXPORT
#		define PLUGIN_API __declspec(dllexport)
#	else
#		define PLUGIN_API __declspec(dllimport)
#	endif
#else
#	ifdef PLUGIN_EXPORT
#		define PLUGIN_API __attribute__((visibility("default")))
#	else
#		define PLUGIN_API
#	endif
#endif

struct ITofu {
	virtual ~ITofu()    = default;
	virtual void Cook() = 0;
	virtual void Eat()  = 0;
};

#ifdef __cplusplus
extern "C" {
#endif

PLUGIN_API const char* name();

PLUGIN_API int magic(int a, int b);

PLUGIN_API ITofu* CreateTofu();

#ifdef __cplusplus
}
#endif
