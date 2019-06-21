#ifndef __WD_SOCKETIO_H__
#define __WD_SOCKETIO_H__
#include <string.h>

namespace wd
{

typedef struct{
    int dataLen;
    char buf[1000];
}Train_t;

class SocketIO
{
public:
	explicit SocketIO(int fd);

    int sendTrain(const char * buff);
    int recvTrain(char * buff);
	
    //int readn(char * buff, int len);
	//int readline(char * buff, int maxlen);
	//int writen(const char * buff, int len);
private:
	//int recvPeek(char * buff, int len);

private:
	int _fd;
};

}//end of namespace wd

#endif 
