#include "solc/BpfLoader.hpp"

namespace solc {

BpfLoader::BpfLoader()  { /* ctor */ }
BpfLoader::~BpfLoader() { /* dtor */ }

bool BpfLoader::loadProgram(const std::vector<uint8_t>& elfBytes) {
    // TODO: transliterate your TS logic here
    return false;
}

bool BpfLoader::deploy(const std::vector<uint8_t>& accountPubkey) {
    // TODO
    return false;
}

} // namespace solc
