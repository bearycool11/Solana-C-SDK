#include "solc/smartcontract.hpp"
#include "solc/FeeCalculator.hpp"
#include "solc/BurnBlock.hpp"
#include "solc/LedgerInterface.hpp"
#include <solana_sdk.h>
#include <vector>
#include <cstring>

namespace solc {

///
/// A concrete LedgerInterface for on-chain use via the Solana C SDK
///
class SC_Ledger : public LedgerInterface {
public:
    SC_Ledger(SolAccountInfo* accounts, uint64_t num_accounts)
      : accounts_(accounts), num_accounts_(num_accounts) {}
    ~SC_Ledger() override = default;

    void writeAccount(uint64_t pubkey, const std::vector<uint8_t>& data) override {
        for (uint64_t i = 0; i < num_accounts_; ++i) {
            if (memcmp(accounts_[i].key, &pubkey, sizeof(pubkey)) == 0) {
                if (accounts_[i].data_len >= data.size()) {
                    sol_memcpy(accounts_[i].data, data.data(), data.size());
                } else {
                    sol_log("writeAccount: buffer too small");
                }
                return;
            }
        }
        sol_log("writeAccount: account not found");
    }

    void solLog(const char* msg) override {
        sol_log(msg);
    }

    void sendBugReward(uint64_t pubkey, uint64_t lamports) override {
        // find hunter index
        int64_t hunter_idx = -1;
        for (uint64_t i = 0; i < num_accounts_; ++i) {
            if (memcmp(accounts_[i].key, &pubkey, sizeof(pubkey)) == 0) {
                hunter_idx = i;
                break;
            }
        }
        if (hunter_idx < 0) {
            sol_log("sendBugReward: hunter not found");
            return;
        }
        // payer is account 0
        SolAccountMeta metas[2] = {
            { accounts_[0].key, /*is_signer=*/true,  /*is_writable=*/true  },
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

/// KINDLING: hash `data[0..len)` into `out[32]`
void SmartContract::KINDLING(const uint8_t* data, uint64_t len, uint8_t out[32]) {
    if (sol_sha256(data, len, out, 32) != SUCCESS) {
        sol_log("KINDLING: sha256 failed");
    }
}

/// TORCHING: hash `data[0..len)` into `out[32]`
void SmartContract::TORCHING(const uint8_t* data, uint64_t len, uint8_t out[32]) {
    if (sol_sha256(data, len, out, 32) != SUCCESS) {
        sol_log("TORCHING: sha256 failed");
    }
}

uint64_t SmartContract::entrypoint(const uint8_t* input) {
    // 1) Deserialize instruction
    SolParameters params;
    if (sol_deserialize(input, &params)) {
        return ERROR_INVALID_ARGUMENT;
    }

    // 2) Extract “slot” (placeholder: lamports of account 0)
    uint64_t slot = params.ka[0].lamports;

    // 3) Compute & log KINDLING hash of slot
    uint8_t kindling_hash[32];
    KINDLING(reinterpret_cast<const uint8_t*>(&slot), sizeof(slot), kindling_hash);
    sol_log_data(kindling_hash, 32);

    // 4) Set up fee‐burn pipeline
    FeeCalculator fc(/*baseFeeRate=*/5000, /*burnRatio=*/0.5);
    BurnBlock   bb(slot, fc);

    // TODO: parse real fee events from params.ka or sysvar; demo placeholder:
    bb.recordFee(/*account=*/1234, /*lamports=*/10'000);

    // 5) Execute (includes BugWatcher logging + rewards)
    SC_Ledger ledger(params.ka, params.num_accounts);
    bb.execute(ledger);

    // 6) Compute & log TORCHING hash of burned total
    uint64_t burned = bb.getBurnedTotal();
    uint8_t torch_hash[32];
    TORCHING(reinterpret_cast<const uint8_t*>(&burned), sizeof(burned), torch_hash);
    sol_log_data(torch_hash, 32);

    return SUCCESS;
}

} // namespace solc
