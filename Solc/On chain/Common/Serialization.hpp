#pragma once
#include <cstdint>

namespace solc {
namespace common {

/// Write a little-endian u64 into a buffer
inline void write_u64_le(uint8_t* buf, uint64_t v) {
    for (int i = 0; i < 8; i++) {
        buf[i] = static_cast<uint8_t>(v >> (8 * i));
    }
}

/// Read a little-endian u64 from a buffer
inline uint64_t read_u64_le(const uint8_t* buf) {
    uint64_t v = 0;
    for (int i = 0; i < 8; i++) {
        v |= static_cast<uint64_t>(buf[i]) << (8 * i);
    }
    return v;
}

/// Write a 32-byte public key into a buffer
inline void write_pubkey(uint8_t buf[32], const uint8_t key[32]) {
    for (int i = 0; i < 32; i++) {
        buf[i] = key[i];
    }
}

/// Read a 32-byte public key from a buffer
inline void read_pubkey(uint8_t key[32], const uint8_t buf[32]) {
    for (int i = 0; i < 32; i++) {
        key[i] = buf[i];
    }
}

} // namespace common
} // namespace solc
