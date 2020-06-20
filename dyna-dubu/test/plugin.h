#pragma once

struct ITofu {
	virtual ~ITofu()    = default;
	virtual void Cook() = 0;
	virtual void Eat()  = 0;
};

#ifdef __cplusplus
extern "C" {
#endif

const char* name();

int magic(int a, int b);

ITofu* CreateTofu();

#ifdef __cplusplus
}
#endif

