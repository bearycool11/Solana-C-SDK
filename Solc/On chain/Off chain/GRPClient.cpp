#include "offchain/client/GRPCClient.hpp"
// #include <grpcpp/grpcpp.h>   // if gRPC library available

namespace solc {
namespace client {

GRPCClient::GRPCClient(const std::string& endpoint)
  : _endpoint(endpoint) {
    // TODO: set up gRPC channel and stubs
}

GRPCClient::~GRPCClient() {
    shutdown();
}

void GRPCClient::subscribeLogs(const std::string& programId,
                               std::function<void(const std::string&)> callback) {
    // TODO: create stream request for logsSubscribe(programId)
    // for each incoming message: callback(raw_message)
}

void GRPCClient::shutdown() {
    // TODO: teardown gRPC channel/context
}

} // namespace client
} // namespace solc
