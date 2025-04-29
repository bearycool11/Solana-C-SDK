#pragma once

#include <cstdint>
#include <solana_sdk.h>

#include "solc/AccountInfo.hpp"
#include "solc/Syscalls.hpp"
#include "solc/TokenProgram.hpp"
#include "solc/StatusCodes.hpp"

namespace solc {
namespace onchain {
namespace token {

/// BPF on-chain Token Mint program: mints SPL tokens via CPI to the Token program.
class TokenMintProgram {
public:
    /// Deserialize & process the mint instruction.
    ///
    /// Accounts expected:
    ///   0. Mint authority (signer)
    ///   1. Mint account (writable)
    ///   2. Token account to credit (writable)
    ///   3. SPL Token program ID
    ///
    /// Instruction data (bytes): 8-byte little-endian u64 `amount`.
    static uint64_t process(const uint8_t* input);
};

} // namespace token
} // namespace onchain
} // namespace solc
