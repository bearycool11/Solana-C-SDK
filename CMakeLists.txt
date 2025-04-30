cmake_minimum_required(VERSION 3.16)
project(SolanaCSDK LANGUAGES C CXX)

# ----------------------------
# Build configuration
# ----------------------------
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

# ----------------------------
# Solana SDK include path
# ----------------------------
if(NOT DEFINED ENV{SOLANA_SDK_INCLUDE})
  message(FATAL_ERROR "Please set SOLANA_SDK_INCLUDE to your Solana SDK include directory")
endif()
include_directories($ENV{SOLANA_SDK_INCLUDE})

# ----------------------------
# Project include directories
# ----------------------------
# Core on-chain headers
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/Solc/onchain
  ${CMAKE_CURRENT_SOURCE_DIR}/Solc/onchain/common
  ${CMAKE_CURRENT_SOURCE_DIR}/Solc/onchain/native
  ${CMAKE_CURRENT_SOURCE_DIR}/Solc/onchain/ibc
)
# Off-chain client headers
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/Solc/offchain/client
)
# Public headers
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/Solc/include/solc
)

# ----------------------------
# On-chain BPF library target
# ----------------------------
# Gather all on-chain .cpp sources
file(GLOB_RECURSE ONCHAIN_SOURCES
  Solc/onchain/*.cpp
)

add_library(solc_contract SHARED ${ONCHAIN_SOURCES})

# Ensure no lib prefix and .so suffix
set_target_properties(solc_contract PROPERTIES
  OUTPUT_NAME "solc_contract"
  PREFIX ""
  SUFFIX ".so"
)

# Strip symbols for minimal BPF binary
target_link_options(solc_contract PRIVATE -s)

# BPF-specific flags
target_compile_options(solc_contract PRIVATE
  -fno-exceptions
  -fno-rtti
  -ffreestanding
  -Wall
  -Werror
  -O2
)

# ----------------------------
# Off-chain client test executable
# ----------------------------
file(GLOB CLIENT_SOURCES
  Solc/offchain/client/SolanaClient.cpp
  Solc/offchain/client/GRPCClient.cpp
  Solc/offchain/client/DRPCClient.cpp
)

add_executable(solana_client_test ${CLIENT_SOURCES})
target_compile_definitions(solana_client_test PRIVATE _GNU_SOURCE)
target_link_libraries(solana_client_test PRIVATE CURL::libcurl)

# ----------------------------
# Find dependencies
# ----------------------------
find_package(CURL REQUIRED)

# ----------------------------
# Summary
# ----------------------------
message(STATUS "Configured Solana-C-SDK:")
message(STATUS "  On-chain target: solc_contract.so")
message(STATUS "  Off-chain test: solana_client_test")
