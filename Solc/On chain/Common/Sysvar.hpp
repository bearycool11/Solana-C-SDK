#pragma once
#include <cstdint>
#include "solana_sdk.h"

namespace solc {
namespace common {

/// Representation of the Clock sysvar
struct Clock {
    uint64_t slot;
    uint64_t epoch_start_timestamp;
    uint64_t epoch;
    uint64_t leader_schedule_epoch;
};

/// Representation of the Rent sysvar
struct Rent {
    uint64_t lamports_per_byte_year;
    uint64_t exemption_threshold;
    uint64_t burn_percent;
};

/// Fetch the Clock sysvar from the given accounts.
/// Panics if not found.
Clock getClock(const SolParameters& params);

/// Fetch the Rent sysvar from the given accounts.
/// Panics if not found.
Rent getRent(const SolParameters& params);

} // namespace common
} // namespace solc
