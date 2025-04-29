#pragma once

#include <cstdint>
#include <solana_sdk.h>

#include "solc/AccountInfo.hpp"
#include "solc/Syscalls.hpp"
#include "solc/StatusCodes.hpp"

namespace solc {
namespace onchain {
namespace governance {

/// Governance instruction types
enum class InstructionType : uint8_t {
  CreateProposal   = 0,
  CastVote         = 1,
  ExecuteProposal  = 2,
};

#pragma pack(push,1)
/// On-chain stored proposal state
struct Proposal {
  uint8_t  proposer[32];   // Pubkey of proposer
  uint64_t yes_votes;
  uint64_t no_votes;
  bool     executed;
};
#pragma pack(pop)
static_assert(sizeof(Proposal) == 49, "Proposal struct must be packed to 49 bytes");

/// BPF on-chain Governance program
class GovernanceProgram {
public:
  /// Entry point: dispatches by first byte of instruction-data
  static uint64_t process(const uint8_t* input);

private:
  static void createProposal(const SolParameters& params);
  static void castVote      (const SolParameters& params);
  static void executeProposal(const SolParameters& params);
};

} // namespace governance
} // namespace onchain
} // namespace solc
