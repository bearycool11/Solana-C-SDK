#include "onchain/governance/GovernanceProgram.hpp"
#include <cstring>

namespace solc {
namespace onchain {
namespace governance {

using solc::AccountInfo;
using solc::Syscalls;
using solc::ProgramError;

uint64_t GovernanceProgram::process(const uint8_t* input) {
  SolParameters params;
  if (sol_deserialize(input, &params)) {
    return ProgramError::InvalidArgument;
  }
  if (params.data_len == 0) {
    sol_panic("Governance: missing instruction tag");
  }
  auto instr = static_cast<InstructionType>(params.data[0]);
  switch (instr) {
    case InstructionType::CreateProposal:
      createProposal(params);
      break;
    case InstructionType::CastVote:
      castVote(params);
      break;
    case InstructionType::ExecuteProposal:
      executeProposal(params);
      break;
    default:
      sol_panic("Governance: unknown instruction");
  }
  return ProgramError::Success;
}

void GovernanceProgram::createProposal(const SolParameters& params) {
  if (params.num_accounts < 3) {
    sol_panic("Governance: requires 3 accounts");
  }
  AccountInfo proposer(&params.ka[0]);
  AccountInfo proposalAcc(&params.ka[1]);
  AccountInfo sysProg(&params.ka[2]);

  // signer check
  Syscalls::assert_signer(proposer);

  // initialize proposal state
  Proposal p{};
  Syscalls::memcpy(p.proposer, proposer.key(), 32);
  p.yes_votes = 0;
  p.no_votes  = 0;
  p.executed  = false;

  // write to account data
  uint8_t* dst = proposalAcc.data();
  if (proposalAcc.data_len() < sizeof(Proposal)) {
    sol_panic("Governance: proposal account too small");
  }
  Syscalls::memcpy(dst, &p, sizeof(Proposal));
}

void GovernanceProgram::castVote(const SolParameters& params) {
  if (params.num_accounts < 2) {
    sol_panic("Governance: requires 2 accounts");
  }
  AccountInfo voter(&params.ka[0]);
  AccountInfo proposalAcc(&params.ka[1]);

  Syscalls::assert_signer(voter);

  if (params.data_len < 2) {
    sol_panic("Governance: missing vote flag");
  }
  uint8_t vote = params.data[1];
  if (vote > 1) {
    sol_panic("Governance: invalid vote flag");
  }

  // load existing state
  uint8_t* dst = proposalAcc.data();
  Proposal p;
  Syscalls::memcpy(&p, dst, sizeof(Proposal));

  if (p.executed) {
    sol_panic("Governance: proposal already executed");
  }
  // tally
  if (vote == 1) {
    p.yes_votes++;
  } else {
    p.no_votes++;
  }
  // write back
  Syscalls::memcpy(dst, &p, sizeof(Proposal));
}

void GovernanceProgram::executeProposal(const SolParameters& params) {
  if (params.num_accounts < 2) {
    sol_panic("Governance: requires 2 accounts");
  }
  AccountInfo executor(&params.ka[0]);
  AccountInfo proposalAcc(&params.ka[1]);

  Syscalls::assert_signer(executor);

  uint8_t* dst = proposalAcc.data();
  Proposal p;
  Syscalls::memcpy(&p, dst, sizeof(Proposal));

  if (p.executed) {
    sol_panic("Governance: already executed");
  }
  // simple majority
  if (p.yes_votes <= p.no_votes) {
    sol_panic("Governance: not approved");
  }
  p.executed = true;

  Syscalls::memcpy(dst, &p, sizeof(Proposal));
  // TODO: invoke any execution CPI logic here
}

} // namespace governance
} // namespace onchain
} // namespace solc
