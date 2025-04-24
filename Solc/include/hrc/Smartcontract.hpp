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
#pragma once
#include <cstdint>

namespace solc {

/// Top‐level contract entrypoint wrapper
class SmartContract {
public:
    /// BPF entrypoint: returns SUCCESS (0) or an error code
    static uint64_t entrypoint(const uint8_t* input);

private:
    /// SHA-256 wrapper for “KINDLING” (e.g. hashing slot)
    static void KINDLING(const uint8_t* data, uint64_t len, uint8_t out[32]);

    /// SHA-256 wrapper for “TORCHING” (e.g. hashing burned‐amount)
    static void TORCHING(const uint8_t* data, uint64_t len, uint8_t out[32]);
};

} // namespace solc
