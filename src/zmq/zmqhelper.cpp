#include "zmqhelper.h"

ZmqHelper::ZmqHelper()
{
}

char *ZmqHelper::s_recv(void *socket)
{

    zmq_msg_t message;
    zmq_msg_init (&message);
    zmq_msg_recv(&message,socket, 0);
    int size = zmq_msg_size (&message);
    char *string =(char*) malloc (size + 1);
    memcpy (string, zmq_msg_data (&message), size);
    zmq_msg_close (&message);
    string [size] = 0;
    return (string);
}


//带有超时时间的数据接受
char *ZmqHelper::s_recv(void *socket,long replyTimeOut,int retryTimes)
{
    int retireLeft=retryTimes;

    //根据超时次数循环请求
    while(retireLeft>0){


        //poll in
        zmq_pollitem_t items [] = { { socket, 0, ZMQ_POLLIN, 0 } };

        //设置等待应答的超时时间
        int rc = zmq_poll (items, 1, replyTimeOut);

        if(rc==-1){
            break;
        }

        //得到应答
        if (items [0].revents & ZMQ_POLLIN) {
            //接收数据
            return s_recv(socket);
        }

        retireLeft--;
    }

    return NULL;

}


int ZmqHelper::s_send(void *socket, char *string)
{

    int rc;
    zmq_msg_t message;
    zmq_msg_init_size (&message, strlen (string));
    memcpy (zmq_msg_data (&message), string, strlen (string));
    rc = zmq_msg_send(&message, socket, 0);

    zmq_msg_close (&message);
    return (rc);

}

//  Sends string as 0MQ string, as multipart non-terminal
int ZmqHelper::s_sendmore (void *socket, char *string) {
    zmq_msg_t message;
    zmq_msg_init_size (&message, strlen (string));
    memcpy (zmq_msg_data (&message), string, strlen (string));
    int size = zmq_msg_send (&message, socket, ZMQ_SNDMORE);
    zmq_msg_close (&message);
    return (size);
}


void ZmqHelper::s_dump (void *socket)
{
    puts ("----------------------------------------");
    while (1) {
        //  Process all parts of the message
        zmq_msg_t message;
        zmq_msg_init (&message);
        int size = zmq_msg_recv (&message, socket, 0);

        //  Dump the message as text or binary
        char *data =(char*)zmq_msg_data (&message);
        int is_text = 1;
        int char_nbr;
        for (char_nbr = 0; char_nbr < size; char_nbr++)
            if ((unsigned char) data [char_nbr] < 32
                    ||  (unsigned char) data [char_nbr] > 127)
                is_text = 0;

        qDebug ("[%03d] ", size);

        for (char_nbr = 0; char_nbr < size; char_nbr++) {
            if (is_text)
                qDebug ("%c", data [char_nbr]);
            else
                qDebug ("%02X", (unsigned char) data [char_nbr]);
        }
        qDebug ("\n");

        int64_t more;           //  Multipart detection
        more = 0;
        size_t more_size = sizeof (more);
        zmq_getsockopt (socket, ZMQ_RCVMORE, &more, &more_size);
        zmq_msg_close (&message);
        if (!more)
            break;      //  Last message part
    }
}





