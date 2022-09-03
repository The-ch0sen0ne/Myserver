#include "httpcontext.h"
#include <algorithm>



//解析请求行
bool HttpContext::parseRequest(ConnectionBuffer* buf)
{
    bool res = 1;
    bool needmore = 1;
    while(needmore)
    {
        if(state_ == kRequest)
        {
            const char* crlf = buf->findCRLF();
            if(crlf)
            {
                res = processRequestLine(buf->peek(),crlf);
                if(res)
                {
                    buf->retrive(crlf - buf->peek() + 2);
                    state_ = kHeaders;
                }
                else
                {
                    needmore = 0;
                }
            }
            else
            {
                needmore = 0;
            }
        }
        else if(state_ == kHeaders)
        {
            const char* crlf = buf->findCRLF();
            if (crlf)
            {
                const char* colon = std::find(buf->peek(), crlf, ':');
            if (colon != crlf)
            {
                //增加头部信息
                request_.addHeader(buf->peek(), colon, crlf);
            }
            else
            {
                // empty line, end of header
                // FIXME:
                state_ = kGotAll;
                needmore = false;
            }
            buf->retrive(crlf - buf->peek()+ 2);
            }
            else
            {
                needmore = false;
            }
        }
        else if(state_ == kBody)
        {
            //直接抛弃正文内容
            std::string Length = request_.findHeader("Content-Length");
            if(Length.size() != 0)
            {
                int len = std::stoi(Length);
                 buf->retrive(len);
            }
        }
    }
    
    return res;
}









bool HttpContext::processRequestLine(const char* begin,const char* end)
{
    bool res = false;
    const char* start = begin;
    const char* space = std::find(start, end, ' ');
    if(end != space && request_.setmethod(begin,space))
    {
        //解析路径
        start = space + 1;
        space = std::find(start,end,' ');
        if(end != space)
        {
            const char* question = std::find(start,space,'?');
            if(question != space)
            {
                request_.setPath(start,question);
                request_.setQuery(question,space);
            }
            else
            {
                request_.setPath(start,space);
            }
        }


        start = space + 1;
        res = end - start == 8 && std::equal(start,end-1,"HTTP/1.");
        if(res)
        {
            if(*(end - 1) == '1')
            {
                request_.setversion(HttpRequest::kHttp11);
            }
            else if
            (*(end - 1) == '0')
            {
                request_.setversion(HttpRequest::kHttp10);
            }
            else{
                res = 0;
            }
        }
    }


    return res;
}