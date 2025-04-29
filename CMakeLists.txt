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

cmake_minimum_required(VERSION 3.16)
project(SolanaCSDK)

# Set to "Release" to strip symbols
set(CMAKE_BUILD_TYPE Release)

# Solana SDK path
if(NOT DEFINED ENV{SOLANA_SDK_INCLUDE})
    message(FATAL_ERROR "Please set SOLANA_SDK_INCLUDE env var to Solana SDK include directory.")
endif()

include_directories($ENV{SOLANA_SDK_INCLUDE})
include_directories(SYSTEM Solc/include)
include_directories(Solc/onchain)
include_directories(Solc/onchain/common)
include_directories(Solc/onchain/native)
include_directories(Solc/onchain/ibc)
include_directories(Solc/offchain/client)

# BPF-specific flags (targeting Solana VM)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti -ffreestanding -Wall -Werror -O2")

# === On-chain Target ===
file(GLOB_RECURSE ONCHAIN_SOURCES
    Solc/onchain/*/*.cpp
    Solc/onchain/*.cpp
)

add_library(solc_contract SHARED ${ONCHAIN_SOURCES})
set_target_properties(solc_contract PROPERTIES
    OUTPUT_NAME "solc_contract"
    SUFFIX ".so"
)

# === Optional: Off-chain Clients ===
add_executable(solana_client_test
    Solc/offchain/client/SolanaClient.cpp
    Solc/offchain/client/DRPCClient.cpp
    Solc/offchain/client/GRPCClient.cpp
)

# Link off-chain client with curl if needed
find_package(CURL REQUIRED)
target_link_libraries(solana_client_test PRIVATE CURL::libcurl)

# === Output ===
message(STATUS "Build output: solc_contract.so + solana_client_test")
