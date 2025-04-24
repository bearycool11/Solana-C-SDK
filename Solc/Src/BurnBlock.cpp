#include "solc/BurnBlock.hpp"
#include "solc/BugWatcher.hpp"

namespace solc {

BurnBlock::BurnBlock(uint64_t blockHeight, const FeeCalculator& fc)
  : _blockHeight(blockHeight), _feeCalc(fc) {}

void BurnBlock::recordFee(uint64_t account, uint64_t lamports) {
    _records.push_back({ account, lamports });
}

void BurnBlock::execute(LedgerInterface& ledger) {
    // Initialize bugwatcher
    bw_init(_blockHeight);

    for (const auto& rec : _records) {
        // 1) Owner check
        if (!ledger.writeAccount) { /* replace with real owner-check API */ }
        // (Assume ledger has a method isExpectedOwner; pseudo-code)
        // if (!ledger.isExpectedOwner(rec.account)) {
        //     bw_record_event(BW_EventType::OWNER_MISMATCH, rec.account);
        //     continue;
        // }

        // 2) Overflow guard
        if (rec.lamports > UINT64_MAX - _burnedTotal) {
            bw_record_event(BW_EventType::OVERFLOW, rec.account);
            continue;
        }

        // 3) Compute burn & validator share
        uint64_t toBurn = _feeCalc.computeBurn(rec.lamports);
        _burnedTotal    += toBurn;
        _validatorTotal += (rec.lamports - toBurn);
    }

    // Finalize watcher: logs + rewards
    bw_finalize(ledger);

    // Example: write updated state back on-chain
    // std::vector<uint8_t> packed = serialize();
    // ledger.writeAccount(burnAccountKey, packed);
}

uint64_t BurnBlock::getBurnedTotal() const     { return _burnedTotal; }
uint64_t BurnBlock::getValidatorTotal() const  { return _validatorTotal; }

} // namespace solc
