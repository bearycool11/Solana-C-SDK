#pragma once

#include <cstdint>
#include <solana_sdk.h>
#include <cstring>

namespace solc {
namespace native {

/// Builders for the System Program CPI instructions
class SystemProgram {
public:
    /// Create a new account
    /// - from:    funding account (signer & writable)
    /// - to:      new account pubkey (writable)
    /// - lamports: amount to fund
    /// - space:   bytes of data to allocate
    /// - owner:   program that will own the new account
    static SolInstruction createAccount(
        const uint8_t from[32],
        const uint8_t to[32],
        uint64_t lamports,
        uint64_t space,
        const uint8_t owner[32]
    );

    /// Transfer lamports from one account to another
    /// - from:    source (signer & writable)
    /// - to:      destination (writable)
    /// - lamports: amount to transfer
    static SolInstruction transfer(
        const uint8_t from[32],
        const uint8_t to[32],
        uint64_t lamports
    );

    /// Allocate space in an account
    /// - account: account pubkey (signer & writable)
    /// - space:   number of bytes to allocate
    static SolInstruction allocate(
        const uint8_t account[32],
        uint64_t space
    );

    /// Assign an account’s owner
    /// - account: account pubkey (signer & writable)
    /// - owner:   new owner program pubkey
    static SolInstruction assign(
        const uint8_t account[32],
        const uint8_t owner[32]
    );
};

} // namespace native
} // namespace solc
