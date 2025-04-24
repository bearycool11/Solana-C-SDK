#pragma once
#include <cstdint>

namespace solc {

/// Types of anomalies we watch for
enum class BW_EventType : uint8_t {
    OWNER_MISMATCH,
    SIGNER_FLAG_MISSING,
    OVERFLOW,
    UNDERFLOW,
    CPI_REUSE,
    // …extend as needed
};

/// Initialize the BugWatcher (once per block)
void bw_init(uint64_t blockHeight);

/// Record an event; returns true if first time seeing it this block
bool bw_record_event(BW_EventType evt, uint64_t offendingAccount);

/// Finalize: emit logs & reward via LedgerInterface
void bw_finalize(class LedgerInterface& ledger);

} // namespace solc
