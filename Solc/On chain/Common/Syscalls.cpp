#include "onchain/common/Syscalls.hpp"
#include <solana_sdk.h>

namespace solc {
namespace common {

void Syscalls::solLog(const char* msg) {
    sol_log(msg);
}

void Syscalls::solLogData(const uint8_t* data, uint64_t len) {
    sol_log_data(data, len);
}

void Syscalls::solPanic(const char* msg) {
    sol_panic(msg);
}

void Syscalls::memCopy(void* dst, const void* src, uint64_t len) {
    sol_memcpy(dst, src, len);
}

uint64_t Syscalls::invoke(const SolInstruction* ix,
                          SolAccountInfo* accounts,
                          uint64_t account_len) {
    return sol_invoke(ix, accounts, account_len);
}

uint64_t Syscalls::invokeSigned(const SolInstruction* ix,
                                SolAccountInfo* accounts,
                                uint64_t account_len,
                                const uint8_t* seeds[],
                                const uint64_t seeds_lens[]) {
    return sol_invoke_signed(ix, accounts, account_len,
                             seeds, seeds_lens);
}

uint64_t Syscalls::sha256(const uint8_t* data,
                          uint64_t len,
                          uint8_t* out,
                          uint64_t out_len) {
    return sol_sha256(data, len, out, out_len);
}

} // namespace common
} // namespace solc
