#pragma once
#include <cstdint>
#include "solana_sdk.h"

namespace solc {
namespace common {

/// Wrapper around Solana C SDK's SolAccountInfo
class AccountInfo {
public:
    explicit AccountInfo(SolAccountInfo* info);

    /// Public key of the account
    const uint8_t* key() const;
    uint64_t       lamports() const;
    uint8_t*       data() const;
    uint64_t       data_len() const;
    const uint8_t* owner() const;
    bool           is_signer() const;
    bool           is_writable() const;

private:
    SolAccountInfo* _info;
};

} // namespace common
} // namespace solc
