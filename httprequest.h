#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include<string>
#include<map>



//��Http�������ݵķ�װ
class HttpRequest
{
public:
    //֧�ֵ����󷽷�����
    enum Method
    {
        kInvalid, kGet, kPost, kHead, kPut, kDelete
    };
    //֧�ֵ�Э��
    enum Version
    {
        kUnknown, kHttp10, kHttp11
    };

    HttpRequest()
    : method_(kInvalid),
      version_(kUnknown)
    {

    }


    void setversion(Version v)
    {
        version_ = v;
    }

    Version getversion()
    {
        return version_;
    }


    bool setmethod(const char* start,const char* end)
    {
        std::string m(start,end);
        if(m == "GET")
        {
            method_ = kGet;
        }
        else if (m == "POST")
        {
            method_ = kPost;
        }
        else if (m == "HEAD")
        {
            method_ = kHead;
        }
        else if (m == "PUT")
        {
            method_ = kPut;
        }
        else if (m == "DELETE")
        {
            method_ = kDelete;
        }
        else
        {
            method_ = kInvalid;
        }
        return method_ != kInvalid;
    }

     Method method() const
    { return method_; }




    const char* methodString() const
    {
        const char* result = "UNKNOWN";
        switch(method_)
        {
        case kGet:
            result = "GET";
            break;
        case kPost:
            result = "POST";
            break;
        case kHead:
            result = "HEAD";
            break;
        case kPut:
            result = "PUT";
            break;
        case kDelete:
            result = "DELETE";
            break;
        default:
            break;
        }
        return result;
    }


    void setPath(const char* start, const char* end)
    {
        path_.assign(start, end);
    }

    const std::string& path() const
    { return path_; }


    void setQuery(const char* start, const char* end)
    {
        query_.assign(start, end);
    }

    const std::string& query() const
    { return query_; }





    void addHeader(const char* start, const char* colon, const char* end)
    {
        //��ͷ����ʼ�������ַ�����Ҳ����ͷ������
        std::string field(start, colon);
        ++colon;
        //�����ո�
        while (colon < end && isspace(*colon))
        {
            ++colon;
        }
        //ͷ��������
        std::string value(colon, end);
        //ȥ��ͷ������β���Ŀո�
        while (!value.empty() && isspace(value[value.size()-1]))
        {
            value.resize(value.size()-1);
        }
        //��ͷ����Ϣ������map��
        headers_[field] = value;
    }


    //��ȡͷ���ַ���
    std::string getHeader(const std::string& field) const
    {
        std::string result;
        std::map<std::string, std::string>::const_iterator it = headers_.find(field);
        if (it != headers_.end())
        {
        result = it->second;
        }
        return result;
    }


    const std::map<std::string, std::string>& headers() const
    { return headers_; }


    void swap(HttpRequest& next)
    {
        std::swap(method_,next.method_);
        std::swap(version_,next.version_);
        path_.swap(next.path_);
        query_.swap(next.query_);
        headers_.swap(next.headers_);
    }

    std::string findHeader(const std::string& header)
    {
        if(headers_.find(header) == headers_.end())
        return {};
        else
        return headers_[header];
    }

private:
    //���󷽷�
    Method method_;
    //HTTP�汾
    Version version_;
    //·��
    std::string path_;
    //������Դ
    std::string query_;
    //�ײ���Ϣ
    std::map<std::string, std::string> headers_;
};











#endif