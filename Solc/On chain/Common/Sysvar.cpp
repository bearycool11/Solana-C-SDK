#include "onchain/common/Sysvar.hpp"
#include <solana_sdk.h>
#include <cstring>

namespace solc {
namespace common {

Clock getClock(const SolParameters& params) {
    for (uint64_t i = 0; i < params.num_accounts; ++i) {
        if (memcmp(params.ka[i].key,
                   SYSVAR_CLOCK_PUBKEY, 32) == 0) {
            // data is a SolClock struct
            SolClock* sc = (SolClock*)params.ka[i].data;
            return Clock{ sc->slot,
                          sc->epoch_start_timestamp,
                          sc->epoch,
                          sc->leader_schedule_epoch };
        }
    }
    sol_panic("Sysvar::getClock: account not found");
}

Rent getRent(const SolParameters& params) {
    for (uint64_t i = 0; i < params.num_accounts; ++i) {
        if (memcmp(params.ka[i].key,
                   SYSVAR_RENT_PUBKEY, 32) == 0) {
            SolRent* sr = (SolRent*)params.ka[i].data;
            return Rent{ sr->lamports_per_byte_year,
                         sr->exemption_threshold,
                         sr->burn_percent };
        }
    }
    sol_panic("Sysvar::getRent: account not found");
}

} // namespace common
} // namespace solc
