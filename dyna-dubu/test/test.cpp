#include <gtest/gtest.h>

#include <dyna-dubu/SharedLibrary.h>

TEST(dyna_dubu, load) {
	dd::SharedLibrary dubuLib("dubu");
	dd::SharedLibrary minaLib("mina");
	dd::SharedLibrary noLib("non_existing");

	EXPECT_EQ(dubuLib.IsLoaded(), true);
	EXPECT_EQ(minaLib.IsLoaded(), true);
	EXPECT_EQ(noLib.IsLoaded(), false);
}

TEST(dyna_dubu, reload){
	dd::SharedLibrary dubuLib("dubu");

	EXPECT_EQ(dubuLib.IsLoaded(), true);

	dubuLib.Reload();

	EXPECT_EQ(dubuLib.IsLoaded(), true);
}
