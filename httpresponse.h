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




     //������Ӧ��
     void setStatusCode(status code)
    { statusCode_ = code; }


    //����״̬��Ϣ
    void setStatusMessage(const std::string& message)
    { statusMessage_ = message; }


    //�����Ƿ�ر�����
    void setCloseConnection(bool on)
    { closeConnection_ = on; }

    //�����Ƿ�ر�����
    bool closeConnection() const
    { return closeConnection_; }

    //�����ı����͵�ͷ��
    void setContentType(const std::string& contentType)
    { addHeader("Content-Type", contentType); }

    // FIXME: replace string with StringPiece
    void addHeader(const std::string& key, const std::string& value)
    { headers_[key] = value; }


    //��������
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