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
