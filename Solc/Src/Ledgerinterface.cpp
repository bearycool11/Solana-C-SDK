// src/LedgerInterface.cpp
#include "solc/LedgerInterface.hpp"
#include <solana_sdk.h>
#include <cstring>
#include <vector>

namespace solc {

// Provide out-of-line definition for the pure-virtual destructor
LedgerInterface::~LedgerInterface() {}


/// A default on-chain implementation of your LedgerInterface,
/// backed by the Solana C SDK types: SolAccountInfo, SolInstruction, etc.
class DefaultLedger : public LedgerInterface {
public:
  DefaultLedger(SolAccountInfo* accounts, uint64_t num_accounts)
    : accounts_(accounts), num_accounts_(num_accounts) {}

  /// Find the matching account by pubkey (raw bytes) and memcpy in `data`
  void writeAccount(uint64_t pubkey, const std::vector<uint8_t>& data) override {
    for (uint64_t i = 0; i < num_accounts_; ++i) {
      if (memcmp(accounts_[i].key, &pubkey, sizeof(pubkey)) == 0) {
        if (accounts_[i].data_len >= data.size()) {
          sol_memcpy(accounts_[i].data, data.data(), data.size());
        } else {
          sol_log("writeAccount: data too large");
        }
        return;
      }
    }
    sol_log("writeAccount: account not found");
  }

  /// Simple wrapper around sol_log
  void solLog(const char* msg) override {
    sol_log(msg);
  }

  /// Issue a native SOL transfer from accounts_[0] to the hunter’s account
  void sendBugReward(uint64_t pubkey, uint64_t lamports) override {
    // assume accounts_[0] is the fee-payer (must be signer & writable)
    int64_t payer_idx = 0;
    int64_t hunter_idx = -1;
    for (uint64_t i = 0; i < num_accounts_; ++i) {
      if (memcmp(accounts_[i].key, &pubkey, sizeof(pubkey)) == 0) {
        hunter_idx = i;
        break;
      }
    }
    if (hunter_idx < 0) {
      sol_log("sendBugReward: hunter account not found");
      return;
    }

    // Build the System Program transfer instruction
    SolAccountMeta metas[2] = {
      { accounts_[payer_idx].key, /*is_signer=*/true,  /*is_writable=*/true  },
      { accounts_[hunter_idx].key,/*is_signer=*/false, /*is_writable=*/true }
    };
    SolInstruction ix = {
      .program_id   = *SYSTEM_PROGRAM_ID,
      .account_meta = metas,
      .account_len  = 2,
      .data         = reinterpret_cast<const uint8_t*>(&lamports),
      .data_len     = sizeof(lamports)
    };
    sol_invoke(&ix, accounts_, num_accounts_);
  }

private:
  SolAccountInfo* accounts_;
  uint64_t        num_accounts_;
};

} // namespace solc
