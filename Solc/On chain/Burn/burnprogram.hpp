#pragma once

#include <cstdint>
#include <solana_sdk.h>

#include "solc/AccountInfo.hpp"
#include "solc/Syscalls.hpp"
#include "solc/TokenProgram.hpp"
#include "solc/StatusCodes.hpp"

namespace solc {
namespace onchain {
namespace burn {

/// BPF on-chain Burn program: burns SPL tokens via CPI to the Token program.
class BurnProgram {
public:
    /// Deserialize & process the burn instruction.
    /// Expects:
    ///   accounts[0] = token owner (signer)
    ///   accounts[1] = token account to burn from (writable)
    ///   accounts[2] = mint account
    ///   accounts[3] = SPL Token program ID
    /// Instruction data = 8-byte little-endian u64 `amount`.
    static uint64_t process(const uint8_t* input);
};

} // namespace burn
} // namespace onchain
} // namespace solc
