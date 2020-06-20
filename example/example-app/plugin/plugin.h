#pragma once

#include "plugin_api.h"

class IPlugin {
public:
	virtual ~IPlugin() = default;
	virtual int GetID() = 0;
};

extern "C" PLUGIN_API IPlugin* CreatePlugin();
