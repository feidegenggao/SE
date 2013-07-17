/*
 * ============================================================================
 *
 *       Filename:  test_socket.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/17/13 11:37:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "base/log.h"
#include    "net/socket.h"
#include    "net/sock_addr.h"
using namespace base;
using namespace net;

#include    <string.h>

int main()
{
    Socket client_socket;
    SockAddr server_addr("202.115.22.86", 80);
    client_socket.Connect(server_addr);

    string send_data("GET / HTTP/1.1\r\n\r\n");
    client_socket.Write(send_data.c_str(), send_data.length());

    const int MAXLENFORHTML = 1024 * 5;
    char read_buf[MAXLENFORHTML] = {0};
    int read_n = 0;
    int read_sum = 0;
    do
    {
        memset(read_buf, 0, sizeof(read_buf));
        read_n = client_socket.Read(read_buf, sizeof(read_buf));
        read_sum += read_n;
        LOG_DEBUG << "read from server :" << read_n;
    }while(read_n != 0);
    LOG_DEBUG << "read sum:" << read_sum;


    LOG_END;
    return 0;
}
