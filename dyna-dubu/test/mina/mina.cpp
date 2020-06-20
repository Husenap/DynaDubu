#include "../plugin.h"

#include <iostream>

struct Mina : public ITofu {
	virtual ~Mina() { std::cout << "Mina is releasing some tofu" << std::endl; }
	virtual void Cook() { std::cout << "Mina is cooking some tofu" << std::endl; }
	virtual void Eat() { std::cout << "Mina is eating some tofu" << std::endl; }
};

#ifdef __cplusplus
extern "C" {
#endif

const char* name() {
	return "mina";
}

int magic(int a, int b) {
	return a + b;
}

ITofu* CreateTofu() {
	return new Mina;
}

#ifdef __cplusplus
}
#endif

