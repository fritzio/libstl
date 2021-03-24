add_executable(fox "fox.cpp")
target_link_libraries(fox PRIVATE libstl)

add_executable(fox_ascii "fox_ascii.cpp")
target_link_libraries(fox_ascii PRIVATE libstl)