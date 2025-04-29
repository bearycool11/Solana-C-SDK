#include "onchain/ibc/IBCChannel.hpp"
#include <cstring>

namespace solc {
namespace ibc {

using common::AccountInfo;
using common::Syscalls;
using common::ProgramError;
using common::read_u64_le;

uint64_t IBCChannel::openChannel(const uint8_t* input) {
    SolParameters params;
    if (sol_deserialize(input, &params)) {
        return static_cast<uint64_t>(ProgramError::InvalidInstructionData);
    }
    if (params.num_accounts < 2) {
        Syscalls::solPanic("IBCChannel::openChannel requires 2 accounts");
    }
    AccountInfo channelAcc(&params.ka[0]);
    AccountInfo authority(&params.ka[1]);

    Syscalls::assert_signer(authority);

    if (params.data_len < 1+1+32+32+32) {
        Syscalls::solPanic("IBCChannel::openChannel data too short");
    }
    ChannelEnd end;
    end.state    = static_cast<ChannelState>(params.data[0]);
    end.ordering = static_cast<Ordering>(params.data[1]);
    std::memcpy(end.remote_port,    params.data+2, 32);
    std::memcpy(end.remote_channel, params.data+34,32);
    std::memcpy(end.version,        params.data+66,32);

    if (channelAcc.data_len() < sizeof(ChannelEnd)) {
        Syscalls::solPanic("IBCChannel::openChannel account too small");
    }
    Syscalls::memCopy(channelAcc.data(), &end, sizeof(end));
    return static_cast<uint64_t>(ProgramError::Success);
}

uint64_t IBCChannel::closeChannel(const uint8_t* input) {
    SolParameters params;
    if (sol_deserialize(input, &params)) {
        return static_cast<uint64_t>(ProgramError::InvalidInstructionData);
    }
    if (params.num_accounts < 2) {
        Syscalls::solPanic("IBCChannel::closeChannel requires 2 accounts");
    }
    AccountInfo channelAcc(&params.ka[0]);
    AccountInfo authority(&params.ka[1]);

    Syscalls::assert_signer(authority);

    ChannelEnd end;
    end.state = ChannelState::Closed;
    if (channelAcc.data_len() < sizeof(ChannelEnd)) {
        Syscalls::solPanic("IBCChannel::closeChannel account too small");
    }
    Syscalls::memCopy(channelAcc.data(), &end, sizeof(end));
    return static_cast<uint64_t>(ProgramError::Success);
}

uint64_t IBCChannel::sendPacket(const uint8_t* input) {
    SolParameters params;
    if (sol_deserialize(input, &params)) {
        return static_cast<uint64_t>(ProgramError::InvalidInstructionData);
    }
    if (params.num_accounts < 3) {
        Syscalls::solPanic("IBCChannel::sendPacket requires 3 accounts");
    }
    AccountInfo channelAcc(&params.ka[0]);
    AccountInfo packetAcc(&params.ka[1]);
    AccountInfo authority(&params.ka[2]);

    Syscalls::assert_signer(authority);

    if (params.data_len < sizeof(Packet)) {
        Syscalls::solPanic("IBCChannel::sendPacket data too short");
    }
    Packet pkt;
    std::memcpy(&pkt, params.data, sizeof(Packet));

    if (packetAcc.data_len() < sizeof(Packet)) {
        Syscalls::solPanic("IBCChannel::sendPacket packet account too small");
    }
    Syscalls::memCopy(packetAcc.data(), &pkt, sizeof(pkt));
    return static_cast<uint64_t>(ProgramError::Success);
}

uint64_t IBCChannel::recvPacket(const uint8_t* input) {
    // This would include proof verification—stubbed for now
    Syscalls::solPanic("IBCChannel::recvPacket not implemented");
    return static_cast<uint64_t>(ProgramError::CustomError);
}

} // namespace ibc
} // namespace solc
