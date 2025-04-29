# Solana-C-SDK

A high-performance C/C++ SDK for writing on-chain Solana programs with advanced features like fee burning, bug-watcher bounties, and built-in SHA-256 (“KINDLING”/“TORCHING”) utilities.

## Features

- **BurnBlock pipeline**: split transaction fees into validator rewards and on-chain burns  
- **BugWatcher**: detect owner-mismatch, overflow, CPI misuse, log anomalies, and pay tiny on-chain bounties  
- **SHA-256 helpers**: `KINDLING` (slot hashing) and `TORCHING` (burned-amount hashing) via Solana syscalls  
- **Modular design**: classes for `FeeCalculator`, `BurnBlock`, `BugWatcher`, `LedgerInterface`, `SmartContract`  
- **CMake build**: produces a stripped BPF shared object (`.so`) ready for deployment  
- **Extensible**: stubbed `BpfLoader` and `Connection` modules for off-chain program management and RPC calls  

## Repository Layout

- `Solana-C-SDK/`  
  - `CMakeLists.txt` — build configuration  
  - `LICENSE` — Apache-2.0 license  
  - `README.md` — this file  
  - `Solc/`  
    - `include/solc/`  
      - `BpfLoader.hpp`  
      - `BugWatcher.hpp`  
      - `BurnBlock.hpp`  
      - `Connection.hpp`  
      - `FeeCalculator.hpp`  
      - `LedgerInterface.hpp`  
      - `SmartContract.hpp`  
    - `src/`  
      - `BpfLoader.cpp`  
      - `BugWatcher.cpp`  
      - `BurnBlock.cpp`  
      - `Connection.cpp`  
      - `FeeCalculator.cpp`  
      - `LedgerInterface.cpp`  
      - `SmartContract.cpp`  
      - `main.cpp`  

## Prerequisites

- Linux or macOS  
- `clang` with BPF target support  
- `solana-cli` v1.10 or later  
- `CMake` ≥ 3.16  

Set the Solana SDK include path:

```bash
export SOLANA_SDK_INCLUDE=/path/to/solana/sdk/include
Solana-C-SDK

v2.0 “Interchain” Release – June 2025

A high-performance C/C++ toolkit for Solana on-chain programs and off-chain clients. This version adds basic IBC modules and a complete client SDK.

Features
	•	On-chain modules
	•	BurnProgram with fee burning, anomaly detection and bounties
	•	TokenMintProgram for SPL token creation
	•	GovernanceProgram for proposals, voting, execution
	•	IBC light-client (initialize, update, verify)
	•	IBC channel (open, close, send packet, receive packet stub)
	•	Common support libraries
	•	SolanaTypes, AccountInfo, syscalls, serialization, PDA seeds, sysvars, status codes
	•	Native wrappers for SystemProgram, TokenProgram, and SolWrapper
	•	Off-chain client modules
	•	SolanaClient for JSON-RPC calls
	•	GRPCClient stub for real-time subscriptions
	•	DRPCClient for parallel RPC with endpoint failover
	•	CMake build system producing a stripped BPF shared object

Repository Layout
	•	CMakeLists.txt
	•	LICENSE (Apache-2.0)
	•	README.md
	•	Solc/
	•	onchain/
	•	burn/
	•	BurnProgram.hpp
	•	BurnProgram.cpp
	•	token/
	•	TokenMintProgram.hpp
	•	TokenMintProgram.cpp
	•	governance/
	•	GovernanceProgram.hpp
	•	GovernanceProgram.cpp
	•	common/
	•	SolanaTypes.hpp, SolanaTypes.cpp
	•	AccountInfo.hpp, AccountInfo.cpp
	•	Syscalls.hpp, Syscalls.cpp
	•	Sysvar.hpp, Sysvar.cpp
	•	Seed.hpp, Seed.cpp
	•	Serialization.hpp, Serialization.cpp
	•	StatusCodes.hpp, StatusCodes.cpp
	•	native/
	•	SystemProgram.hpp, SystemProgram.cpp
	•	TokenProgram.hpp, TokenProgram.cpp
	•	SolWrapper.hpp, SolWrapper.cpp
	•	ibc/
	•	IBCClient.hpp, IBCClient.cpp
	•	IBCChannel.hpp, IBCChannel.cpp
	•	offchain/
	•	client/
	•	SolanaClient.hpp, SolanaClient.cpp
	•	GRPCClient.hpp, GRPCClient.cpp
	•	DRPCClient.hpp, DRPCClient.cpp
	•	include/solc/
	•	Public headers for core modules

Prerequisites
	•	Linux or macOS
	•	clang with BPF target support
	•	solana-cli v1.10 or later
	•	CMake 3.16 or higher

Set environment variable for Solana SDK include path:
