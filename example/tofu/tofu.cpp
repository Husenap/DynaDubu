#include "../example-app/plugin/plugin.h"

class TofuPlugin : public IPlugin {
public:
	virtual ~TofuPlugin() override {}
	int GetID() override { return 420; }
};

extern "C" IPlugin* CreatePlugin() {
	return new TofuPlugin();
}
