#include "solc/BugWatcher.hpp"
#include "solc/LedgerInterface.hpp"
#include <array>
#include <cstdio>

namespace solc {

static constexpr int MAX_EVENTS = 16;
static struct {
    BW_EventType type;
    uint64_t     account;
    bool         seen;
} events[MAX_EVENTS];
static int event_count;
static uint64_t current_block;

void bw_init(uint64_t blockHeight) {
    current_block = blockHeight;
    event_count = 0;
    for (int i = 0; i < MAX_EVENTS; i++) {
        events[i].seen = false;
    }
}

bool bw_record_event(BW_EventType evt, uint64_t offendingAccount) {
    for (int i = 0; i < event_count; i++) {
        if (events[i].type == evt && events[i].account == offendingAccount) {
            return false;
        }
    }
    if (event_count < MAX_EVENTS) {
        events[event_count++] = { evt, offendingAccount, true };
    }
    return true;
}

void bw_finalize(LedgerInterface& ledger) {
    char buf[128];
    constexpr uint64_t BUG_REWARD = 100; // lamports to reward
    for (int i = 0; i < event_count; i++) {
        std::snprintf(buf, sizeof(buf),
            "[BugWatcher][Block %llu] EVT=%u ACCT=0x%llx",
            (unsigned long long)current_block,
            static_cast<uint8_t>(events[i].type),
            (unsigned long long)events[i].account
        );
        ledger.solLog(buf);
        // reward the “finder” (here we use offendingAccount as the recipient)
        ledger.sendBugReward(events[i].account, BUG_REWARD);
    }
}

} // namespace solc
