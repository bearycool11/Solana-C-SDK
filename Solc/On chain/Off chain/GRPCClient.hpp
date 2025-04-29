#pragma once

#include <string>
#include <functional>

namespace solc {
namespace client {

/// Stub gRPC client interface for Solana streaming (e.g., logs, slots)
class GRPCClient {
public:
    explicit GRPCClient(const std::string& endpoint);
    ~GRPCClient();

    /// Subscribe to transaction logs for a program ID
    /// callback is invoked with raw log entries
    void subscribeLogs(const std::string& programId,
                       std::function<void(const std::string&)> callback);

    /// Close all streams and cleanup
    void shutdown();

private:
    std::string _endpoint;
    // internal gRPC stubs/contexts would go here
};

} // namespace client
} // namespace solc
