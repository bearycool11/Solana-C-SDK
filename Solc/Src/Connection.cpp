#include "solc/Connection.hpp"

namespace solc {

Connection::Connection(const std::string& rpcUrl) {
    // TODO: store rpcUrl
}

Connection::~Connection() { }

bool Connection::sendRawTransaction(const std::vector<uint8_t>& txData) {
    // TODO: implement via HTTP POST or websockets
    return false;
}

std::string Connection::simulateTransaction(const std::vector<uint8_t>& txData) {
    // TODO
    return {};
}

} // namespace solc
