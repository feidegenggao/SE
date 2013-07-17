/*
 * ============================================================================
 *
 *       Filename:  http.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/17/13 17:22:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  lxf (), 
 *        Company:  NDSL
 *
 * ============================================================================
 */
#include    "http.h"
#include    "url.h"
#include    "base/regex.h"
#include    "base/log.h"
using namespace base;
#include    "net/socket.h"
using namespace net;

#include    <string.h>

bool GetPage(const Url &server_url, string &http_header, string &http_data)
{
    Socket client_socket;
    if (!client_socket.Connect(server_url.GetSockAddr())) return false;

    //Group the HTTP header that will send to HTTP-Server
    //Get
    string send_data("GET ");
    send_data += server_url.GetSourceDataUrl();
    send_data += " HTTP/1.0\r\n";
    //Host
    send_data = send_data + string("Host:") + server_url.GetNode() + string("\r\n");
    //Connection
    send_data = send_data + "Connection:close\r\n";
    //Accept
    send_data = send_data + "Accept:text/html\r\n";
    //User-Agent
    send_data = send_data + "User-Agent:pighead\r\n";
    //The end
    send_data += "\r\n";
    //End Group the HTTP header that will send to HTTP-Server

    client_socket.Write(send_data.c_str(), send_data.length());

    const int MAXLENFORHTML = 1024 * 5;
    char read_buf[MAXLENFORHTML] = {0};
    int read_n = 0;
    int read_sum = 0;

    string  dst_string("HTTP/1.1 200 OK");
    read_n = client_socket.Read(read_buf, dst_string.length());
    LOG_DEBUG << "read from server :" << read_n;
    string result_string(read_buf);
    //FIXME:
    //Currently, we only receive the 200 OK datagram
    string regex_string("HTTP/1.[0 1]{1} 200 OK");
    if (!RegexMatch(result_string, regex_string)) return false;

    do
    {
        memset(read_buf, 0, sizeof(read_buf));
        read_n = client_socket.Read(read_buf, sizeof(read_buf));
        read_sum += read_n;
        LOG_DEBUG << "read from server :" << read_n;
        LOG_DEBUG << read_buf;
    }while(read_n != 0);
    LOG_DEBUG << "read sum:" << read_sum;
    return true;
}
