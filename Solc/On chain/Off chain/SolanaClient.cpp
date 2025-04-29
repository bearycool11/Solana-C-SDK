#include "offchain/client/SolanaClient.hpp"
#include <curl/curl.h>
#include <sstream>

namespace solc {
namespace client {

static size_t curlWrite(void* contents, size_t size, size_t nmemb, void* userp) {
    auto* s = static_cast<std::string*>(userp);
    s->append(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

SolanaClient::SolanaClient(std::string rpc_url)
  : _rpc_url(std::move(rpc_url)) {}

SolanaClient::~SolanaClient() {}

std::string SolanaClient::post(const std::string& payload) {
    CURL* curl = curl_easy_init();
    std::string response;
    if (!curl) return "{}";

    curl_easy_setopt(curl, CURLOPT_URL, _rpc_url.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWrite);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    struct curl_slist* hdrs = nullptr;
    hdrs = curl_slist_append(hdrs, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hdrs);

    curl_easy_perform(curl);
    curl_slist_free_all(hdrs);
    curl_easy_cleanup(curl);
    return response;
}

std::string SolanaClient::sendTransaction(const std::string& txBase64) {
    std::ostringstream js;
    js << R"({"jsonrpc":"2.0","id":1,"method":"sendTransaction","params":[")"
       << txBase64 << R"(",{"encoding":"base64"}]})";
    return post(js.str());
}

std::string SolanaClient::simulateTransaction(const std::string& txBase64) {
    std::ostringstream js;
    js << R"({"jsonrpc":"2.0","id":1,"method":"simulateTransaction","params":[")"
       << txBase64 << R"(",{"sigVerify":false,"encoding":"base64"}]})";
    return post(js.str());
}

std::string SolanaClient::getAccountInfo(const std::string& pubkey) {
    std::ostringstream js;
    js << R"({"jsonrpc":"2.0","id":1,"method":"getAccountInfo","params":[" )"
       << pubkey << R"(",{"encoding":"base64"}]})";
    return post(js.str());
}

} // namespace client
} // namespace solc
