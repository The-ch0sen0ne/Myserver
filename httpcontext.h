#ifndef HTTPCONTEXT_H
#define HTTPCONTEXT_H

#include "httprequest.h"
#include "connectionbuffer.h"

class ConnectionBuffer;
//用于读取HTTP请求的类
class HttpContext
{
public:
    enum HttpRequestParseState
    {
        kRequest,
        kHeaders,
        kBody,
        kGotAll
    };

    HttpContext()
    : state_(kRequest)
    {
    }


    bool parseRequest(ConnectionBuffer* buf);



    bool gotAll() const
    { return state_ == kGotAll; }

    void reset()
    {
        state_ = kRequest;
        HttpRequest dummy;
        request_.swap(dummy);
    }

    const HttpRequest& request() const
    { return request_; }

    HttpRequest& request()
    { return request_; }

private:
    bool processRequestLine(const char* begin,const char* end);

    HttpRequestParseState state_;

    HttpRequest request_;
};










#endif