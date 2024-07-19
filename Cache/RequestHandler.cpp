#include "RequestHandler.hpp"
#include <optional>

void HttpRequestHandler::handleRequest(HttpRequest request) {
    auto response = cache->item(request.cacheKey());
    if (response != std::nullopt) {
        return responseSender->send(*response, request);
    }
    
    if (requestStorage.count(request.cacheKey()) != 0) {
        return requestStorage[request.cacheKey()].push_back(request);
    }
    
    requestSender->send(request);
    std::vector<HttpRequest> requests;
    requests.push_back(request);
    requestStorage[request.cacheKey()] = requests;
}

void HttpRequestHandler::handleResponse(HttpResponse response) {
    auto it = requestStorage.find(response.cacheKey());
    if (it == requestStorage.end()) return;
    for (auto & request : it->second) {
        responseSender->send(response, request);
    }
    requestStorage.erase(it);
    
    cache->setItem(response, response.cacheKey());
}
