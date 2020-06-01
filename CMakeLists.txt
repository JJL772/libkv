# CMake script for libkv

project(libkv C CXX)

set(SRCS src/keyvalues.cpp)

if(COMPILE_TESTS)
        add_executable(libkv ${SRCS} src/main.cpp)
else()
        add_library(libkv STATIC ${SRCS})
endif(COMPILE_TESTS)



