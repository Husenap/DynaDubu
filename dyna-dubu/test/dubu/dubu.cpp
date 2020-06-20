#ifdef __cplusplus
extern "C" {
#endif

#include "../plugin.h"

const char* name() {
	return "dubu";
}

int magic(int a, int b){
	return a * b;
}

#ifdef __cplusplus
}
#endif

