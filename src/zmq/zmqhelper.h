#ifndef ZMQHELPER_H
#define ZMQHELPER_H

#include "zmq.h"
#include "zmq_utils.h"

#include <QDebug>

class ZmqHelper
{
public:
    ZmqHelper();
    static char * s_recv (void *socket);
    static char * s_recv(void *socket,long replyTimeOut,int retryTimes);

    static int s_send (void *socket, char *string);
    static int s_sendmore (void *socket, char *string);
    static void  s_dump (void *socket);
};



#endif // ZMQHELPER_H
