#pragma once

#include <cstdint>
#include <solana_sdk.h>

namespace solc {
namespace native {

/// Convenience wrappers around Solana SDK syscalls
class SolWrapper {
public:
    /// Log a UTF-8 string
    static void log(const char* msg);

    /// Log raw bytes
    static void logData(const uint8_t* data, uint64_t len);

    /// Panic (abort) with a message
    static void panic(const char* msg);

    /// Copy memory
    static void memCopy(void* dst, const void* src, uint64_t len);

    /// Invoke a CPI instruction
    static uint64_t invoke(const SolInstruction* ix,
                           SolAccountInfo* accounts,
                           uint64_t account_len);

    /// Invoke a signed CPI instruction
    static uint64_t invokeSigned(const SolInstruction* ix,
                                 SolAccountInfo* accounts,
                                 uint64_t account_len,
                                 const uint8_t* seeds[],
                                 const uint64_t seeds_lens[]);
};

} // namespace native
} // namespace solc
