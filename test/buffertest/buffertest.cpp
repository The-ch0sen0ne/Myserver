#include "connectionbuffer.h"
#include <iostream>
#include<string.h>
#include<string>
#include<unistd.h>
int main(int argc,char* argv[])
{
    ConnectionBuffer buf;
    // std::cout << "befor readablebyte = " << buf.readable() << std::endl;
    // std::cout << "befor writeablebyte = " << buf.writeable() << std::endl;
    // std::string s(24,'a');
    // const char* a = "abcdfabcdf";
    // buf.append(a,strlen(a));
    // std::cout << "1 readablebyte = " << buf.readable() << std::endl;
    // std::cout << "1 writeablebyte = " << buf.writeable() << std::endl;
    

    // buf.retrive(5);    
    // std::cout << "2 readablebyte = " << buf.readable() << std::endl;
    // std::cout << "2 writeablebyte = " << buf.writeable() << std::endl;


    // buf.append(s.c_str(),s.size());
    // std::cout << "3 readablebyte = " << buf.readable() << std::endl;
    // std::cout << "3 writeablebyte = " << buf.writeable() << std::endl;
    


    // std::string ans = buf.readalltostring();
    // std::cout << "res string = " << ans << std::endl;


    int pipefd[2];

    if(pipe(pipefd) == -1)
    std::cerr << "pipe error" << std::endl;


    std::string a(60,'a');
    int len0 = write(pipefd[1],a.c_str(),a.size());

    int save;
    int len1 = buf.readfromfd(pipefd[0],&save);
    std::cout << "len1 = " << len1 << std::endl;


    std::cout << "string = " << buf.readalltostring() << std::endl;


    return 0;
}