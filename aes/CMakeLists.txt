cmake_minimum_required(VERSION 3.4...3.18)
project(aes)
set(CMAKE_CXX_FLAGS "-Wall -shared -std=c++11 -fPIC -o aes$(python3-config --extension-suffix)")
add_subdirectory(pybind11-2.11.1)
add_library(aes aes.cpp)

target_link_libraries(
    aes
    pybind11::headers
    ssl
    crypto
)

# target_compile_definitions(
#     aes
#     "-I/opt/python38/include/python3.8 -L/opt/python38/lib/python3.8/config-3.8-x86_64-linux-gnu -L/opt/python38/lib  -lcrypt -lpthread -ldl  -lutil -lm -lm"

# )
