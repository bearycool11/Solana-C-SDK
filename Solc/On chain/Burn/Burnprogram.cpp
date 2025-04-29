#include "onchain/burn/BurnProgram.hpp"

#include <cstring>
#include <solana_sdk.h>

#include "solc/AccountInfo.hpp"
#include "solc/Syscalls.hpp"
#include "solc/TokenProgram.hpp"
#include "solc/StatusCodes.hpp"

namespace solc {
namespace onchain {
namespace burn {

uint64_t BurnProgram::process(const uint8_t* input) {
    // 1) Deserialize parameters
    SolParameters params;
    if (sol_deserialize(input, &params)) {
        return ProgramError::InvalidArgument;
    }
    if (params.num_accounts < 4) {
        sol_panic("BurnProgram: requires 4 accounts");
    }

    // 2) Wrap raw SolAccountInfo in our helper
    AccountInfo owner(&params.ka[0]);
    AccountInfo tokenAccount(&params.ka[1]);
    AccountInfo mintAccount(&params.ka[2]);
    AccountInfo tokenProgram(&params.ka[3]);

    // 3) Read `amount` from instruction data
    if (params.data_len < sizeof(uint64_t)) {
        sol_panic("BurnProgram: data too small for amount");
    }
    uint64_t amount;
    std::memcpy(&amount, params.data, sizeof(amount));

    // 4) Validate accounts
    Syscalls::assert_signer(owner);  // owner must sign
    if (tokenAccount.owner() != SPL_TOKEN_PROGRAM_ID) {
        sol_panic("BurnProgram: token account not owned by SPL Token program");
    }
    auto tokenState = tokenAccount.decodeTokenAccount();
    if (tokenState.mint != mintAccount.key()) {
        sol_panic("BurnProgram: token mint mismatch");
    }
    if (tokenState.amount < amount) {
        sol_panic("BurnProgram: insufficient token balance");
    }

    // 5) Build the SPL Token Burn instruction via CPI
    Instruction ix = TokenProgram::burn(
        tokenAccount.key(),   // token account
        mintAccount.key(),    // mint
        owner.key(),          // authority
        amount                // amount
    );

    // 6) Invoke CPI
    Syscalls::invoke(ix, params.ka, params.num_accounts);

    return ProgramError::Success;
}

} // namespace burn
} // namespace onchain
} // namespace solc
