#include "onchain/common/AccountInfo.hpp"

namespace solc {
namespace common {

AccountInfo::AccountInfo(SolAccountInfo* info) : _info(info) {}

const uint8_t* AccountInfo::key() const {
    return _info->key;
}

uint64_t AccountInfo::lamports() const {
    return _info->lamports;
}

uint8_t* AccountInfo::data() const {
    return _info->data;
}

uint64_t AccountInfo::data_len() const {
    return _info->data_len;
}

const uint8_t* AccountInfo::owner() const {
    return _info->owner;
}

bool AccountInfo::is_signer() const {
    return _info->is_signer;
}

bool AccountInfo::is_writable() const {
    return _info->is_writable;
}

} // namespace common
} // namespace solc
