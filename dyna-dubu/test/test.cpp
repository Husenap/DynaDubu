#include <gtest/gtest.h>

#include <dyna-dubu/SharedLibrary.h>

TEST(dyna_dubu, load) {
	dd::SharedLibrary dubuLib("dubu");
	dd::SharedLibrary minaLib("mina");
	dd::SharedLibrary noLib("nonexistent");

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

TEST(dyna_dubu, name_function){
	dd::SharedLibrary dubuLib("dubu");
	dd::SharedLibrary minaLib("mina");

	std::string dubuName = dubuLib.Call<const char*>("name");
	std::string minaName = minaLib.Call<const char*>("name");

	EXPECT_EQ(dubuName, "dubu");
	EXPECT_EQ(minaName, "mina");
}

TEST(dyna_dubu, magic_function){
	dd::SharedLibrary dubuLib("dubu");
	dd::SharedLibrary minaLib("mina");

	int dubuMagi0 = dubuLib.GetFunction<int, int, int>("magic")(4, 5);
	int minaMagi0 = minaLib.GetFunction<int, int, int>("magic")(4, 5);

	int dubuMagic = dubuLib.Call<int>("magic", 4, 5);
	int minaMagic = minaLib.Call<int>("magic", 4, 5);

	EXPECT_EQ(dubuMagic, 20);
	EXPECT_EQ(minaMagic, 9);
}

