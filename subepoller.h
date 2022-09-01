#ifndef SUBEPOLLER_H
#define SUBEPOLLER_H


#include "epoller.h"
#include <mutex>
#include "tcpconnection.h"
#include <map>
#include <memory>
#include "circularbuffer.hpp"
#include <unordered_set>
#include<set>
#include "entry.h"
#include <sys/timerfd.h>
#include <time.h>
#include <strings.h>
#include <atomic>
#include<unordered_map>


class TcpConnection;
class Entry;
class subepoller : public epoller
{
public:
    subepoller();
    ~subepoller() override;
    //���ڿ��߳����fd
    void addevent(int fd,int eve) override;
    void pool() override;
    void removefromlist(int fd);

 

    void addtocircularbuffer(std::shared_ptr<Entry>);
    
    void addeventInloop(int fd,int eve);

    void addeventInloop(int fd,int eve,int index);

    void addwrite(int fd);

    void cancelwrite(int fd);

    void stop()
    {
        start_ = 0;
    }
    bool getstate()
    {
        return state_;
    }

    int listsize()
    {
        return connectionlist_.size();
    }
private:
    typedef std::shared_ptr<Entry> EntryPtr;
    typedef std::weak_ptr<Entry> WeakEntryPtr;
    typedef std::shared_ptr<TcpConnection> ConnectionPtr;
    bool start_;
    bool state_;
    int wakeupfd;
    int timerfd;
    std::mutex mutex_;
    //�����첽��������ӵ�vector
    std::vector<std::pair<int,int>> connfdlist_;
    // //���TCP���Ӳ�����fd
    std::unordered_map<int,ConnectionPtr> connectionlist_;
    


    std::atomic<int> index_;

    //���ӵ���ʱ���յ���Ϣʱ�򻺳�����ĩβһ��Ԫ�ص�Ͱ����Ӵ���
    CircularBuffer< std::unordered_set< EntryPtr >  > circularbuffer_;    
    
    void wakeup();
    int createEventfd();
    int createTimerfd();
    void handleconnection(int fd,int event);
    void readTimerfd();
    void setnewtimer(int interval);
    void handletime();
    // void handleconnection(int fd,int event,int idx);
    

};





#endif