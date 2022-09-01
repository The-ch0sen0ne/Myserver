#include "httpresponse.h"


#include <stdio.h>
#include<string.h>

void HttpResponse::appendToBuffer(ConnectionBuffer* output) const
{
    const char* crlf = "\r\n";
    const char* separator = ": ";
    const char* close = "Connection: close\r\n";
    const char* keepalive = "Connection: Keep-Alive\r\n";
    char buf[32];
    snprintf(buf, sizeof(buf), "HTTP/1.1 %d ", statusCode_);
    output->append(buf,strlen(buf));
    output->append(statusMessage_.c_str(),statusMessage_.size());
    //��Ӧ����ͷ���ķָ���
    output->append(crlf,strlen(crlf));

    if (closeConnection_)
    {
        output->append(close,strlen(close));
    }
    else
    {
        snprintf(buf, sizeof(buf), "Content-Length: %d\r\n", body_.size());
        output->append(buf,strlen(buf));
        output->append(keepalive,strlen(keepalive));
    }

    //���ͻ��������ͷ����Ϣ
    for (const auto& header : headers_)
    {
        output->append(header.first.c_str(),header.first.size());
        output->append(separator,strlen(separator));
        output->append(header.second.c_str(),header.second.size());
        output->append(crlf,strlen(crlf));
    }

    //ͷ��������ķָ���
    output->append(crlf,strlen(crlf));
    //����
    output->append(body_.c_str(),body_.size());
}