
#ifndef PLUGIN_API
#ifdef WIN32
#	ifdef PLUGIN_IMPORT
#		define PLUGIN_API __declspec(dllimport)
#	else
#		define PLUGIN_API __declspec(dllexport)
#	endif
#else
#	ifdef PLUGIN_IMPORT
#		define PLUGIN_API
#	else
#		define PLUGIN_API __attribute__((visibility("default")))
#	endif
#endif
#endif
