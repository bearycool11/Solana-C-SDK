#pragma once
#include "FeeCalculator.hpp"
#include "LedgerInterface.hpp"
#include "BugWatcher.hpp"
#include <cstdint>
#include <vector>

namespace solc {

struct BurnRecord {
    uint64_t account;
    uint64_t lamports;
};

class BurnBlock {
public:
    BurnBlock(uint64_t blockHeight, const FeeCalculator& fc);

    /// Register that `lamports` were collected from `account`
    void recordFee(uint64_t account, uint64_t lamports);

    /// Process all records: split fees, burn, reward & log anomalies
    void execute(LedgerInterface& ledger);

    uint64_t getBurnedTotal() const;
    uint64_t getValidatorTotal() const;

private:
    uint64_t             _blockHeight;
    const FeeCalculator& _feeCalc;
    std::vector<BurnRecord> _records;
    uint64_t             _burnedTotal    = 0;
    uint64_t             _validatorTotal = 0;
};

} // namespace solc
