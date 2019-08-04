cmake_minimum_required(VERSION 2.9)
project(ansinizer)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(LLVM REQUIRED)
find_package(Clang REQUIRED)

set(CMAKE_CXX_FLAGS "${LLVM_COMPILE_FLAGS} ${CMAKE_CXX_FLAGS} -std=c++11 -lstdc++ -w -Os")
if(CMAKE_BUILD_TYPE MATCHES Debug)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fsanitize=address")
endif(CMAKE_BUILD_TYPE MATCHES Debug)

message(STATUS "CXX flags: " ${CMAKE_CXX_FLAGS})

include_directories(${LLVM_INCLUDE_DIRS})
include_directories(${CLANG_INCLUDE_DIRS})
include_directories(include)

add_executable(ansinizer
  src/Frontend.cpp
  src/Main.cpp
  src/OptionManager.cpp
  src/Transformation.cpp
  src/FileManager.cpp
)

target_link_libraries(ansinizer ${CLANG_LIBS} ${LLVM_LIBS_CORE} ${LLVM_LDFLAGS})

# for make test
#enable_testing()
#add_subdirectory(test)
