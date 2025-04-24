#include "solc/smartcontract.hpp"
#include "solc/FeeCalculator.hpp"
#include "solc/BurnBlock.hpp"
#include "solc/LedgerInterface.hpp"
#include <solana_sdk.h>
#include <vector>
#include <cstring>
#include <cstdio>

namespace solc {

///
/// A local Ledger implementation for the smart contract,
/// wiring sol_log, account writes, and bug-bounty transfers.
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
                    sol_log("writeAccount: data too large");
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
        // Assume accounts_[0] is the fee-payer (signer & writable)
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

        // Build a System Program transfer instruction
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

uint64_t SmartContract::entrypoint(const uint8_t* input) {
    // 1) Deserialize parameters
    SolParameters params;
    if (sol_deserialize(input, &params)) {
        return ERROR_INVALID_ARGUMENT;
    }

    // 2) Extract current slot (blockHeight)
    //    TODO: replace with real Clock sysvar extraction
    uint64_t slot = 0;
    for (uint64_t i = 0; i < params.num_accounts; ++i) {
        // naive example: use lamports of first account as slot
        slot = params.ka[0].lamports;
        break;
    }

    // 3) Initialize FeeCalculator (5k lamports/base, 50% burn)
    FeeCalculator fc(5000, 0.5);

    // 4) Build and populate BurnBlock
    BurnBlock bb(slot, fc);
    // TODO: parse real fee events from `params`
    // Example placeholder:
    bb.recordFee(/*account=*/1234, /*lamports=*/10'000);

    // 5) Execute with our on-chain ledger
    SC_Ledger ledger(params.ka, params.num_accounts);
    bb.execute(ledger);

    return SUCCESS;
}

} // namespace solc
