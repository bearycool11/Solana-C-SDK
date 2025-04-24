#include "solc/FeeCalculator.hpp"
#include <cmath>

namespace solc {

FeeCalculator::FeeCalculator(uint64_t baseFeeRate, double burnRatio)
  : _baseFeeRate(baseFeeRate), _burnRatio(burnRatio) {}

FeeCalculator::~FeeCalculator() {}

uint64_t FeeCalculator::computeBurn(uint64_t totalLamports) const {
    // TODO: your TS logic here
    return static_cast<uint64_t>(std::floor(totalLamports * _burnRatio));
}

uint64_t FeeCalculator::computeValidatorShare(uint64_t totalLamports) const {
    return totalLamports - computeBurn(totalLamports);
}

} // namespace solc
