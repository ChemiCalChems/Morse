project (Morse)

set(CMAKE_CXX_COMPILER_FLAGS "--std=c++14 -Wall -Werror")

set(SOURCE_FILES src/morse.cpp src/console.cpp)

find_package(OpenAL REQUIRED)

include_directories(${OPENAL_INCLUDE_DIR})

add_library(morse SHARED ${SOURCE_FILES})

add_executable(test src/test.cpp)

target_link_libraries(test ${OPENAL_LIBRARY})

target_link_libraries(test morse)
