#define PLUGIN_EXPORT
#include "../plugin.h"

#include <iostream>

struct Dubu : public ITofu {
	virtual ~Dubu() = default;
	void Cook() override { std::cout << "Dubu is cooking some tofu" << std::endl; }
	void Eat() override { std::cout << "Dubu is eating some tofu" << std::endl; }
	void Release() override { std::cout << "Dubu is releasing some tofu" << std::endl; }
};

#ifdef __cplusplus
extern "C" {
#endif

const char* name() {
	return "dubu";
}

int magic(int a, int b) {
	return a * b;
}

ITofu* CreateTofu() {
	return new Dubu;
}

#ifdef __cplusplus
}
#endif

