#pragma once
#include <cstdint>

namespace solc {

class FeeCalculator {
public:
    /// baseFeeRate: lamports per signature; 
    /// burnRatio: fraction [0–1] of fees to burn
    FeeCalculator(uint64_t baseFeeRate, double burnRatio);
    ~FeeCalculator();

    /// Total lamports to burn
    uint64_t computeBurn(uint64_t totalLamports) const;

    /// Lamports to validator
    uint64_t computeValidatorShare(uint64_t totalLamports) const;

private:
    uint64_t _baseFeeRate;
    double   _burnRatio;
};

} // namespace solc
