#include "onchain/ibc/IBCClient.hpp"
#include <cstring>

namespace solc {
namespace ibc {

using common::AccountInfo;
using common::Syscalls;
using common::ProgramError;
using common::read_u64_le;

uint64_t IBCClient::initialize(const uint8_t* input) {
    SolParameters params;
    if (sol_deserialize(input, &params)) {
        return static_cast<uint64_t>(ProgramError::InvalidInstructionData);
    }
    // Expect store account + payer
    if (params.num_accounts < 2) {
        Syscalls::solPanic("IBCClient::initialize requires 2 accounts");
    }
    AccountInfo store(&params.ka[0]);
    // Read and deserialize instruction data
    if (params.data_len < 32 + 8 + 32) {
        Syscalls::solPanic("IBCClient::initialize data too short");
    }
    ClientState cs;
    std::memcpy(cs.chain_id, params.data, 32);
    cs.latest_height = read_u64_le(params.data + 32);
    cs.frozen = false;
    std::memcpy(cs.trust_root, params.data + 40, 32);
    // Write into store account data
    if (store.data_len() < sizeof(ClientState)) {
        Syscalls::solPanic("IBCClient::initialize store too small");
    }
    Syscalls::memCopy(store.data(), &cs, sizeof(cs));
    return static_cast<uint64_t>(ProgramError::Success);
}

uint64_t IBCClient::update(const uint8_t* input) {
    // TODO: parse header + proof, verify via proof verification library
    Syscalls::solPanic("IBCClient::update not implemented");
    return static_cast<uint64_t>(ProgramError::CustomError);
}

uint64_t IBCClient::verifyHeader(const uint8_t* input) {
    // TODO: load ClientState, parse header, run verification
    Syscalls::solPanic("IBCClient::verifyHeader not implemented");
    return static_cast<uint64_t>(ProgramError::CustomError);
}

} // namespace ibc
} // namespace solc
