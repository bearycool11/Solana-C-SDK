#include "onchain/native/SolWrapper.hpp"
#include <solana_sdk.h>

namespace solc {
namespace native {

void SolWrapper::log(const char* msg) {
    sol_log(msg);
}

void SolWrapper::logData(const uint8_t* data, uint64_t len) {
    sol_log_data(data, len);
}

void SolWrapper::panic(const char* msg) {
    sol_panic(msg);
}

void SolWrapper::memCopy(void* dst, const void* src, uint64_t len) {
    sol_memcpy(dst, src, len);
}

uint64_t SolWrapper::invoke(const SolInstruction* ix,
                            SolAccountInfo* accounts,
                            uint64_t account_len) {
    return sol_invoke(ix, accounts, account_len);
}

uint64_t SolWrapper::invokeSigned(const SolInstruction* ix,
                                  SolAccountInfo* accounts,
                                  uint64_t account_len,
                                  const uint8_t* seeds[],
                                  const uint64_t seeds_lens[]) {
    return sol_invoke_signed(ix, accounts, account_len,
                             seeds, seeds_lens);
}

} // namespace native
} // namespace solc
