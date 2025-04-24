#pragma once
#include <string>

namespace solc {

class Connection {
public:
    Connection(const std::string& rpcUrl);
    ~Connection();

    /// Send a raw transaction (base64 or binary)
    bool sendRawTransaction(const std::vector<uint8_t>& txData);

    /// Simulate a transaction
    std::string simulateTransaction(const std::vector<uint8_t>& txData);

    // TODO: other methods from connection.ts
};

} // namespace solc
