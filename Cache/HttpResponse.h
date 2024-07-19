#ifndef HttpResponse_h
#define HttpResponse_h
#include <string>

struct HttpResponse {
    // should be the same as cache key for equivalent request
    std::string cacheKey() const { return ""; }
};

#endif /* HttpResponse_h */
