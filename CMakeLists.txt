project (Morse)

set(CMAKE_CXX_COMPILER_FLAGS "--std=c++14 -Wall -Werror")

set(SOURCE_FILES src/main.cpp)

find_package(OpenAL REQUIRED)

include_directories(${OPENAL_INCLUDE_DIR})

add_executable(Morse ${SOURCE_FILES})

target_link_libraries(Morse ${OPENAL_LIBRARY})
