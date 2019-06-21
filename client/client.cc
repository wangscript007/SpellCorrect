#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <json/json.h>
#include <iostream>
#include <string>

using namespace std;

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

void do_service(int sockfd);

int recvCycle(int newFd, void *p, int len)
{
    int total = 0;
    int ret;
    char *pStart = (char*)p;
    while(total < len){
        ret = recv(newFd, pStart + total, len - total, 0);
        if(0 == ret){
            return -1;
        }
        total = total + ret;
    }
    return total;
}

typedef struct
{
    int dataLen;
    char buf[1000];
}Train_t;

void sendTrain(string buff, int sockfd)
{
    Train_t train;
    memset(&train, 0, sizeof(Train_t));
    train.dataLen = sizeof(buff);
    strcpy(train.buf, buff.c_str());
    send(sockfd, &train, 4 + train.dataLen, 0);   
}

int recvTrain(string &buff, int sockfd)
{
    Train_t train;
    memset(&train, 0, sizeof(Train_t));
    recvCycle(sockfd, &train.dataLen, 4);
    int ret = recvCycle(sockfd, &train.buf, train.dataLen);
    buff = string(train.buf);
    return ret;
}

int main()
{
    int peerfd = socket(PF_INET, SOCK_STREAM, 0);
    if(peerfd == -1)
        ERR_EXIT("socket");

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("192.168.3.160"); //localhost
    //addr.sin_addr.s_addr = INADDR_ANY; //localhost
    addr.sin_port = htons(5000);
    socklen_t len = sizeof addr;
    if(connect(peerfd, (struct sockaddr*)&addr, len) == -1)
        ERR_EXIT("Connect");
	string buf;
    Train_t tmp;
    recvTrain(buf, peerfd);

    do_service(peerfd);
    return 0;
}

void do_service(int sockfd)
{
    string recvbuf;
    string sendbuf;
    recvbuf.resize(1000);
    sendbuf.resize(1000);
    
    while(1)
    {
        //fgets会把换行符也读取
        //fgets(sendbuf.c_str(), 1000, stdin);
        cin >> sendbuf;
        sendTrain(sendbuf, sockfd);
        
        int nread = recvTrain(recvbuf, sockfd);
        if(nread == -1)
        {
            if(errno == EINTR)
                continue;
            ERR_EXIT("read");
        }
        else if(nread == 0) //代表链接断开
        {
            printf("server close!\n");
            close(sockfd);
            exit(EXIT_SUCCESS);
        }

        Json::Reader reader;
        Json::Value root;
        if(reader.parse(recvbuf, root))
        {
            string word1 = root["word1"].asString();
            string word2 = root["word2"].asString();
            string word3 = root["word3"].asString();
            cout << word1 << " " << word2 << " " << word3 << endl;
        }
        
        //printf("receive msg : %s\n", recvbuf.c_str());
        recvbuf.clear();
        sendbuf.clear();
    }
}
