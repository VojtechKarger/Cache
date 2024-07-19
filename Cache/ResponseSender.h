#ifndef ResponseSender_h
#define ResponseSender_h

#include "HttpResponse.h"

class ResponseSender {
public:
    virtual void send(HttpResponse response, HttpRequest request);
    
};

typedef std::shared_ptr<ResponseSender> SptrResponseSender;


#endif /* ResponseSender_h */
