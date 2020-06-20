#include <iostream>
#include <thread>
#include <chrono>
#include <memory>

#define PLUGIN_IMPORT
#include "plugin/plugin.h"

#include <dyna-dubu/SharedLibrary.h>

void DoWork(){
	dd::SharedLibrary lib("tofu");

	std::unique_ptr<IPlugin> plugin;

	std::cout << "Thread id: " << std::this_thread::get_id() << std::endl;

	int tick = 0;

	while(true){
		if(!lib.IsLoaded() || lib.NeedsToReload()){
			std::cout << "Loading library!" << std::endl;
			lib.Reload();
		}

		++tick;

		if(lib.IsLoaded()){
			if(!plugin){
				plugin.reset(lib.Call<IPlugin*>("CreatePlugin"));
			}

			//std::cout << "Plugin ID: " << plugin->GetID() << std::endl;
		}else{
			std::cout << "Plugin is not loaded" << std::endl;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

int main(){
	std::thread t(DoWork);

	std::cout << "Thread id: " << std::this_thread::get_id() << std::endl;

	if(t.joinable()){
		t.join();
	}

	return 0;
}
