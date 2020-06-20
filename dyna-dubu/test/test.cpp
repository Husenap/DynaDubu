#include <gtest/gtest.h>

#include <dyna-dubu/SharedLibrary.h>

TEST(dyna_dubu, constructor) {
	dd::SharedLibrary dubuLib("dubulib");
	dd::SharedLibrary minaLib("minalib");
}
