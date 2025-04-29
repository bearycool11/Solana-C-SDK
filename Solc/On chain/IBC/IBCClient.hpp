#pragma once

#include <cstdint>
#include <solana_sdk.h>
#include "onchain/common/AccountInfo.hpp"
#include "onchain/common/Syscalls.hpp"
#include "onchain/common/Serialization.hpp"
#include "onchain/common/StatusCodes.hpp"

namespace solc {
namespace ibc {

#pragma pack(push,1)
/// Light‐client state for another chain
struct ClientState {
    uint8_t  chain_id[32];     // UTF-8 bytes or hashed identifier
    uint64_t latest_height;    // last verified block height
    bool     frozen;           // if true, client is frozen
    uint8_t  trust_root[32];   // root hash of trusted state
};
#pragma pack(pop)

#pragma pack(push,1)
/// Consensus state (timestamp + commitment root)
struct ConsensusState {
    uint64_t timestamp;
    uint8_t  root[32];
};
#pragma pack(pop)

/// BPF on-chain IBC light-client operations
class IBCClient {
public:
    /// Initialize a new client in account[0], funded by account[1]
    /// instruction data: [32-byte chain_id][8-byte init_height][32-byte trust_root]
    static uint64_t initialize(const uint8_t* input);

    /// Update the client with a new header
    /// instruction data: serialized header + proof
    static uint64_t update(const uint8_t* input);

    /// Verify that a header is valid against the stored state
    /// instruction data: serialized header + proof
    static uint64_t verifyHeader(const uint8_t* input);
};

} // namespace ibc
} // namespace solc
