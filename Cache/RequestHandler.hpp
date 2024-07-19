#ifndef RequestHandler_hpp
#define RequestHandler_hpp

#include <map>

#include "HttpRequest.h"
#include "RequestSender.h"
#include "ResponseSender.h"
#include "Cache/Cache.h"

class HttpRequestHandler {
public:
    
    void handleRequest(HttpRequest request);
    void handleResponse(HttpResponse response);
    
private:
    // I have chosen map since it is not possible to predict when the requests response
    // will be recieved
    std::unordered_map<std::string, std::vector<HttpRequest>> requestStorage;
    
    SptrCache cache;
    SptrRequestSender requestSender;
    SptrResponseSender responseSender;
};

#endif /* RequestHandler_hpp */
