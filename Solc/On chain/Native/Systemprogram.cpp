#include "onchain/native/SystemProgram.hpp"

namespace solc {
namespace native {

SolInstruction SystemProgram::createAccount(
    const uint8_t from[32],
    const uint8_t to[32],
    uint64_t lamports,
    uint64_t space,
    const uint8_t owner[32]
) {
    // instruction index 0 = CreateAccount
    uint8_t data[1 + 8 + 8 + 32];
    data[0] = 0;
    std::memcpy(data + 1,  &lamports, 8);
    std::memcpy(data + 9,  &space,    8);
    std::memcpy(data + 17, owner,    32);

    SolAccountMeta metas[2] = {
        { from, true,  true  },
        { to,   false, true  }
    };
    return SolInstruction{
        *SYSTEM_PROGRAM_ID,
        metas,
        2,
        data,
        sizeof(data)
    };
}

SolInstruction SystemProgram::transfer(
    const uint8_t from[32],
    const uint8_t to[32],
    uint64_t lamports
) {
    // instruction index 2 = Transfer
    uint8_t data[1 + 8];
    data[0] = 2;
    std::memcpy(data + 1, &lamports, 8);

    SolAccountMeta metas[2] = {
        { from, true,  true  },
        { to,   false, true  }
    };
    return SolInstruction{
        *SYSTEM_PROGRAM_ID,
        metas,
        2,
        data,
        sizeof(data)
    };
}

SolInstruction SystemProgram::allocate(
    const uint8_t account[32],
    uint64_t space
) {
    // instruction index 8 = Allocate
    uint8_t data[1 + 8];
    data[0] = 8;
    std::memcpy(data + 1, &space, 8);

    SolAccountMeta metas[1] = {
        { account, true, true }
    };
    return SolInstruction{
        *SYSTEM_PROGRAM_ID,
        metas,
        1,
        data,
        sizeof(data)
    };
}

SolInstruction SystemProgram::assign(
    const uint8_t account[32],
    const uint8_t owner[32]
) {
    // instruction index 9 = Assign
    uint8_t data[1 + 32];
    data[0] = 9;
    std::memcpy(data + 1, owner, 32);

    SolAccountMeta metas[1] = {
        { account, true, true }
    };
    return SolInstruction{
        *SYSTEM_PROGRAM_ID,
        metas,
        1,
        data,
        sizeof(data)
    };
}

} // namespace native
} // namespace solc
