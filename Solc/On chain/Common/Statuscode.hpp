#pragma once
#include <cstdint>

namespace solc {
namespace common {

/// Common program error codes matching Solana's ProgramError enum
enum class ProgramError : uint32_t {
    Success                   = 0,
    InvalidArgument           = 1,
    InvalidInstructionData    = 2,
    InvalidAccountData        = 3,
    AccountDataTooSmall       = 4,
    InsufficientFunds         = 5,
    IncorrectProgramId        = 6,
    MissingRequiredSignature  = 7,
    AccountAlreadyInitialized = 8,
    UninitializedAccount      = 9,
    NotEnoughAccountKeys      = 10,
    AccountBorrowFailed       = 11,
    MaxSeedLengthExceeded     = 12,
    InvalidSeeds              = 13,
    InvalidRealloc            = 14,
    ComputationalBudgetExceeded = 15,
    PrivilegeEscalation       = 16,
    CustomError               = 0x100
};

/// Convert error to human-readable string (for logs)
const char* errorToString(ProgramError code);

} // namespace common
} // namespace solc
