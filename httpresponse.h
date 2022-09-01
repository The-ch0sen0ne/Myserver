#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include<map>
#include<string>
#include"connectionbuffer.h"

class ConnectionBuffer;
class HttpResponse
{
public:
    enum status
    {
        kUnknown,
        k200Ok = 200,
        k301MovedPermanently = 301,
        k400BadRequest = 400,
        k404NotFound = 404
    };

    explicit HttpResponse(bool close)
    : statusCode_(kUnknown),
    closeConnection_(close)
    {

    }




     //设置响应码
     void setStatusCode(status code)
    { statusCode_ = code; }


    //设置状态信息
    void setStatusMessage(const std::string& message)
    { statusMessage_ = message; }


    //设置是否关闭连接
    void setCloseConnection(bool on)
    { closeConnection_ = on; }

    //返回是否关闭连接
    bool closeConnection() const
    { return closeConnection_; }

    //设置文本类型的头部
    void setContentType(const std::string& contentType)
    { addHeader("Content-Type", contentType); }

    // FIXME: replace string with StringPiece
    void addHeader(const std::string& key, const std::string& value)
    { headers_[key] = value; }


    //设置主体
    void setBody(const std::string& body)
    { body_ = body; }

    void appendToBuffer(ConnectionBuffer* output) const;
private:
    std::map<std::string,std::string> headers_;
    status statusCode_;
    std::string statusMessage_;
    std::string body_;
    bool closeConnection_;
};








#endif