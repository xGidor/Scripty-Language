cmake_minimum_required(VERSION 3.6.0)
project(ScriptyLang)

# Specify the source files
set(SOURCES
    main.cpp
    src/nodes/nodes.cpp
    src/parser/parser.cpp
    src/tokenizer/tokenizer.cpp
)

# Specify the include directories, including the one within the "src" directory
include_directories(
    src/nodes
    src/errors
    src/json
    src/parser
    src/position
    src/tokenizer
)

# Create an executable target
add_executable(Scripty ${SOURCES})

# You can set compiler flags here if needed, e.g., C++ version
# set(CMAKE_CXX_FLAGS "-std=c++11")

# Optionally, specify additional libraries if required
# target_link_libraries(MyExecutable SomeLibrary)

# Set the output directory for the binary
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)