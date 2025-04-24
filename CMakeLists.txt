cmake_minimum_required(VERSION 3.16)
project(solc_contract LANGUAGES C CXX)

# BPF target (using Solana SDK toolchain)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

# Where solana_sdk.h lives
include_directories($ENV{SOLANA_SDK_INCLUDE})

# Include our headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source files
file(GLOB SRCS
    src/*.cpp
)

# Build BPF shared object
add_library(solc_contract SHARED ${SRCS})

# Strip symbols
target_link_options(solc_contract PRIVATE -s)

# Place .so in out directory
set_target_properties(solc_contract PROPERTIES
    OUTPUT_NAME "solc_contract"
    PREFIX ""           # no lib prefix
    SUFFIX ".so"
)
