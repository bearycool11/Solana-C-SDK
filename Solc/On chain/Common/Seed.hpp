#pragma once
#include <cstdint>
#include "solana_sdk.h"

namespace solc {
namespace common {

/// Attempts to find a program-derived address (PDA).
/// On success returns the bump seed and fills out_address[32].
/// Panics on failure.
uint8_t findProgramAddress(
    const uint8_t* const seeds[],
    const uint64_t  seeds_len[],
    uint64_t        seeds_cnt,
    const uint8_t   program_id[32],
    uint8_t         out_address[32]
);

/// Creates a program address (no bump seed).
/// Panics if the address is invalid.
void createProgramAddress(
    const uint8_t* const seeds[],
    const uint64_t  seeds_len[],
    uint64_t        seeds_cnt,
    const uint8_t   program_id[32],
    uint8_t         out_address[32]
);

} // namespace common
} // namespace solc
