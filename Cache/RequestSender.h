#ifndef RequestSender_h
#define RequestSender_h

#include "HttpRequest.h"

class RequestSender {
public:
    virtual void send(HttpRequest request);
    
};

typedef std::shared_ptr<RequestSender> SptrRequestSender;

#endif /* RequestSender_h */
