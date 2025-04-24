#pragma once
#include <cstdint>

namespace solc {

/// Top-level smart contract entrypoint wrapper
class SmartContract {
public:
    /// Called by Solana’s runtime; returns SUCCESS or error code
    static uint64_t entrypoint(const uint8_t* input);
};

} // namespace solc
