#include "onchain/common/Seed.hpp"
#include <solana_sdk.h>

namespace solc {
namespace common {

uint8_t findProgramAddress(
    const uint8_t* const seeds[],
    const uint64_t  seeds_len[],
    uint64_t        seeds_cnt,
    const uint8_t   program_id[32],
    uint8_t         out_address[32]
) {
    uint8_t bump;
    // sol_try_find_program_address returns SUCCESS on success
    if (sol_try_find_program_address(
            seeds, seeds_len, seeds_cnt,
            program_id, out_address, &bump) != SUCCESS) {
        sol_panic("Seed::findProgramAddress failed");
    }
    return bump;
}

void createProgramAddress(
    const uint8_t* const seeds[],
    const uint64_t  seeds_len[],
    uint64_t        seeds_cnt,
    const uint8_t   program_id[32],
    uint8_t         out_address[32]
) {
    if (sol_create_program_address(
            seeds, seeds_len, seeds_cnt,
            program_id, out_address) != SUCCESS) {
        sol_panic("Seed::createProgramAddress failed");
    }
}

} // namespace common
} // namespace solc
