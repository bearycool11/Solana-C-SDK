#pragma once
#include <vector>
#include <cstdint>

namespace solc {

class BpfLoader {
public:
    BpfLoader();
    ~BpfLoader();

    /// Load a BPF program from bytes
    bool loadProgram(const std::vector<uint8_t>& elfBytes);

    /// Deploy to on-chain account
    bool deploy(const std::vector<uint8_t>& accountPubkey);

    // TODO: add other methods equivalent to your bpf-loader.ts exports
};

} // namespace solc
