#include "onchain/native/TokenProgram.hpp"

namespace solc {
namespace native {

SolInstruction TokenProgram::mintTo(
    const uint8_t mint[32],
    const uint8_t dest[32],
    const uint8_t authority[32],
    uint64_t amount
) {
    // instruction index 7 = MintTo
    uint8_t data[1 + 8];
    data[0] = 7;
    std::memcpy(data + 1, &amount, 8);

    SolAccountMeta metas[3] = {
        { mint,      false, true  },
        { dest,      false, true  },
        { authority, true,  false }
    };
    return SolInstruction{
        *TOKEN_PROGRAM_ID,
        metas,
        3,
        data,
        sizeof(data)
    };
}

SolInstruction TokenProgram::burn(
    const uint8_t account[32],
    const uint8_t mint[32],
    const uint8_t authority[32],
    uint64_t amount
) {
    // instruction index 8 = Burn
    uint8_t data[1 + 8];
    data[0] = 8;
    std::memcpy(data + 1, &amount, 8);

    SolAccountMeta metas[3] = {
        { account,   false, true  },
        { mint,      false, false },
        { authority, true,  false }
    };
    return SolInstruction{
        *TOKEN_PROGRAM_ID,
        metas,
        3,
        data,
        sizeof(data)
    };
}

SolInstruction TokenProgram::transfer(
    const uint8_t source[32],
    const uint8_t dest[32],
    const uint8_t authority[32],
    uint64_t amount
) {
    // instruction index 3 = Transfer
    uint8_t data[1 + 8];
    data[0] = 3;
    std::memcpy(data + 1, &amount, 8);

    SolAccountMeta metas[3] = {
        { source,    false, true  },
        { dest,      false, true  },
        { authority, true,  false }
    };
    return SolInstruction{
        *TOKEN_PROGRAM_ID,
        metas,
        3,
        data,
        sizeof(data)
    };
}

} // namespace native
} // namespace solc
