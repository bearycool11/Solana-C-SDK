#pragma once

#include <string>
#include <vector>

namespace solc {
namespace client {

/// JSON-RPC client for Solana
class SolanaClient {
public:
    /// rpc_url: e.g. "https://api.mainnet-beta.solana.com"
    explicit SolanaClient(std::string rpc_url);
    ~SolanaClient();

    /// Send a raw transaction (base64-encoded), returns tx signature
    std::string sendTransaction(const std::string& txBase64);

    /// Simulate a transaction, returns JSON result
    std::string simulateTransaction(const std::string& txBase64);

    /// Get account info in JSON form
    std::string getAccountInfo(const std::string& pubkeyBase58);

private:
    std::string _rpc_url;

    /// Helper to perform an HTTP POST with given JSON payload
    std::string post(const std::string& payload);
};

} // namespace client
} // namespace solc
