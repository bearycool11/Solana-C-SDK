#pragma once
#include <cstdint>
#include "solana_sdk.h"

namespace solc {
namespace common {

/// Pubkey wrapper for 32-byte public keys
class Pubkey {
public:
    explicit Pubkey(const uint8_t* data);
    /// Returns pointer to 32-byte array
    const uint8_t* data() const;

private:
    const uint8_t* _data;
};

/// Metadata for instruction accounts
struct AccountMeta {
    Pubkey       pubkey;
    bool         is_signer;
    bool         is_writable;
};

/// Represents a Solana instruction for CPI
struct Instruction {
    Pubkey                program_id;
    const AccountMeta*    accounts;
    uint64_t              account_len;
    const uint8_t*        data;
    uint64_t              data_len;
};

} // namespace common
} // namespace solc
