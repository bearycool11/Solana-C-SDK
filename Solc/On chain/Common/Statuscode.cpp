#include "onchain/common/StatusCodes.hpp"

namespace solc {
namespace common {

const char* errorToString(ProgramError code) {
    switch (code) {
        case ProgramError::Success:                   return "Success";
        case ProgramError::InvalidArgument:           return "InvalidArgument";
        case ProgramError::InvalidInstructionData:    return "InvalidInstructionData";
        case ProgramError::InvalidAccountData:        return "InvalidAccountData";
        case ProgramError::AccountDataTooSmall:       return "AccountDataTooSmall";
        case ProgramError::InsufficientFunds:         return "InsufficientFunds";
        case ProgramError::IncorrectProgramId:        return "IncorrectProgramId";
        case ProgramError::MissingRequiredSignature:  return "MissingRequiredSignature";
        case ProgramError::AccountAlreadyInitialized: return "AccountAlreadyInitialized";
        case ProgramError::UninitializedAccount:      return "UninitializedAccount";
        case ProgramError::NotEnoughAccountKeys:      return "NotEnoughAccountKeys";
        case ProgramError::AccountBorrowFailed:       return "AccountBorrowFailed";
        case ProgramError::MaxSeedLengthExceeded:     return "MaxSeedLengthExceeded";
        case ProgramError::InvalidSeeds:              return "InvalidSeeds";
        case ProgramError::InvalidRealloc:            return "InvalidRealloc";
        case ProgramError::ComputationalBudgetExceeded: return "ComputationalBudgetExceeded";
        case ProgramError::PrivilegeEscalation:       return "PrivilegeEscalation";
        case ProgramError::CustomError:               return "CustomError";
        default:                                      return "UnknownError";
    }
}

} // namespace common
} // namespace solc
