#pragma once
#include <cstdint>
#include "solana_sdk.h"

namespace solc {
namespace common {

/// Thin wrappers around Solana C SDK syscalls
class Syscalls {
public:
    static void        solLog(const char* msg);
    static void        solLogData(const uint8_t* data, uint64_t len);
    static void        solPanic(const char* msg);
    static void        memCopy(void* dst, const void* src, uint64_t len);

    static uint64_t    invoke(const SolInstruction* ix,
                              SolAccountInfo* accounts,
                              uint64_t account_len);

    static uint64_t    invokeSigned(const SolInstruction* ix,
                                     SolAccountInfo* accounts,
                                     uint64_t account_len,
                                     const uint8_t* seeds[],
                                     const uint64_t seeds_lens[]);

    static uint64_t    sha256(const uint8_t* data,
                              uint64_t len,
                              uint8_t* out,
                              uint64_t out_len);
};

} // namespace common
} // namespace solc
