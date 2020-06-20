#define PLUGIN_EXPORT
#include "../plugin.h"

#include <iostream>

struct Mina : public ITofu {
	virtual ~Mina() = default;
	void Cook() override { std::cout << "Mina is cooking some tofu" << std::endl; }
	void Eat() override { std::cout << "Mina is eating some tofu" << std::endl; }
	void Release() override { std::cout << "Mina is releasing some tofu" << std::endl; }
};

#ifdef __cplusplus
extern "C" {
#endif

const char* name() {
	return "mina";
}

int magic(int a, int b){
	return a + b;
}

ITofu* CreateTofu() {
	return new Mina;
}

#ifdef __cplusplus
}
#endif

