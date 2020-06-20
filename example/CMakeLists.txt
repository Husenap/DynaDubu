set(target_name "example-app")


# Main application
set(src_files
	"example-app/main.cpp")

add_executable(${target_name} ${src_files})

target_link_libraries(${target_name} "dyna-dubu")

set(THREADS_PREFER_PTHREAD_FLAG on)
find_package(Threads REQUIRED)
target_link_libraries(${target_name} Threads::Threads)

# Tofu plugin
add_library("tofu" SHARED "tofu/tofu.cpp")


copy_to_target("tofu" ${target_name})
