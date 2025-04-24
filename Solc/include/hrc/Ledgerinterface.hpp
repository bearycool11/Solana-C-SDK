#pragma once
#include <vector>
#include <cstdint>
#include <string>

namespace solc {

class LedgerInterface {
public:
    virtual ~LedgerInterface() = default;

    /// Write raw bytes into account `pubkey`
    virtual void writeAccount(uint64_t pubkey, const std::vector<uint8_t>& data) = 0;

    /// Emit an on-chain log
    virtual void solLog(const char* msg) = 0;

    /// Send a bug‐bounty reward (lamports) to an account
    virtual void sendBugReward(uint64_t pubkey, uint64_t lamports) = 0;
};

} // namespace solc
