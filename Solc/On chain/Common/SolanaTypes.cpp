#include "onchain/common/SolanaTypes.hpp"

namespace solc {
namespace common {

Pubkey::Pubkey(const uint8_t* data) : _data(data) {}

const uint8_t* Pubkey::data() const {
    return _data;
}

} // namespace common
} // namespace solc
