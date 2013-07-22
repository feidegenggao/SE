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

bool GetPage(const Url &server_url, string &http_header, string &html_data)
{
    Socket client_socket;
    if (!client_socket.Connect(server_url.GetSockAddr())) 
    {
        LOG_ERROR << "Can't connect url:" << server_url.Str();
        return false;
    }

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

    string http_data;//inclue http_header \r\n and html_data 
    do
    {
        memset(read_buf, 0, sizeof(read_buf));
        read_n = client_socket.Read(read_buf, sizeof(read_buf) - 1);
        if (read_n < 0) return false;
        read_buf[sizeof(read_buf) - 1] = '\0';

        read_sum += read_n;
        http_data += read_buf;
    }while(read_n != 0);

    //find the "\r\n\r\n" 's position this position is
    //the separator between http_header and html_data
    const size_t separator_opsition = http_data.find("\r\n\r\n");
    if (separator_opsition == string::npos)
    {
        //can't find \r\n\r\n, we can make assertion that this http_data is invalid
        LOG_ERROR << "Receive data NOT include \\r\\n\\r\\n ";
        return false;
    }

    http_header = string(http_data, 0, separator_opsition);
    string regex("^HTTP/1.[0 1]{1} 200 OK.*");
    if (RegexMatch(http_header, regex))
    {
        //LOG_DEBUG << "This HTTP header match 200 OK";
    }
    else
    {
        LOG_ERROR << "HTTP Server(url:" << server_url.Str() << "\tError Info:";

        string regex_find_code("^HTTP/1\\.[0-1]{1} (\\d{1,3}[^\\r\\n]*).*");
        RegexSearchResultType result;
        RegexSearch(http_header, regex_find_code, result);
        if (result.size() > 0)
        {
            LOG_ERROR << *result.begin();
        }

        return false;
    }
    html_data = string(http_data, separator_opsition + 4);

    return true;
}
