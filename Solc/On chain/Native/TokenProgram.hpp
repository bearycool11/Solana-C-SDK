#pragma once

#include <cstdint>
#include <solana_sdk.h>
#include <cstring>

namespace solc {
namespace native {

/// Builders for the SPL Token Program CPI instructions
class TokenProgram {
public:
    /// Mint tokens to a token account
    /// - mint:      mint account pubkey (writable)
    /// - dest:      token account to credit (writable)
    /// - authority: mint authority (signer)
    /// - amount:    tokens to mint
    static SolInstruction mintTo(
        const uint8_t mint[32],
        const uint8_t dest[32],
        const uint8_t authority[32],
        uint64_t amount
    );

    /// Burn tokens from a token account
    /// - account:   token account to debit (writable)
    /// - mint:      mint account pubkey
    /// - authority: account owner or delegate (signer)
    /// - amount:    tokens to burn
    static SolInstruction burn(
        const uint8_t account[32],
        const uint8_t mint[32],
        const uint8_t authority[32],
        uint64_t amount
    );

    /// Transfer tokens between accounts
    /// - source:    source token account (writable)
    /// - dest:      destination token account (writable)
    /// - authority: owner or delegate (signer)
    /// - amount:    tokens to transfer
    static SolInstruction transfer(
        const uint8_t source[32],
        const uint8_t dest[32],
        const uint8_t authority[32],
        uint64_t amount
    );
};

} // namespace native
} // namespace solc
