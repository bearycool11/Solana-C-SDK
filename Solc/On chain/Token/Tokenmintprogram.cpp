#include "onchain/token/TokenMintProgram.hpp"

#include <cstring>
#include <solana_sdk.h>

#include "solc/AccountInfo.hpp"
#include "solc/Syscalls.hpp"
#include "solc/TokenProgram.hpp"
#include "solc/StatusCodes.hpp"

namespace solc {
namespace onchain {
namespace token {

uint64_t TokenMintProgram::process(const uint8_t* input) {
    // 1) Deserialize parameters
    SolParameters params;
    if (sol_deserialize(input, &params)) {
        return ProgramError::InvalidArgument;
    }
    if (params.num_accounts < 4) {
        sol_panic("TokenMintProgram: requires 4 accounts");
    }

    // 2) Wrap raw SolAccountInfo in helpers
    AccountInfo authority(&params.ka[0]);
    AccountInfo mintAccount(&params.ka[1]);
    AccountInfo destAccount(&params.ka[2]);
    AccountInfo tokenProgram(&params.ka[3]);

    // 3) Read `amount` from instruction data
    if (params.data_len < sizeof(uint64_t)) {
        sol_panic("TokenMintProgram: data too small for amount");
    }
    uint64_t amount;
    std::memcpy(&amount, params.data, sizeof(amount));

    // 4) Validate accounts
    Syscalls::assert_signer(authority);  // must be a signer

    if (mintAccount.owner() != SPL_TOKEN_PROGRAM_ID) {
        sol_panic("TokenMintProgram: mint not owned by SPL Token program");
    }
    auto mintInfo = mintAccount.decodeMint();
    if (!mintInfo.is_initialized) {
        sol_panic("TokenMintProgram: mint is not initialized");
    }

    if (destAccount.owner() != SPL_TOKEN_PROGRAM_ID) {
        sol_panic("TokenMintProgram: destination not owned by SPL Token program");
    }
    auto tokenState = destAccount.decodeTokenAccount();
    if (tokenState.mint != mintAccount.key()) {
        sol_panic("TokenMintProgram: destination mint mismatch");
    }

    // 5) Build the SPL Token MintTo instruction via CPI
    Instruction ix = TokenProgram::mintTo(
        mintAccount.key(),    // mint
        destAccount.key(),    // destination token account
        authority.key(),      // mint authority
        amount                // amount to mint
    );

    // 6) Invoke CPI
    Syscalls::invoke(ix, params.ka, params.num_accounts);

    return ProgramError::Success;
}

} // namespace token
} // namespace onchain
} // namespace solc
