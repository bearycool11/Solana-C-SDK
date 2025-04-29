#pragma once

#include <cstdint>
#include <solana_sdk.h>
#include "onchain/common/AccountInfo.hpp"
#include "onchain/common/Syscalls.hpp"
#include "onchain/common/Serialization.hpp"
#include "onchain/common/StatusCodes.hpp"

namespace solc {
namespace ibc {

/// Channel handshake states
enum class ChannelState : uint8_t {
    Uninitialized = 0,
    Init          = 1,
    TryOpen       = 2,
    Open          = 3,
    Closed        = 4
};

/// Ordering types
enum class Ordering : uint8_t {
    None      = 0,
    Ordered   = 1,
    Unordered = 2
};

#pragma pack(push,1)
/// On-chain representation of a channel end
struct ChannelEnd {
    ChannelState state;
    Ordering     ordering;
    uint8_t      remote_port[32];
    uint8_t      remote_channel[32];
    uint8_t      version[32];
};
#pragma pack(pop)

#pragma pack(push,1)
/// Simplified IBC packet metadata
struct Packet {
    uint64_t sequence;
    uint8_t  source_port[32];
    uint8_t  source_channel[32];
    uint8_t  dest_port[32];
    uint8_t  dest_channel[32];
    uint8_t  data_hash[32];
};
#pragma pack(pop)

/// BPF on-chain IBC channel operations
class IBCChannel {
public:
    /// Initialize a new channel end
    /// Accounts: channel account (writable), authority (signer)
    /// Data: [1-byte state=Init][1-byte ordering][32-byte port][32-byte channel][32-byte version]
    static uint64_t openChannel(const uint8_t* input);

    /// Close an existing channel
    /// Accounts: channel account (writable), authority (signer)
    static uint64_t closeChannel(const uint8_t* input);

    /// Send a packet
    /// Accounts: channel account, packet store account (writable), authority (signer)
    /// Data: serialized `Packet` struct
    static uint64_t sendPacket(const uint8_t* input);

    /// Receive a packet
    /// Accounts: channel account, packet store account (writable), authority (signer)
    /// Data: serialized `Packet` struct + proof
    static uint64_t recvPacket(const uint8_t* input);
};

} // namespace ibc
} // namespace solc
